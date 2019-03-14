#include "Level.h"
#include <random>

float Level::maxX = 1000;
float Level::maxY = 1000;

Level::Level(sf::RenderWindow& win, int lvl=0) : window(win), level(lvl)
{
	// create a random level
	int roomCount = lvl + 2;
	float x1, x2, y1, y2;

	Room* rm = generateRoom();
	entry = rm;
	Room *prevRoom = nullptr;
	rooms.push_front(rm);
	Door *newDoor = nullptr;
	rm->makeFirst();	// let the room know it's the first one of the level
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
	// max room size = 50% of level's total size
	// min room size = 30% of level's total size
	std::random_device rd1, rd2;
	std::mt19937 genX(rd1());
	std::mt19937 genY(rd2());
	std::mt19937 genSize(rd2());

	double maxSize = (maxX < maxY ? maxX : maxY) * 0.5;
	double minSize = (maxX < maxY ? maxX : maxY) * 0.3;

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

Room* Level::generateRoom(Room* connection) { 

	// THIS METHOD ISN'T FINISHED. DO NOT USE //

		// find a good x, y location along connection's wall for the room
	Wall* wall = nullptr;

	std::random_device rd1, rd2;
	std::mt19937 genDir(rd1());
	std::mt19937 genY(rd2());
	std::mt19937 genSize(rd2());

	int maxSize = (maxX < maxY ? maxX : maxY) * 0.1;
	int minSize = maxSize / 2;

	std::uniform_int_distribution<> disDir(0, 3);	// north, south, east, or west wall connection
//	std::uniform_int_distribution<> disY(0, .9*maxY);	// starting Y values
//	std::uniform_int_distribution<> disSize(minSize, maxSize);	// starting Y values

	int x1, y1, x2, y2;
	int dir = disDir(genDir);// 0=south, 1=north, 2=east, 3=west
	x1 = y1 = x2 = y2 = 0;


//	y1 = disY(genY);	
//	x2 = x1 + disSize(genSize);
//	y2 = y1 + disSize(genSize);

	Room *rm = new Room(window, x1, y1, x2, y2);

	return rm;
}

Level::~Level()
{
}

Level::Level(sf::RenderWindow& win, std::string filename) : window(win)
{

}
