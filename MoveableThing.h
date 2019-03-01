#pragma once
#include "Thing.h"

#include "SFML/Graphics.hpp"

class MoveableThing :
	public Thing
{
public:
	MoveableThing(sf::RenderWindow& win);
	~MoveableThing();
	virtual void takeTurn(void);
	bool move(int deltaX, int deltaY);
	bool resolveCollisions(int x, int y);

};

