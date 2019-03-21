#pragma once
#include "Door.h"
#include "Wall.h"
#include <list>

struct Coords {
	int x1;
	int x2;
	int y1;
	int y2;
};
class Room : public StaticThing
{
public:
	Room(sf::RenderWindow& window, double x1, double y1, double x2, double y2);

	bool makeLast(void) { isLast = true; return true; }
	bool makeFirst(void) { isFirst = true; return true;  }
	~Room();
	Coords getCoords(void);
	Wall *getEastWall(void) { return east; };
	Wall *getWestWall(void) { return west; };
	Wall *getNorthWall(void) { return north; };
	Wall *getSouthWall(void) { return south; };

private:
	bool isLast = false;
	bool isFirst = false;

	int exitCount;
	Wall *west, *south, *east, *north;
};

