#pragma once
#include <string>
#include <stdio.h>
#include <iomanip>
#include <list>
#include "SFML/Graphics.hpp"
#include "Room.h"


class Level
{
private:
	Room* generateRoom(void);
	Room* generateRoom(Room* connection, Door* newDoor);

	void populate(Room* rm);
	static std::string levelDirectory;
	sf::RenderWindow& window;
	std::list<Room*> rooms;
	Room* entry = nullptr;	// this is where you start!
	Room* exit = nullptr; // room to next level
	int level;
	static float maxX, maxY;

public:
	Level(sf::RenderWindow& win, int lvl);
	Level(sf::RenderWindow& win, std::string filename);
	~Level();
//	void enter(Player& me);
	Room* getEntry(void) { return entry; };

};

