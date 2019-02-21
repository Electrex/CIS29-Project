#include <cstdlib>
#include <iostream>
#include "Explosion.h"

Explosion::Explosion(const std::string& filename)
: exploding(false), count(0)
{
    texture.loadFromFile(filename);
    explosion.setTexture(texture);
    explosion.setOrigin(explosion.getLocalBounds().width/2.0f,explosion.getLocalBounds().height / 2.0f);
}

void Explosion::update()
{
    ++count;
    if (count > 200)
    {
        exploding = false;
    }
    explosion.rotate(90.0f);
}
