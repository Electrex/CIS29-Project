#pragma once
#include "Door.h"
#include "Wall.h"
#include <list>

struct Coords {
	int x1, x2, y1, y2;
};
class Room : public StaticThing
{
public:
	Room(sf::RenderWindow& window, double x1, double y1, double x2, double y2);
//	bool addDoor(sf::RenderWindow& window, Room& connection);
	bool makeLast(void) { isLast = true; return true; }
	bool makeFirst(void) { isFirst = true; return true;  }
	~Room();
	Coords getCoords(void);

protected:
	Wall *getEastWall(void) { return east; };
	Wall *getWestWall(void) { return west; };
	Wall *getNorthWall(void) { return north; };
	Wall *getSouthWall(void) { return south; };

private:
	bool isLast = false;
	bool isFirst = false;
//	std::vector <Door*> exits;
	int exitCount;
	Wall *west, *south, *east, *north;
};

