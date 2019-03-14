#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
#include "Room.h"

class Door :
	public MoveableThing
{
public:
//	Door(sf::RenderWindow &win, Room* firstRoom, Room* secondRoom, bool open=true, bool locked=false, bool last=false);
	Door(sf::RenderWindow& win);
	~Door();
	int open() { if (isLocked == false) isOpen = true; return isOpen; };
	int unlock() { if (isLocked == false) return false; isLocked = false; return true; };
	void takeTurn(void);
//	Room* firstRoom;
//	Room* secondRoom;
	bool isLastofLevel;

private:
	bool isOpen;
	bool isLocked;
//	Wall *firstWall = nullptr;
//	Wall *secondWall = nullptr;

};

