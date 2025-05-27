#ifndef BULLET__H
#define BULLET__H

#include <SFML/Graphics.hpp>
#include "grid.h"

class Enemy
{
public:
    int health;
    std::string name;
    int row;
    int col;
    sf::CircleShape renderer;
    bool alive;
};

class Bullet
{
    int damage;
    sf::CircleShape renderer;
    Bullet(int damage)
    {
        renderer.setRadius(blockSize * 0.2f);
        renderer.setFillColor(sf::Color::Black);
        renderer.setOrigin(renderer.getRadius(), renderer.getRadius());
    }

};

#endif