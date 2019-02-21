#ifndef SAUCER_H
#define SAUCER_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Bullet.h"

extern sf::Texture SaucerTexture;


class Saucer : public sf::Sprite
{
public:
    enum Direction {East, West};
    Saucer();
    sf::Vector2f size() const
    {
        return sf::Vector2f(getLocalBounds().width * getScale().x, getLocalBounds().height * getScale().y);
    }
    bool move();
    bool hitByBullet(const Bullet& bullet) const;

private:
    Direction direction;
};

#endif // SAUCER_H
