#ifndef PREBUILD_H
#define PREBUILD_H

#include <SFML/Graphics.hpp>
#include "button.h"
#include "grid.h"
#include "cmath"

class PrebuildManager
{
public:
    Button button;
    sf::RectangleShape previewBlock;
    bool prebuilding = false;

    PrebuildManager(sf::Vector2f position, sf::Vector2f size, sf::Color color) : button(position, size, color)
    {
        previewBlock.setSize({blockSize - borderWidth, blockSize - borderWidth});
        previewBlock.setFillColor(sf::Color::Yellow);
    };

    void update(sf::Vector2f gameMousePos)
    {
        if (button.isPressed(gameMousePos))
        {
            prebuilding = true;
            button.renderer.setFillColor(sf::Color::Red);
        }

        if (prebuilding)
        {
            int col = static_cast<int>(floor(gameMousePos.x / blockSize));
            int row = static_cast<int>(floor(gameMousePos.y / blockSize));
            float snappedX = col * blockSize;
            float snappedY = row * blockSize;
            previewBlock.setPosition({snappedX, snappedY});
        }
    };

    void drawPreview(sf::RenderWindow &window)
    {
        if (prebuilding)
        {
            window.draw(previewBlock);
        }
    };

    void drawUI(sf::RenderWindow &window)
    {
        button.draw(window);
    };
};

#endif