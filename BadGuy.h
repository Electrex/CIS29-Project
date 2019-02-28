#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
class BadGuy :
	public MoveableThing
{
public:
	BadGuy(sf::RenderWindow win);
	~BadGuy();
	void takeTurn(void);
};

