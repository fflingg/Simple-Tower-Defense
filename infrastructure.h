#ifndef INFRASTRUCTURE__H
#define INFRASTRUCTURE__H

#include <SFML/Graphics.hpp>
#include <string>
#include "grid.h"

using namespace std;

enum InfrastructureName
{
    ArrowTowerType,
    CommandCenter,
    Mine
};

class Infrastructure
{
public:
    int health;
    string name;
    int posR;
    int posC;
    int sizeR;
    int sizeC;
    sf::RectangleShape rectRender;
    int attackRange;
    bool activateAttackRangeView;
};

class ArrowTower : public Infrastructure
{
public:
    ArrowTower(int rowPos, int colPos)
    {
        posR = rowPos;
        posC = colPos;

        attackRange = 5;
        sizeR = 1;
        sizeC = 1;
        name = "arrow tower";
        health = 100;
        activateAttackRangeView = false;
    }
};

// put the infrastructure down
void setInfrastructure(InfrastructureName target, int rowPos, int colPos, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure> &infrastructures)
{
    if (target == ArrowTowerType)
    {
        ArrowTower aTower(rowPos, colPos);

        aTower.rectRender.setSize(sf::Vector2f(blockSize, blockSize));
        aTower.rectRender.setFillColor(sf::Color::White);
        float x = colPos * blockSize;
        float y = rowPos * blockSize;
        aTower.rectRender.setPosition(x, y);
        aTower.rectRender.setFillColor(sf::Color::Yellow);

        infrastructures.push_back(aTower);

        blocks[rowPos][colPos].occupy = Building;
    }
}

void drawAttackRange(sf::RenderWindow &window, const Infrastructure &infra)
{
    if (infra.activateAttackRangeView)
    {
        for (int r = 0; r < gridRow; ++r)
        {
            for (int c = 0; c < gridColumn; ++c)
            {
                int dist = abs(r - infra.posR) + abs(c - infra.posC);
                if (dist <= infra.attackRange)
                {
                    sf::RectangleShape block;
                    block.setSize(sf::Vector2f(blockSize, blockSize));
                    block.setPosition(c * blockSize, r * blockSize);
                    block.setFillColor(sf::Color(255, 255, 0, 50));
                    block.setOutlineColor(sf::Color::Yellow);
                    block.setOutlineThickness(1);
                    window.draw(block);
                }
            }
        }
    }
}

#endif