#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button
{
public:
    sf::Vector2f pos;
    sf::RectangleShape renderer;

    Button(sf::Vector2f position, sf::Vector2f size,sf::Color color)
        : pos(position)
    {
        renderer.setSize(size);
        renderer.setPosition(pos);
        renderer.setOrigin({size.x / 2.f, size.y / 2.f});
        renderer.setFillColor(color); 
    }

    bool isPressed(sf::Vector2f mousePos)
    {
        sf::FloatRect bounds = renderer.getGlobalBounds();
        if (bounds.contains(mousePos) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(renderer);
    }
};

#endif