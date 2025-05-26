#ifndef GRID__H
#define GRID__H

#include <SFML/Graphics.hpp>

const int blockSize = 50;
const int borderWidth = 4;
const int gridRow = 20;
const int gridColumn = 20;

const std::vector<std::vector<int>> map = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

const sf::Color lightGray(200, 200, 200);

enum BlockOccupy
{
    Road,
    Building,
    Empty
};

enum InfrastructureName
{
    YellowTower,
    CommandCenter,
    Mine
};

class Block
{
public:
    int row;
    int column;
    BlockOccupy occupy;
    sf::RectangleShape rectRender;
};

class Infrastructure
{
public:
    int health;
    std::string name;
    int posR;
    int posC;
    int sizeR;
    int sizeC;
    sf::RectangleShape rectRender;
};

void initGrid(std::vector<std::vector<Block>> &blocks, const int gridRow, const int gridColumn, const int blockSize)
{
    blocks.resize(gridRow);
    for (auto &row : blocks)
    {
        row.resize(gridColumn);
    }
    for (int row = 0; row < gridRow; ++row)
    {
        for (int col = 0; col < gridColumn; ++col)
        {
            blocks[row][col].row = row;
            blocks[row][col].column = col;
            blocks[row][col].rectRender.setSize(sf::Vector2f(blockSize, blockSize));
            blocks[row][col].rectRender.setOutlineThickness(0);
            blocks[row][col].rectRender.setOutlineColor(sf::Color::Black);
            if (map[row][col] == 0)
            {
                blocks[row][col].rectRender.setFillColor(lightGray);
                blocks[row][col].occupy = Empty;
            }
            else if (map[row][col] == 1)
            {
                blocks[row][col].rectRender.setFillColor(sf::Color::Red);
                blocks[row][col].occupy = Building;
            }
            else if (map[row][col] == 2)
            {
                blocks[row][col].rectRender.setFillColor(sf::Color::White);
                blocks[row][col].occupy = Road;
            }
            float x = col * blockSize;
            float y = row * blockSize;
            blocks[row][col].rectRender.setPosition(x, y);
        }
    }
}

// activate/deactivate grid lines
void gridPrebuilding(std::vector<std::vector<Block>> &blocks, const int gridRow, const int gridColumn, bool on)
{
    if (on)
    {
        for (int row = 0; row < gridRow; ++row)
        {
            for (int col = 0; col < gridColumn; ++col)
            {

                blocks[row][col].rectRender.setOutlineThickness(borderWidth);
            }
        }
    }
    else
    {
        for (int row = 0; row < gridRow; ++row)
        {
            for (int col = 0; col < gridColumn; ++col)
            {

                blocks[row][col].rectRender.setOutlineThickness(0);
            }
        }
    }
}

void setInfrastructure(InfrastructureName target, int rowPos, int colPos, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure> &infrastructures)
{
    if (target == YellowTower)
    {
        Infrastructure yTower;
        yTower.health = 10;
        yTower.name = "YellowTower";
        yTower.sizeR = yTower.sizeC = 1;
        yTower.posR = rowPos;
        yTower.posC = colPos;

        yTower.rectRender.setSize(sf::Vector2f(blockSize, blockSize));
        yTower.rectRender.setFillColor(sf::Color::White);

        float x = colPos * blockSize;
        float y = rowPos * blockSize;
        yTower.rectRender.setPosition(x, y);
        yTower.rectRender.setFillColor(sf::Color::Yellow);
        infrastructures.push_back(yTower);
    }
}

bool JudgeCanBuildHere(const std::vector<std::vector<Block>> &blocks, int row, int col)
{
    if (row < 0 || row >= gridRow || col < 0 || col >= gridColumn)
    {
        return false;
    }

    if (blocks[row][col].occupy != Empty)
    {
        return false;
    }

    return true;
}


#endif