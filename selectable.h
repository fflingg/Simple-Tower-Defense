#ifndef SELECTABLE_H
#define SELECTABLE_H

#include <SFML/Graphics.hpp>

class Selectable {
public:
    virtual ~Selectable() = default;

    virtual sf::FloatRect getGlobalBounds() const = 0;

    virtual void setSelected(bool selected) = 0;

    virtual bool isSelected() const = 0;
};


#endif