#pragma once
#include "Thing.h"
#include "SFML/Graphics.hpp"
class StaticThing :
	public Thing
{
public:
	StaticThing(sf::RenderWindow& win);
	~StaticThing();
};

