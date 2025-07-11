#ifndef BOXSELECTION__H
#define BOXSELECTION__H

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "infrastructure.h"
#include "worker.h"
#include "selectable.h"

class BoxSelection
{
public:
    std::vector<Selectable *> allSelectables;
    std::vector<Selectable *> selectedObjects;
    BoxSelection()
    {
        isDragging = false;
        selectionRect.setFillColor(sf::Color(0, 0, 255, 50));
        selectionRect.setOutlineColor(sf::Color::Blue);
        selectionRect.setOutlineThickness(1);
    }

    void handleEvent(const sf::Event &event, const sf::Vector2f &mousePos)
    {
        if (auto mousePressed = event.getIf<sf::Event::MouseButtonPressed>())
        {
            if (mousePressed->button == sf::Mouse::Button::Left)
            {
                isDragging = true;
                dragStartPos = mousePos;
                dragCurrentPos = mousePos;
            }
        }
        else if (auto mouseReleased = event.getIf<sf::Event::MouseButtonReleased>())
        {
            if (mouseReleased->button == sf::Mouse::Button::Left)
            {                
                isDragging = false;
                if((dragStartPos !=  dragCurrentPos)){
                    selectionBounds = getSelectionBounds();
                    getSelected();
                }
            }
        }
    }

    void update(const sf::Vector2f &mousePos, const std::vector<Infrastructure *> &infrastructures, Workers workers)
    {
        if (isDragging)
        {
            dragCurrentPos = mousePos;
            sf::Vector2f size = dragCurrentPos - dragStartPos;
            selectionRect.setPosition({std::min(dragStartPos.x, dragCurrentPos.x), std::min(dragStartPos.y, dragCurrentPos.y)});
            selectionRect.setSize(sf::Vector2f(std::abs(size.x), std::abs(size.y)));
        }

        // update with all selectables outside
        allSelectables.clear();
        for (auto *infra : infrastructures)
        {
            allSelectables.push_back(static_cast<Selectable *>(infra));
        }
        for (auto *worker : workers.allWorkers)
        {
            allSelectables.push_back(static_cast<Selectable *>(worker));
        }
    }

    void draw(sf::RenderWindow &window)
    {
        if (isDragging)
        {
            window.draw(selectionRect);
        }
    }

    void getSelected()
    {
        selectedObjects.clear();
        for (auto &object : allSelectables)
        {
            if (selectionBounds.findIntersection(object->getGlobalBounds()).has_value())
            {
                object->setSelected(true);
                selectedObjects.push_back(object);
            }
            else
            {
                object->setSelected(false);
            }
        }
    }

    void clearSelection()
    {
        selectionBounds = sf::FloatRect();
    }

private:
    bool isDragging;
    sf::Vector2f dragStartPos;
    sf::Vector2f dragCurrentPos;
    sf::RectangleShape selectionRect;
    sf::FloatRect selectionBounds;

    sf::FloatRect getSelectionBounds() const
    {
        return sf::FloatRect(
            {std::min(dragStartPos.x, dragCurrentPos.x), std::min(dragStartPos.y, dragCurrentPos.y)},
            {std::abs(dragCurrentPos.x - dragStartPos.x), std::abs(dragCurrentPos.y - dragStartPos.y)});
    }
};

#endif
