#include "StaticThing.h"
#include "Game.h"


StaticThing::StaticThing(sf::RenderWindow& win) : Thing(win)
{

}


StaticThing::~StaticThing()
{
}

bool StaticThing::resolveCollisions(int x, int y)
{
	return Game::getInstance().resolveCollisions(x, y, *this);
}

bool StaticThing::resolveCollisions(double x1, double y1, double x2, double y2)
{
	return Game::getInstance().resolveCollisions(x1, y1, x2, y2, *this);
}
