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

	bool resolveCollisions(double x1, double y1, double x2, double y2);

	virtual void hit(MoveableThing &hitBy);
	virtual bool getAttacked(){};
	virtual bool resetAttacked(){};

	virtual void takeDamage(int damage) {};
};

