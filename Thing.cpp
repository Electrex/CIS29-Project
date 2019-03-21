#include "Thing.h"


Thing::Thing(sf::RenderWindow& win) : window(win)
{
	x1 = x2 = y1 = y2 = sizeX = sizeY = 0;
}

bool Thing::isAtLocation(double x, double y)
{
	if (((x2 >= x1) && ((x<=x2) && (x>=x1))) || ((x2 < x1) && ((x>=x2) && (x<=x1)))) {	// in range of x
		if (((y2 >= y1) && ((y <= y2) && (y >= y1))) || ((y2 < y1) && ((y >= y2) && (y <= y1)))) { // in range of y
			return true;
		}
	}
	return false;
}

bool Thing::isAtLocation(double x1, double y1, double x2, double y2)
{
	// current location is in this->x1, this->y1, this->x2, this->y2
	// checks if the two rectangles overlap at all

		if (x2 < x1) {			// make sure coordinates are in the right order
			std::swap(x2, x1);
			std::swap(y2, y1);
		}

		if (this->x2 < this->x1) {
			std::swap(this->x2, this->x1);
			std::swap(this->y2, this->y1);
		}

		return (( x2 > this->x1) &&
			(y2 > this->y1) &&
			(this->x2 < this->x1 || this->x2 > x1) &&
			(this->y2 < this->y1 || this->y2 > y1));


		return true;
}


Thing::~Thing()
{
}
