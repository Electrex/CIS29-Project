#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
class Door :
	public MoveableThing
{
public:
	Door(sf::RenderWindow &win);
	~Door();
	int open() { if (isLocked == false) isOpen = true; return isOpen; };
	int unlock() { if (isLocked == false) return false; isLocked = false; return true; };
	void takeTurn(void);

private:
	bool isOpen;
	bool isLocked;
};

