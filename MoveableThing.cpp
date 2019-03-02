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

bool MoveableThing::move(float deltaX, float deltaY)
{
	if (resolveCollisions(((x2+x1)/2)+deltaX, ((y2+y1)/2)+deltaY)) {
		x1 += 10*deltaX;		// from Julie: Why times 10?
		x2 += 10*deltaX;
		y1 += 10*deltaY;
		y2 += 10*deltaY;
	}

	return false;
};

bool MoveableThing::resolveCollisions(int x, int y)
{
	return Game::getInstance().resolveCollisions(x, y, *this);
};
