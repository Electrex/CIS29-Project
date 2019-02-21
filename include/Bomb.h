#ifndef BOMB_H
#define BOMB_H

#include <SFML\Graphics.hpp>
#include "Bullet.h"

class Invaders;  // forward declaration

const sf::Vector2f BombSize{12.0f,24.0f};
extern sf::Texture BombTexture;
extern const sf::Vector2u NumInvaders;

class Bomb : public sf::RectangleShape
{
public:
    Bomb(int imageIndex = 4);
    void moveBombToStartPosition(const Invaders& invaders);
    bool move();
    bool hitByBullet(Bullet& bullet);
protected:

private:
    int imageIndex;
    sf::Vector2f position;
};

#endif // BOMB_H
