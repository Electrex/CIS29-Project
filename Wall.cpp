#include "Wall.h"
#include "Game.h"



Wall::Wall(sf::RenderWindow& win, int x1, int y1, int x2, int y2) : StaticThing(win)
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
	rectangle.setSize(sf::Vector2f(sizeX, sizeY));
	rectangle.move(x1, y1);

}


Wall::~Wall()
{
}

void Wall::display(void) {
	window.draw(rectangle);
}
