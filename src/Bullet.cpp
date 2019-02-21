#include "Bullet.h"

Bullet::Bullet(const sf::Vector2f& pos)
: sf::CircleShape(2.0f)
{
    setPosition(pos);
    setFillColor(sf::Color::Yellow);
}

bool Bullet::move()
{
    setPosition(getPosition().x, getPosition().y - 1.0f);
    if (getPosition().y < 40.0f) return false;
    return true;
}

