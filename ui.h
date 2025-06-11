#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "button.h"
#include "prebuild.h"

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
};

class UI
{
public:
    std::vector<textbox *> allUI;
    sf::Font font;
    std::vector<PrebuildManager *> prebuildButtons;

    UI()
    {
        if (font.openFromFile("./assets/font/MesloLGS NF Regular.ttf"))
        {
            // std::cout << "font loaded" << std::endl;
        }
        sf::Vector2f size(1200.f, 250.f);
        sf::Vector2f position(parallelResolution / 2.f, verticalResolution - size.y / 2.f);

        textbox *bottomBox = new textbox("bottomBox", "main menu", font, position, size, {0, 0.5});
        allUI.push_back(bottomBox);

        float buttonSize = 60.f;                                           // Size of each button
        float padding = 10.f;                                              // Space between buttons
        float startX = position.x + padding + buttonSize / 2;              // Left edge of bottomBox + padding
        float startY = position.y - size.y / 2 + padding + buttonSize / 2; // Middle of bottomBox (since we're using bottom half)

        // Create a 3x3 grid of PrebuildManager buttons
        for (int row = 0; row < 3; ++row)
        {
            for (int col = 0; col < 3; ++col)
            {
                float x = startX + col * (buttonSize + padding);
                float y = startY + row * (buttonSize + padding);

                // Create a new PrebuildManager with different colors for each button
                sf::Color buttonColor(100 + col * 50, 100 + row * 50, 200); // Vary color based on position
                ArrowTower_Prebuild *prebuildBtn = new ArrowTower_Prebuild(
                    {x, y},
                    {buttonSize, buttonSize},
                    buttonColor);

                prebuildButtons.push_back(prebuildBtn);
            }
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

    void update(sf::Vector2f mousePos,sf::Vector2f gameMousePos,std::vector<std::vector<Block>> &blocks,std::vector<Infrastructure *> &infrastructures)
    {
        for (auto &prebuildButton : prebuildButtons)
        {
            prebuildButton->update(mousePos,gameMousePos,blocks,infrastructures);
        }
    }
};

#endif