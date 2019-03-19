#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"

class Room;

class Door :
	public MoveableThing
{
public:
//	Door(sf::RenderWindow &win, Room* firstRoom, Room* secondRoom, bool open=true, bool locked=false, bool last=false);
	Door(sf::RenderWindow& win);
	~Door();
	bool connectRooms(Room* rm1, Room* rm2, double x1, double y1, double x2, double y2);
	bool open();
	bool unlock();
	bool close();
	bool lock();
	bool isOpen(void) { return _isOpen; };
	bool isLocked(void) { return _isLocked; };
	void takeTurn(void);
	bool isAtLocation(double x, double y);
	bool isAtLocation(double x1, double y1, double x2, double y2);
	bool isOpenAtLocation(double x1, double y1, double x2, double y2);
	bool isLastofLevel;
	void display(void);
private:
	bool _isOpen;
	bool _isLocked;
//	Wall *firstWall = nullptr;
//	Wall *secondWall = nullptr;
	Room* firstRoom;
	Room* secondRoom;
	sf::RectangleShape rectangle;

};

