#ifndef INFRASTRUCTURE__H
#define INFRASTRUCTURE__H

#include <SFML/Graphics.hpp>
#include <string>
#include "grid.h"
#include "bullet.h"
#include "enemy.h"

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
    sf::Vector2f pos;
    sf::RectangleShape rectRender;
    int attackRange;
    bool activateAttackRangeView = false;
    bool enemyInRange = false;
    vector<Bullet *> bullets;
    float attackInterval;
    sf::Clock attackClock;
    virtual void attackAt(Enemy *target) {};
    virtual void update(std::vector<Enemy *> enemies) {};
    virtual void lateUpdate(std::vector<Enemy *> enemies) {}; // delete bullets aiming at dead enemies
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
        pos = {posC * blockSize + blockSize / 2.f, posR * blockSize + blockSize / 2.f};
        name = "arrow tower";
        health = 100;
        attackInterval = 1.0f;
    }

    void attackAt(Enemy *target)
    {
        if (!target->alive)
        {
            for (Bullet *bullet : bullets)
            {
                delete bullet;
            }
            bullets.clear();
        }
        else
        {
            Bullet *newBullet = new Bullet(10, target, pos);
            bullets.push_back(newBullet);
        }
    }

    void update(std::vector<Enemy *> enemies)
    {
        float elapsed = attackClock.getElapsedTime().asSeconds();
        bool foundEnemyInRange = false;

        for (Enemy *enemy : enemies)
        {
            int dist = abs(posR - enemy->row) + abs(posC - enemy->col);
            if (dist <= attackRange && elapsed >= attackInterval)
            {
                enemyInRange = true;
                rectRender.setFillColor(sf::Color::Red);
                attackAt(enemy);
                attackClock.restart();
                foundEnemyInRange = true;
                break;
            }
        }

        if (!foundEnemyInRange)
        {
            enemyInRange = false;
            rectRender.setFillColor(sf::Color::Yellow);
        }

        for (auto &bullet : bullets)
        {
            bullet->update();
        }
    }

    void lateUpdate(std::vector<Enemy *> enemies)
    {
        for (auto &bullet : bullets)
        {
            if(!bullet->target->alive){
                bullet->active = false;
            }
        }
        for (auto it = bullets.begin(); it != bullets.end();)
        {
            if (!(*it)->active)
            {
                delete *it;
                it = bullets.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
};

// put the infrastructure down
void setInfrastructure(InfrastructureName target, int rowPos, int colPos, std::vector<std::vector<Block>> &blocks, std::vector<Infrastructure *> &infrastructures)
{
    if (target == ArrowTowerType)
    {
        ArrowTower *aTower = new ArrowTower(rowPos, colPos);

        aTower->rectRender.setSize(sf::Vector2f(blockSize, blockSize));
        float x = colPos * blockSize;
        float y = rowPos * blockSize;
        aTower->rectRender.setPosition({x, y});
        aTower->rectRender.setFillColor(sf::Color::Yellow);

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
                    block.setPosition({(float)c * blockSize, (float)r * blockSize});
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