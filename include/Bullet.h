#ifndef BULLET_H
#define BULLET_H
#include <sfml\Graphics.hpp>

//#include "Bomb.h"

class Bullet : public sf::CircleShape
{
    public:
        Bullet(const sf::Vector2f& pos);
        bool move();
};

#endif // BULLET_H
