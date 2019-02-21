#include <iostream>
#include <cstdlib>
#include "Bomb.h"
#include "Invaders.h"

Bomb::Bomb(int index)
    : sf::RectangleShape(BombSize), imageIndex(index<3?index:rand()%3)
{
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);

    // set texture for bomb
    sf::IntRect bombImageLocationInTexture;
    bombImageLocationInTexture.height = BombSize.y;
    bombImageLocationInTexture.width = BombSize.x;
    bombImageLocationInTexture.left = 0;
    bombImageLocationInTexture.top = imageIndex * BombTexture.getSize().y / 3;
    setTextureRect(bombImageLocationInTexture);
    setTexture(&BombTexture);
}

void Bomb::moveBombToStartPosition(const Invaders& invaders)
{
        int bomberCol = rand() % NumInvaders.y;
    int bomberRow = invaders.getMaxIndexOfVisibleInvaderByColumn(bomberCol);
    if (bomberRow != -1)
        position = sf::Vector2f(invaders.getInvaderPosition(bomberRow,bomberCol));
    else
        position = sf::Vector2f(MainWindowWidth,MainWindowHeight);
    setPosition(position);
}

bool Bomb::move()
{
    if (position == sf::Vector2f(MainWindowWidth,MainWindowHeight))
    {
        return false;
    }

    sf::IntRect bombImageLocationInTexture;
    bombImageLocationInTexture = getTextureRect();
    if (bombImageLocationInTexture.left == 0)
        bombImageLocationInTexture.left = 12;
    else
        bombImageLocationInTexture.left = 0;

    setTextureRect(bombImageLocationInTexture);
    position.y += 0.5f;
    setPosition(position);
    if (position.y > 0.95f * MainWindowHeight)
        return false;
    return true;
}

bool Bomb::hitByBullet(Bullet& bullet)
{
    bool hit;
    if ((position.y - bullet.getPosition().y) > BombSize.y / 2.0f)
        return false;
    float diffX = fabs(position.x - bullet.getPosition().x);
    float diffY = fabs(position.y - bullet.getPosition().y);
    hit = std::sqrt(diffX * diffX + diffY * diffY) < (BombSize.x / 2.0f + 1.0f);
    if (hit) std::cout << "* Bomb hit by bullet" << std::endl;
    return hit;
}

