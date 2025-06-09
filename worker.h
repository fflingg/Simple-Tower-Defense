#ifndef WORKER_H
#define WORKER_H

#include "selectable.h"
#include <cmath>
#include "grid.h"

class Worker : public Selectable
{
public:
    sf::Vector2f pos;
    sf::CircleShape renderer;
    bool selected = false;
    sf::Vector2f targetPos;
    bool isMoving = false;
    float speed = 5.0f;
    sf::CircleShape targetPosRenderer;

    Worker(sf::Vector2f position)
    {
        pos = position;
        renderer.setPosition(pos);
        renderer.setRadius(blockSize * 0.3f);
        renderer.setFillColor(sf::Color::Green);
        renderer.setOrigin({blockSize * 0.3f, blockSize * 0.3f});
    }

    sf::FloatRect getGlobalBounds() const
    {
        return renderer.getGlobalBounds();
    }

    void setSelected(bool isSelected)
    {
        selected = isSelected;
    }

    bool isSelected() const
    {
        return selected;
    }

    void setTargetPosition(const sf::Vector2f &target)
    {
        targetPos = target;
        isMoving = true;
        targetPosRenderer.setPosition(targetPos);
        targetPosRenderer.setRadius(blockSize * 0.3f);
        targetPosRenderer.setFillColor(sf::Color(144, 238, 144)); //light green        
        targetPosRenderer.setOrigin({blockSize * 0.3f, blockSize * 0.3f});
    }

    void update()
    {
        if (isMoving)
        {
            sf::Vector2f direction = targetPos - pos;
            float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

            if (distance < 5.0f)
            {
                pos = targetPos;
                isMoving = false;
            }
            else
            {
                direction /= distance;
                sf::Vector2f movement = direction * speed;

                if (std::abs(movement.x) > std::abs(targetPos.x - pos.x))
                    movement.x = targetPos.x - pos.x;
                if (std::abs(movement.y) > std::abs(targetPos.y - pos.y))
                    movement.y = targetPos.y - pos.y;

                pos += movement;
            }

            renderer.setPosition(pos);
        }

        if (selected)
        {
            renderer.setOutlineColor(sf::Color(0, 100, 0));
            renderer.setOutlineThickness(2.0f);
        }
        else
        {
            renderer.setOutlineThickness(0);
        }
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(renderer);
        window.draw(targetPosRenderer);
    }
};

class Workers
{
public:
    std::vector<Worker *> allWorkers;
    int workerNumber;

    Workers(int number = 4)
    {
        workerNumber = number;
        for (int i = 0; i < workerNumber; ++i)
        {
            allWorkers.push_back(new Worker(sf::Vector2f(30, 30 + 30 * i)));
        }
    }

    void draw(sf::RenderWindow &window)
    {
        for (auto &worker : allWorkers)
        {
            worker->draw(window);
        }
    }

    void update(sf::Vector2f gameMousePos)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            for (auto &worker : allWorkers)
            {
                if (worker->isSelected())
                {
                    worker->setTargetPosition(gameMousePos);
                }
            }
        }

        for (auto &worker : allWorkers)
        {
            worker->update();
        }
    }
};

#endif