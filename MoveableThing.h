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
	bool move(float deltaX, float deltaY);
	bool resolveCollisions(int x, int y);

// protected:
//	Game& game;
};

