#ifndef GRID__H
#define GRID__H

#include <SFML/Graphics.hpp>


const int blockSize = 50;
const int borderWidth = 4;
const int gridRow = 20;
const int gridColumn = 20;

const std::vector<std::vector<int>> gridMap = {
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



class Block
{
public:
    int row;
    int column;
    BlockOccupy occupy;
    sf::RectangleShape rectRender;
};

//initialize the gird
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
            if (gridMap[row][col] == 0)
            {
                blocks[row][col].rectRender.setFillColor(lightGray);
                blocks[row][col].occupy = Empty;
            }
            else if (gridMap[row][col] == 1)
            {
                blocks[row][col].rectRender.setFillColor(sf::Color::Red);
                blocks[row][col].occupy = Building;
            }
            else if (gridMap[row][col] == 2)
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