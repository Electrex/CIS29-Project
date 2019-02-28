#pragma once
#include "SFML/Graphics.hpp"

class Thing
{
public:
	~Thing();
	virtual void display() {};
	Thing(sf::RenderWindow& win);
	virtual bool isAtLocation(int x, int y);
protected:
	int x1, y1;
	int x2, y2;
	int sizeX, sizeY;
	sf::Texture texture;
	sf::Image image;
	sf::RenderWindow &window;
};

