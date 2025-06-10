#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const int parallelResolution = 1920;
const int verticalResolution = 1080;

class textbox
{
public:
    sf::Text text;
    sf::RectangleShape box;
    std::string name;

    textbox() = delete; // illegal

    textbox(const std::string &uiName, const std::string &content, const sf::Font &font, const sf::Vector2f &position, const sf::Vector2f &size) : name(uiName), text(font, content)
    {
        //set box
        box.setSize(size);
        box.setFillColor(sf::Color::Transparent);
        box.setPosition(position);
        box.setOrigin({size.x / 2.f, size.y / 2.f});
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(5.0f);

        //set text
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin({textBounds.position.x + textBounds.size.x / 2.f,
                        textBounds.position.y + textBounds.size.y / 2.f});
        text.setPosition(position);
    }
};

class UI
{
public:
    std::vector<textbox *> allUI;
    sf::Font font;

    UI()
    {
        if(font.openFromFile("./assets/font/MesloLGS NF Regular.ttf")){
            //std::cout << "font loaded" << std::endl;
        }
        sf::Vector2f size(300.f, 100.f); 
        sf::Vector2f position(parallelResolution / 2.f, verticalResolution - size.y / 2.f); 
        
        textbox* bottomBox = new textbox("bottomBox","test", font, position, size);
        allUI.push_back(bottomBox);
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &textbox : allUI)
        {
            window.draw(textbox->text);
            window.draw(textbox->box);
        }
    }
};

#endif