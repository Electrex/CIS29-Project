#include <cmath>
#include "Gun.h"

Gun::Gun()
    : gun(GunTexture),
      position(sf::Vector2f(MainWindowWidth / 2.0f, 0.96f * MainWindowHeight)),
      gunSpeed(15.0f),
      visible(true)
{
    gun.setPosition(position);
    gun.setOrigin(gun.getLocalBounds().width/2.0f,gun.getLocalBounds().height / 2.0f);
  //  moveToStartPosition();
}
/*
void Gun::moveToStartPosition()
{
    position = sf::Vector2f(MainWindowWidth / 2.0f, 0.96f * MainWindowHeight);
    gun.setPosition(position);
}
*/
void Gun::moveToPosition(sf::Vector2f pos)
{
    position = pos;
    gun.setPosition(pos);
}

void Gun::move(Direction dir)
{
    if (dir == Right)
    {
        // if the gun is on the right edge, disallow move
        if (position.x < MainWindowWidth - size().x)
            position.x += gunSpeed;
    }
    if (dir == Left)
    {
        // if the gun is on the left edge, disallow move
        if (position.x > size().x)

            position.x -= gunSpeed;
    }
    gun.setPosition(position);
}

Bullet* Gun::shoot() const
{
    // Get gun location
    sf::Vector2f gunBarrelEnd = sf::Vector2f(position.x - 1.5f,position.y - (size().y / 1.5f));
    return new Bullet(gunBarrelEnd);
}

bool Gun::hitByBomb(Bomb& bomb)
{
    bool hit;
    // std::cout << position.y << ' ' << bomb.getPosition().y << ' ' << size().y << ' ' <<  bomb.getSize().y << ' ' << (size().y + bomb.getSize().y) / 2.0f << std::endl;
    if ((position.y - bomb.getPosition().y) > ((size().y + bomb.getSize().y) / 2.0f))
        return false;
    float diffX = fabs(position.x - bomb.getPosition().x);
    float diffY = fabs(position.y - bomb.getPosition().y);
    hit = std::sqrt(diffX * diffX + diffY * diffY) < (size().x + BombSize.x) / 2.0f;
    if (hit) visible = false;
    return hit;
}
/*
void Gun::moveToSpareLocation(int locationNum)
{
    if (visible) gun.setPosition(sf::Vector2f(760.0f+75.0f*locationNum,30.0f));
}
*/
