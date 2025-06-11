#ifndef PREBUILD_H
#define PREBUILD_H

#include <SFML/Graphics.hpp>
#include "button.h"
#include "grid.h"
#include "cmath"
#include "infrastructure.h"
#include <iostream>

class PrebuildManager
{
public:
    Button button;
    sf::RectangleShape previewBlock;
    bool prebuilding = false;
    bool isBuilding = false;

    virtual void build(int col, int row, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure *> &infrastructures) = 0;

    PrebuildManager(sf::Vector2f position, sf::Vector2f size, sf::Color color) : button(position, size, color)
    {
        previewBlock.setSize({blockSize - borderWidth, blockSize - borderWidth});
        previewBlock.setFillColor(sf::Color::Yellow);
    };

    void update(sf::Vector2f mousePos, sf::Vector2f gameMousePos, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure *> &infrastructures, sf::FloatRect ui_region)
    {
        if (button.isPressed(mousePos))
        {
            prebuilding = true;
        }

        if (prebuilding)
        {
            int col = static_cast<int>(floor(gameMousePos.x / blockSize));
            int row = static_cast<int>(floor(gameMousePos.y / blockSize));
            float snappedX = col * blockSize;
            float snappedY = row * blockSize;
            previewBlock.setPosition({snappedX, snappedY});

            gridPrebuilding(blocks, gridRow, gridColumn, true);
            bool canBuildHere = JudgeCanBuildHere(blocks, row, col);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && isBuilding && canBuildHere && !ui_region.contains(mousePos))
            {
                build(col, row, blocks, infrastructures);
                prebuilding = isBuilding = false;
                gridPrebuilding(blocks, gridRow, gridColumn, false);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                prebuilding = isBuilding = false;
                gridPrebuilding(blocks, gridRow, gridColumn, false);
            }

            isBuilding = true;
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

class ArrowTower_Prebuild : public PrebuildManager
{
public:
    ArrowTower_Prebuild(sf::Vector2f position, sf::Vector2f size, sf::Color color)
        : PrebuildManager(position, size, color) {}

    void build(int col, int row, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure *> &infrastructures)
    {
        setInfrastructure(ArrowTowerType, row, col, blocks, infrastructures);
    }
};

#endif