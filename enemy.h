#ifndef ENEMY__H
#define ENEMY__H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include "grid.h"

using VecField = std::vector<std::vector<std::pair<int, int>>>;
using IntField = std::vector<std::vector<int>>;

const float moveInterval = 2.0f;

class Enemy
{
private:
    VecField flowGrid; // initialize once for all

public:
    void move();
    void printFlowGrid() const;
    void update();
    void lateUpdate(); 

    int health;
    std::string name;
    int row;
    int col;
    sf::CircleShape renderer;
    bool alive;
    sf::Vector2f pos;
    sf::Clock moveClock;
};

static std::vector<std::pair<int, int>> probe(int length, int width, int row,
                                              int col)
{
    std::vector<std::pair<int, int>> directions;
    if (row > 0)
    {
        directions.push_back({-1, 0}); // Up
    }
    if (row < length - 1)
    {
        directions.push_back({1, 0}); // Down
    }
    if (col > 0)
    {
        directions.push_back({0, -1}); // Left
    }
    if (col < width - 1)
    {
        directions.push_back({0, 1}); // Right
    }
    return directions;
}

static int calDist(IntField map, int row, int col, int path, int target)
{
    if (map[row][col] == target)
    {
        return 0; // already reached target
    }
    else if (map[row][col] == 0)
    {
        return map.size() * map[row].size(); // not on path
    }
    map[row][col] = 0; // Mark the current cell as empty
    std::vector<std::pair<int, int>> directions =
        probe(map.size(), map[row].size(), row, col);
    int dist = map.size() * map[row].size(); // max distance possible
    for (auto dir : directions)
    {
        int next = map[row + dir.first][col + dir.second]; // next step
        if (next == target)
        {
            return 1; // one step away from target
        }
        else if (next == path)
        { // still on path
            int nextDist = calDist(map, row + dir.first, col + dir.second, path, target);
            dist = nextDist < dist ? nextDist : dist;
        }
        else
        {
            continue; // not on path
        }
    }
    return dist + 1;
}

static std::pair<int, int> calFlow(IntField map, int row, int col)
{
    std::vector<std::pair<int, int>> directions =
        probe(map.size(), map[row].size(), row, col);
    std::vector<int> distances;
    bool hasWayOut = false;
    for (auto dir : directions)
    {
        int dist = calDist(map, row + dir.first, col + dir.second, 2, 1);
        if (dist != map.size() * map[row].size())
        {
            hasWayOut = true;
        }
        distances.push_back(dist);
    }
    if (!hasWayOut)
    {
        return {0, 0}; // No way out
    }
    else
    {
        return directions[std::min_element(distances.begin(), distances.end()) -
                          distances.begin()];
    }
}

VecField calFlowGrid(IntField map)
{
    VecField flowGrid(map.size(),
                      std::vector<std::pair<int, int>>(map[0].size(), {0, 0}));
    for (int r = 0; r < map.size(); r++)
    {
        for (int c = 0; c < map[r].size(); c++)
        {
            if (map[r][c] == 2)
            {
                flowGrid[r][c] = calFlow(map, r, c);
            }
        }
    }
    return flowGrid;
}

void Enemy::move()
{

    std::pair<int, int> direction = flowGrid[row][col];
    row += direction.first;
    col += direction.second;
    pos = {this->col * blockSize + blockSize / 2.f, this->row * blockSize + blockSize / 2.f};
    
}

void Enemy::printFlowGrid() const
{
    std::cout << "Flow Grid:\n";
    for (int i = 0; i < flowGrid.size(); i++)
    {
        for (int j = 0; j < flowGrid[0].size(); j++)
        {
            std::pair<int, int> flow = flowGrid[i][j];
            if (flow == std::make_pair(0, -1))
            {
                std::cout << "<";
            }
            else if (flow == std::make_pair(0, 1))
            {
                std::cout << ">";
            }
            else if (flow == std::make_pair(-1, 0))
            {
                std::cout << "^";
            }
            else if (flow == std::make_pair(1, 0))
            {
                std::cout << "v";
            }
            else
            {
                std::cout << ".";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Enemy::update()
{
    flowGrid = calFlowGrid(gridMap);
    float elapsed = moveClock.getElapsedTime().asSeconds();
    if (elapsed > moveInterval)
    {
        this->move();
        moveClock.restart();
    }
    renderer.setPosition(pos);
    if(health <= 0 ){
        alive = false;
    }
}

void enemyLateUpdate(std::vector<Enemy *> &enemies) {
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!(*it)->alive) {
            delete *it;      
            it = enemies.erase(it);  
        } else {
            ++it;           
        }
    }
}

#endif // ENEMY__H
