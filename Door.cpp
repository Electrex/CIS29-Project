#include "Door.h"
#include "Game.h"



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

void Door::takeTurn(void) {
	// do something
}
