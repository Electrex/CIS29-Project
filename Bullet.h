#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"

class Bullet :
	public MoveableThing
{
public:
	Bullet(sf::RenderWindow& win);
	~Bullet();
	void takeTurn(void);
};

