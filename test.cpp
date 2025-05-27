#include <SFML/Graphics.hpp>
#include <vector>
#include "grid.h"
#include "infrastructure.h"
#include "boxSelection.h"

const int parallelResolution = 1920;
const int verticalResolution = 1080;
const float screenMoveSpeed = 1000.f;

int main()
{
    sf::RenderWindow window(sf::VideoMode(parallelResolution, verticalResolution), "test");
    window.setFramerateLimit(60);
    sf::View uiView = window.getDefaultView();
    sf::View gameView = window.getView();

    // UI for prebuilding/////////////////////////////////////////////////////////////////////////////////////
    sf::RectangleShape yellowBlock(sf::Vector2f(150.f, 150.f));                                    ///
    yellowBlock.setFillColor(sf::Color::Yellow);                                                   ///
    yellowBlock.setPosition(0, 1080.f - 200.f);                                                    ///
    bool preBuilding = false;                                                                      ///
    bool isBuilding = false;                                                                       ///
    bool canBuildHere = true;                                                                      ///
    sf::RectangleShape smallBlock(sf::Vector2f(blockSize - borderWidth, blockSize - borderWidth)); ///
    smallBlock.setFillColor(sf::Color::Yellow);                                                    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<Infrastructure*> infrastructures;
    // init the blocks
    std::vector<std::vector<Block>> blocks;
    initGrid(blocks, gridRow, gridColumn, blockSize);

    // get a clock for time-based update
    sf::Clock clock;

    // test an enemy here


    std::vector<Enemy> enemies;
    Enemy testEnemy;
    testEnemy.row = 8;
    testEnemy.col = 19;
    testEnemy.renderer.setRadius(blockSize * 0.4f);
    testEnemy.renderer.setFillColor(sf::Color::Red);
    testEnemy.renderer.setOrigin(testEnemy.renderer.getRadius(), testEnemy.renderer.getRadius());
    enemies.push_back(testEnemy);

    // box selection
    BoxSelection boxSelection;

    /////////////////////////////////////////////////////////////////
    ///////////////////////// update ////////////////////////////////
    /////////////////////////////////////////////////////////////////
    while (window.isOpen())
    {
        // parameters
        float deltaTime = clock.restart().asSeconds();
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), uiView);
        sf::Vector2f gameMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), gameView);
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            boxSelection.handleEvent(event, gameMousePos);

            // adjust the size of the view
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                {
                    float delta = event.mouseWheelScroll.delta;
                    if (delta > 0)
                        gameView.zoom(0.9f);
                    else if (delta < 0)
                        gameView.zoom(1.1f);
                }
            }
        }

        // move the camera by w,a,s,d
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            movement.y -= screenMoveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            movement.y += screenMoveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            movement.x -= screenMoveSpeed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            movement.x += screenMoveSpeed;
        gameView.move(movement * deltaTime);

        // update for boxselection
        boxSelection.update(gameMousePos);
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            boxSelection.getSelected(infrastructures);

            for (auto *infra : boxSelection.selectedInfrastructures)
            {
                infra->activateAttackRangeView = true;
            }
        }

        // activate/deactivate attack range preview
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && !preBuilding)
        {
            bool clickedOnInfrastructure = false;

            for (auto &infra : infrastructures)
            {
                if (infra->rectRender.getGlobalBounds().contains(gameMousePos))
                {
                    infra->activateAttackRangeView = true;
                    clickedOnInfrastructure = true;
                }
                else
                {
                    infra->activateAttackRangeView = false;
                }
            }

            if (!clickedOnInfrastructure)
            {
                for (auto &infra : infrastructures)
                {
                    infra->activateAttackRangeView = false;
                }
            }
        }

        // deal with infrastructure preview ui
        if (yellowBlock.getGlobalBounds().contains(mousePos))
        {
            yellowBlock.setFillColor(sf::Color(200, 200, 0));
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                preBuilding = true;
                isBuilding = false;
            }
        }
        else
        {
            yellowBlock.setFillColor(sf::Color::Yellow);
        }

        // set the position for pre-building
        if (preBuilding)
        {
            canBuildHere = true;
            int col = static_cast<int>(gameMousePos.x) / blockSize;
            int row = static_cast<int>(gameMousePos.y) / blockSize;
            float snappedX = col * blockSize;
            float snappedY = row * blockSize;
            smallBlock.setPosition(snappedX, snappedY);

            gridPrebuilding(blocks, gridRow, gridColumn, true);
            canBuildHere = JudgeCanBuildHere(blocks, row, col);
            // build the infrastructure
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && isBuilding && canBuildHere)
            {
                setInfrastructure(ArrowTowerType, row, col, blocks, infrastructures);
                preBuilding = isBuilding = false;
                gridPrebuilding(blocks, gridRow, gridColumn, false);
            }
            // cancel the pre-building
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                preBuilding = isBuilding = false;
                gridPrebuilding(blocks, gridRow, gridColumn, false);
            }

            isBuilding = true;
        }

        // update for tower attack
        for (auto &infra : infrastructures)
        {
            infra->update(testEnemy);
        }

        // update ends here
        // start render
        window.clear(sf::Color::White);

        // render things that will move
        window.setView(gameView);
        for (const auto &row : blocks)
        {
            for (const auto &block : row)
            {
                window.draw(block.rectRender);
            }
        }

        if (preBuilding)
        {
            window.draw(smallBlock);
        }

        // draw the enemy
        sf::Vector2f enemyPos(testEnemy.col * blockSize + blockSize / 2.f, testEnemy.row * blockSize + blockSize / 2.f);
        testEnemy.renderer.setPosition(enemyPos);
        window.draw(testEnemy.renderer);

        // draw infrastructures
        for (const auto &infrastructure : infrastructures)
        {
            window.draw(infrastructure->rectRender);
            drawAttackRange(window, *infrastructure);
        }

        // draw selection box
        boxSelection.draw(window);

        // render things that won't move
        window.setView(uiView);
        window.draw(yellowBlock);

        window.display();
    }

    return 0;
}