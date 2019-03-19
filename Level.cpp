#include "Level.h"
#include <random>
#include "Game.h"

float Level::maxX = 10000;
float Level::maxY = 10000;

Level::Level(sf::RenderWindow& win, int lvl=0) : window(win), level(lvl)
{
	// create a random level
	int roomCount = lvl + 2;
	double x1, x2, y1, y2;

	Room* rm = generateRoom();
	entry = rm;
	Room *prevRoom = nullptr;
	rooms.push_front(rm);
	Door *newDoor = new Door(win);
	rm->makeFirst();	// let the room know it's the first one of the level
	Room* rm2 = generateRoom(rm, newDoor);

	/*												//// MULTIPLE ROOMS NOT WORKING YET /////
	for (int i = 1; i < roomCount; ++i) {
		prevRoom = rm;
		rm = generateRoom(prevRoom);
		newDoor = new Door(win, prevRoom, rm);
		rooms.push_front(rm);
	}
	*/
	exit = rm;

	rm->makeLast();	// let the room know it's the end!

};

Room* Level::generateRoom(void) {	// first room
	// max room size = 15% of level's total size
	// min room size = 10% of level's total size
static	std::random_device rd1, rd2;
	std::mt19937 genX(rd1());
	std::mt19937 genY(rd2());
	std::mt19937 genSize(rd2());

	double maxSize = (maxX < maxY ? maxX : maxY) * 0.15;
	double minSize = (maxX < maxY ? maxX : maxY) * 0.10;

	std::uniform_int_distribution<> disX(0, .5*maxX);	// starting X values
	std::uniform_int_distribution<> disY(0, .5*maxY);	// starting Y values
	std::uniform_int_distribution<> disSize(minSize,maxSize);	// starting Y values

	double x1, y1, x2, y2;
	x1 = disX(genX);
	y1 = disY(genY);
	x2 = x1 + disSize(genSize);
	y2 = y1 + disSize(genSize);

	return new Room(window, x1, y1, x2, y2);
}

Room* Level::generateRoom(Room* connection, Door* newDoor) { 

	// THIS METHOD ISN'T FINISHED. DO NOT USE //

		// find a good x, y location along connection's wall for the room
	Wall* wall = nullptr;
	Room *rm = nullptr;

	static std::random_device rd1, rd2, rd3, rd4;
	std::mt19937 genDir(rd1());
	std::mt19937 genOffset(rd2());
//	std::mt19937 genY(rd3());
	std::mt19937 genSize(rd4());

	std::uniform_int_distribution<> disDir(0, 3);	// north, south, east, or west wall connection
	double maxSize = (maxX < maxY ? maxX : maxY) * 0.15;
	double minSize = (maxX < maxY ? maxX : maxY) * 0.10;

	std::uniform_int_distribution<> disSize(minSize, maxSize);	// starting X values
	std::uniform_int_distribution<> disY(0, .5*maxY);	// starting Y values
	std::uniform_int_distribution<> disOffset(20, minSize / 2);

	double x1, y1, x2, y2;
	double doorX1, doorX2, doorY1, doorY2;
	int dir = disDir(genDir);// 0=south, 1=north, 2=east, 3=west
	x1 = y1 = x2 = y2 = 0;

	double offSet = disOffset(genOffset);
	bool found = false;

	for (int i = 0; i < 4; ++i) {
		switch (dir) {
		case 0: {	// try to create a room south of the current room
			doorX1 = (connection->getx1() + (connection->getx2() - connection->getx1())/2 - 80);
			doorX2 = (connection->getx1() + (connection->getx2() - connection->getx1()) / 2 + 80);
			doorY1 = connection->gety2();
			doorY2 = doorY1 + 10;

			x1 = doorX1 - offSet;
			x2 = x1 + disSize(genSize);
			y1 = doorY2;
			y2 = y1 + disSize(genSize);

			if (Game::getInstance().resolveCollisions(x1, y1, x2, y2, *newDoor)) {
				found = true;
				break;
			}
		}
		case 1: { // try to create a room north of the current room
			doorX1 = (connection->getx1() + (connection->getx2() - connection->getx1()) / 2 - 80);
			doorX2 = (connection->getx1() + (connection->getx2() - connection->getx1()) / 2 + 80);
			doorY1 = connection->gety1()-10;
			doorY2 = connection->gety1();

			x1 = doorX1 - offSet;
			x2 = x1 + disSize(genSize);
			y1 = y1 - disSize(genSize);
			y2 = doorY1;

			if (Game::getInstance().resolveCollisions(x1, y1, x2, y2, *newDoor)) {
				found = true;
				break;
			}
		}
		case 2: { // try to create a room east of the current room
			doorX1 = connection->getx2();
			doorX2 = doorX1 + 10;
			doorY1 = (connection->gety1() + (connection->gety2() - connection->gety1()) / 2) - 80;
			doorY2 = (connection->gety1() + (connection->gety2() - connection->gety1()) / 2) + 80;

			x1 = doorX2;
			x2 = x1 + disSize(genSize);
			y1 = doorY1 - offSet;
			y2 = y1 + disSize(genSize);

			if (Game::getInstance().resolveCollisions(x1, y1, x2, y2, *newDoor)) {
				found = true;
				break;
			}		}
		case 3: { // try to create a room west of the current room
			doorX1 = connection->getx1()-10;
			doorX2 = connection->getx1();
			doorY1 = (connection->gety1() + (connection->gety2() - connection->gety1()) / 2) - 80;
			doorY2 = (connection->gety1() + (connection->gety2() - connection->gety1()) / 2) + 80;

			x1 = doorX2 - disSize(genSize);
			x2 = doorX2;
			y1 = doorY1 - offSet;
			y2 = y1 + disSize(genSize);

			if (Game::getInstance().resolveCollisions(x1, y1, x2, y2, *newDoor)) {
				found = true;
				break;
			}
		}
		default: {
		}
		}
		if(!found)
			dir = (dir + 1) % 4;	// try all 4 directions
		if (found) {
			rm = new Room(window, x1, y1, x2, y2);
			
			switch (dir) {
			case 0: {	// new room is south
				newDoor->connectRooms(connection, rm, doorX1, doorY1-10, doorX2, doorY2+10);
				connection->getSouthWall()->addDoor(newDoor);
				rm->getNorthWall()->addDoor(newDoor);
				break;
			}
			case 1: {	// new room is north;
				newDoor->connectRooms(connection, rm, doorX1, doorY1-10, doorX2, doorY2+10);
				connection->getNorthWall()->addDoor(newDoor);
				rm->getSouthWall()->addDoor(newDoor);
				break;
			}
			case 2: {	// new room is east
				newDoor->connectRooms(connection, rm, doorX1-10, doorY1, doorX2+10, doorY2);
				connection->getEastWall()->addDoor(newDoor);
				rm->getWestWall()->addDoor(newDoor);
				break;
			}
			case 3: {	// new room is west
				newDoor->connectRooms(connection, rm, doorX1-10, doorY1, doorX2+10, doorY2);
				connection->getWestWall()->addDoor(newDoor);
				rm->getEastWall()->addDoor(newDoor);
				break;
			}
			default: {
				;
			}
			}
			newDoor->unlock();
			newDoor->open();
			return rm;
		}
	}


	return rm;
}

Level::~Level()
{
}

Level::Level(sf::RenderWindow& win, std::string filename) : window(win)
{

}
