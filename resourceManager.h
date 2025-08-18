#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>

class ResourceManager
{
public:
    int resource;
    int increaseRate;
    sf::Clock clock;
    float elapsedTime = 0.f;
    float updateInterval = 1.f;
    
    ResourceManager()
    {
        resource = increaseRate = 10;
    }

    void increaseResource(int value)
    {
        resource += value;
    }

    bool canSpend(int cost)
    {
        if (resource < cost)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void spend(int cost)
    {
        resource -= cost;
    }

    void update()
    {
        float deltaTime = clock.restart().asSeconds();
        elapsedTime += deltaTime;

        if (elapsedTime >= updateInterval)
        {
            resource += increaseRate;
            elapsedTime -= updateInterval;
        }
    }
};

#endif