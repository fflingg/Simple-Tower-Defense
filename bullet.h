#ifndef BULLET__H
#define BULLET__H

#include <SFML/Graphics.hpp>
#include "grid.h"
#include <cmath>
#include "enemy.h"

class Bullet
{
public:
    int damage;
    sf::CircleShape renderer;
    sf::Vector2f pos;
    Enemy *target;

    Bullet(int damage, Enemy *enemy, sf::Vector2f position)
    {
        renderer.setRadius(blockSize * 0.2f);
        renderer.setFillColor(sf::Color::Black);
        renderer.setOrigin(renderer.getRadius(), renderer.getRadius());
        target = enemy;
        pos = position;
    }

    void update()
    {
        sf::Vector2f direction = target->pos - pos;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            direction /= length;
            float speed = 5.0f;
            pos += direction * speed;
            renderer.setPosition(pos);
        }
    }
};

#endif