#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "button.h"
#include "prebuild.h"
#include "resourceManager.h"

const int parallelResolution = 1920;
const int verticalResolution = 1080;

class textbox
{
public:
    sf::Text text;
    sf::RectangleShape box;
    std::string name;

    textbox() = delete; // illegal

    // name, content, font, size, position, relative position of text
    textbox(const std::string &uiName, const std::string &content, const sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size, const sf::Vector2f &textAlignment = {0.5f, 0.5f}) : name(uiName), text(font, content)
    {
        // set box
        box.setSize(size);
        box.setFillColor(sf::Color::White);
        box.setPosition(position);
        box.setOrigin({size.x / 2.f, size.y / 2.f});
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(5.0f);

        // set text
        text.setCharacterSize(36);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = text.getLocalBounds();
        float textX = position.x - size.x / 2 + textAlignment.x * size.x;
        float textY = position.y - size.y / 2 + textAlignment.y * size.y;
        textX -= textBounds.size.x * textAlignment.x;
        textY -= textBounds.size.y * textAlignment.y;
        text.setOrigin({0, 0});
        text.setPosition({textX, textY});
    }

    void updateText(const std::string& newContent) {
        text.setString(newContent);
    }
};

class UI
{
public:
    std::vector<textbox *> allUI;
    sf::Font font;
    std::vector<PrebuildManager *> prebuildButtons;
    sf::FloatRect bottom_ui_region;
    std::vector<sf::FloatRect> preset_button_rect; // position of center, as is defined in button
    int resource = 0;
    int resourceIncreaseRate;

    UI()
    {
        if (font.openFromFile("./assets/font/MesloLGS NF Regular.ttf"))
        {
            // std::cout << "font loaded" << std::endl;
        }

        sf::Vector2f size = {1200.f, 250.f};
        sf::Vector2f position = {parallelResolution / 2.f, verticalResolution - 250.f / 2.f}; // position of the center

        bottom_ui_region = {{position.x - size.x / 2.f, position.y - size.y / 2.f}, size}; // rect uses position of top left corner

        textbox *bottomBox = new textbox("bottomBox", "main menu", font, position, size, {0, 0.5});
        allUI.push_back(bottomBox);

        textbox *resourceBox = new textbox("resourceBox", to_string(resource) + " + " + to_string(resourceIncreaseRate), font, {parallelResolution / 2.f + 100.f, verticalResolution - 250.f / 2.f}, {200.f, 100.f}, {0, 0});
        allUI.push_back(resourceBox);

        float buttonSize = 70.f;
        float padding = 10.f;
        float startX = position.x + size.x / 2 -  padding - buttonSize / 2;
        float startY = position.y -  padding - buttonSize;

        // Create a 3x3 grid of preset buttons
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 4; ++col)
            {
                float x = startX - col * (buttonSize + padding);
                float y = startY + row * (buttonSize + padding);
                preset_button_rect.push_back({{x, y}, {buttonSize, buttonSize}});
            }
        }

        for (int i = 0; i < 12; i++)
        {
            ArrowTower_Prebuild *prebuildBtn = new ArrowTower_Prebuild(
                preset_button_rect[i].position,
                preset_button_rect[i].size,
                sf::Color::Yellow);
            prebuildButtons.push_back(prebuildBtn);
        }
    }

    void draw_in_ui_View(sf::RenderWindow &window)
    {
        for (auto &textbox : allUI)
        {
            window.draw(textbox->box);
            window.draw(textbox->text);
        }
        for (auto &prebuildButton : prebuildButtons)
        {
            prebuildButton->drawUI(window);
        }
    }

    void draw_in_game_View(sf::RenderWindow &window)
    {
        for (auto &prebuildButton : prebuildButtons)
        {
            prebuildButton->drawPreview(window);
        }
    }

    void update(sf::Vector2f mousePos, sf::Vector2f gameMousePos, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure *> &infrastructures, ResourceManager &resourceManager)
    {
        for (auto &prebuildButton : prebuildButtons)
        {
            prebuildButton->update(mousePos, gameMousePos, blocks, infrastructures, bottom_ui_region,resourceManager);
        }
        resource = resourceManager.resource;
        resourceIncreaseRate = resourceManager.increaseRate;
        for (auto &textbox : allUI)
        {
            if(textbox->name == "resourceBox"){
                textbox->updateText(to_string(resource) + " + " + to_string(resourceIncreaseRate));
            }
        }
    }

    bool isprebuilding()
    {
        for (auto &prebuildButton : prebuildButtons)
        {
            if (prebuildButton->prebuilding)
            {
                return true;
            }
        }
        return false;
    }
};

#endif