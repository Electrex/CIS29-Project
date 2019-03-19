#pragma once
#include "Thing.h"
#include "SFML/Graphics.hpp"
class StaticThing :
	public Thing
{
public:
	StaticThing(sf::RenderWindow& win);
	~StaticThing();
	bool resolveCollisions(int x, int y);
	bool resolveCollisions(double x1, double y1, double x2, double y2);
};

