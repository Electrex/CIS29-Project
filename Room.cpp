#include "Room.h"
#include "Game.h"




Room::Room(sf::RenderWindow& win, double x1, double y1, double x2, double y2) : StaticThing(win)
{
	north = new Wall(win, x1, y1, x2, y1 + 10);
	south = new Wall(win, x1, y2 - 10, x2, y2);
	west = new Wall(win, x1, y1, x1 + 10, y2);
	east = new Wall(win, x2 - 10, y1, x2, y2);

	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;

	Game::getInstance().registerObject(north);
	Game::getInstance().registerObject(south);
	Game::getInstance().registerObject(east);
	Game::getInstance().registerObject(west);
}



Room::~Room()
{
	Game::getInstance().deregisterObject(north);
	Game::getInstance().deregisterObject(south);
	Game::getInstance().deregisterObject(east);
	Game::getInstance().deregisterObject(west);
}



Coords Room::getCoords(void) {
	Coords c;
	c.x1 = x1;
	c.x2 = x2;
	c.y1 = y1;
	c.y2 = y2;
	return c;
}
