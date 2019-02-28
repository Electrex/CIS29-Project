#include "Thing.h"


Thing::Thing(sf::RenderWindow& win) : window(win)
{
	x1 = x2 = y1 = y2 = sizeX = sizeY = 0;
};

bool Thing::isAtLocation(int x, int y)
{
	if (((x2 >= x1) && ((x<=x2) && (x>=x1))) || ((x2 < x1) && ((x>=x2) && (x<=x1)))) {	// in range of x
		if (((y2 >= y1) && ((y <= y2) && (y >= y1))) || ((y2 < y1) && ((y >= y2) && (y <= y1)))) { // in range of y
			return true;
		}
	}
	return false;
};


Thing::~Thing()
{
};
