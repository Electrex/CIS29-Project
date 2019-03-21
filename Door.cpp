#include "Door.h"
#include "Game.h"
#include "Room.h"



/*Door::Door(sf::RenderWindow &win, Room* firstRoom, Room* secondRoom, bool open = true, bool locked = false, bool last = false) : MoveableThing(win), firstRoom(this->firstRoom), secondRoom(this->secondRoom)
{
	if (last)
		isLastofLevel = true;
	Game::getInstance().registerObject(this);
}
*/

Door::Door(sf::RenderWindow& win) : MoveableThing(win)
{
	Game::getInstance().deregisterObject(this);
}


Door::~Door()
{
}

bool Door::open(void)
{
	if (_isLocked == false) {
		_isOpen = true;
//		rectangle.setFillColor(sf::Color::Black);
	}
	return _isOpen;
}

bool Door::unlock(void)
{
	if (!_isOpen) {
		_isLocked = false;
		rectangle.setFillColor(sf::Color::Green);
	}
	return _isLocked;
}

bool Door::close(void)
{
	if (_isOpen) {
		_isOpen = false;
		rectangle.setFillColor(sf::Color::Green);
	}
	return _isOpen;
}

bool Door::lock(void)
{
	if (!_isOpen) {
		_isLocked = true;
		rectangle.setFillColor(sf::Color::Yellow);
	}
	return _isLocked;
}

bool Door::connectRooms(Room * rm1, Room * rm2, double x1, double y1, double x2, double y2)
{
	firstRoom = rm1;
	secondRoom = rm2;
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
	sizeX = x2 - x1;
	sizeY = y2 - y1;

	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setSize(sf::Vector2f(sizeX, sizeY));
	rectangle.move(x1, y1);

	Game::getInstance().registerObject(this);

	return false;
}

void Door::takeTurn(void) {
	// do something
}

bool Door::isAtLocation(double x, double y)
{
	if (!_isOpen)
		return false;
	return MoveableThing::isAtLocation(x, y);
}

bool Door::isAtLocation(double x1, double y1, double x2, double y2)
{
	if (_isOpen)
		return false;
	return MoveableThing::isAtLocation(x1, y1, x2, y2);
}

bool Door::isOpenAtLocation(double x1, double y1, double x2, double y2) {
	if (!_isOpen)
		return false;
	return
		MoveableThing::isAtLocation(x1, y1, x2, y2);
}

void Door::display(void) {
	window.draw(rectangle);
}
