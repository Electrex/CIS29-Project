#pragma once
#include "StaticThing.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

class Door;

class Wall :
	public StaticThing
{
public:
	Wall(sf::RenderWindow &win, int x1, int y1,int x2, int y2);
	~Wall();
	void display(void);
	void addDoor(Door* newDoor);
	bool isAtLocation(double x, double y);
	bool isAtLocation(double x1, double y1, double x2, double y2);

private:
	sf::RectangleShape rectangle;
	std::vector<Door*> doors;
};

