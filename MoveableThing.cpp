#include "MoveableThing.h"
#include "Game.h"



MoveableThing::MoveableThing(sf::RenderWindow& win) : Thing(win)
{
};


MoveableThing::~MoveableThing()
{
};

void MoveableThing::takeTurn(void)
{
};

bool MoveableThing::move(int deltaX, int deltaY)
{
	if (resolveCollisions(((x2+x1)/2)+deltaX, ((y2+y1)/2)+deltaY)) {
		x1 += deltaX;
		x2 += deltaX;
		y1 += deltaY;
		y2 += deltaY;
	}

	return false;
};

bool MoveableThing::resolveCollisions(int x, int y)
{
	return Game::getInstance().resolveCollisions(x, y, *this);
};
