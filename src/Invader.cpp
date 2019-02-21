#include "Invader.h"

Invader::Invader()
    : sf::RectangleShape(InvaderSize), status(Visible), explosionCount(0U)
{
    setOrigin(getLocalBounds().width/2.0f,getLocalBounds().height / 2.0f);
}

Invader::~Invader()
{ }
