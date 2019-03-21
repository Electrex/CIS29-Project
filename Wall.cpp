#include "Wall.h"
#include "Game.h"
#include "Door.h"



Wall::Wall(sf::RenderWindow& win, double x1, double y1, double x2, double y2) : StaticThing(win)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	sizeX = abs(x2 - x1);
	sizeY = abs(y2 - y1);
		//	if (!image.loadFromFile("player.png", sf::IntRect(0, 0, 62, 75)))
		//		cerr << "Error could not load player image" << endl;

	rectangle.setFillColor(sf::Color::Red);
	rectangle.setSize(sf::Vector2f(static_cast<float>(sizeX), static_cast<float>(sizeY)));
	rectangle.move(static_cast<float>(x1), static_cast<float>(y1));
}


Wall::~Wall()
{
	for (auto it = doors.begin(); it != doors.end(); ++it)
		Game::getInstance().deregisterObject(*it);

}

void Wall::display(void) {
	window.draw(rectangle);
}

void Wall::addDoor(Door * newDoor)
{
	doors.push_back(newDoor);
}

bool Wall::isAtLocation(double x, double y)	// don't use this one!
{
	return StaticThing::isAtLocation(x,y);	
}

bool Wall::isAtLocation(double x1, double y1, double x2, double y2)
// this is the wall, it will be the door, player is at (x1, y1), (x2, y2)
{
	for (auto it = doors.begin(); it != doors.end(); ++it) {
		if ((*it)->isOpenAtLocation(x1,y1,x2,y2))			// overlaps a door
		{
			if ((*it)->isOpen())
				if (((*it)->getx2() - (*it)->getx1()) > ((*it)->gety2() - (*it)->gety1())) { // horizontal door
					if (((x1 > (*it)->getx1()) && (x1 < (*it)->getx2())) && ((x2 > (*it)->getx1()) && (x2 < (*it)->getx2())))
						return false;
					else
						return true;
				}
				else { // vertical door
					if (((y1 > (*it)->gety1()) && (y1 < (*it)->gety2())) && ((y2 > (*it)->gety1()) && (y2 < (*it)->gety2())))
						return false;
					else
						return true;
				}
			else
				return StaticThing::isAtLocation(x1, y1, x2, y2);
		}
	}
	return StaticThing::isAtLocation(x1, y1, x2, y2);
}

