#ifndef BOXSELECTION__H
#define BOXSELECTION__H


#include <SFML/Graphics.hpp>
#include <vector>
#include "infrastructure.h"

class BoxSelection
{
public:
    BoxSelection()
    {
        isDragging = false;
        selectionRect.setFillColor(sf::Color(0, 0, 255, 50)); 
        selectionRect.setOutlineColor(sf::Color::Blue);
        selectionRect.setOutlineThickness(1);
    }

    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            isDragging = true;
            dragStartPos = mousePos;
            dragCurrentPos = mousePos;
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            isDragging = false;
            selectionBounds = getSelectionBounds();
        }
    }

    void update(const sf::Vector2f& mousePos)
    {
        if (isDragging)
        {
            dragCurrentPos = mousePos;
            sf::Vector2f size = dragCurrentPos - dragStartPos;
            selectionRect.setPosition(std::min(dragStartPos.x, dragCurrentPos.x), std::min(dragStartPos.y, dragCurrentPos.y));
            selectionRect.setSize(sf::Vector2f(std::abs(size.x), std::abs(size.y)));
        }
    }

    void draw(sf::RenderWindow& window)
    {
        if (isDragging)
        {
            window.draw(selectionRect);
        }
    }

    std::vector<Infrastructure*> getSelected(const std::vector<Infrastructure>& infrastructures)
    {
        std::vector<Infrastructure*> selected;
        for (auto& infra : infrastructures)
        {
            if (selectionBounds.intersects(infra.rectRender.getGlobalBounds()))
            {
                selected.push_back(const_cast<Infrastructure*>(&infra)); 
            }
        }
        return selected;
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
            std::min(dragStartPos.x, dragCurrentPos.x),
            std::min(dragStartPos.y, dragCurrentPos.y),
            std::abs(dragCurrentPos.x - dragStartPos.x),
            std::abs(dragCurrentPos.y - dragStartPos.y)
        );
    }
};

#endif