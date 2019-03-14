#pragma once
#include "SFML/Graphics.hpp"

class Thing
{
public:
	~Thing();
	virtual void display() {};
	Thing(sf::RenderWindow& win);
	virtual bool isAtLocation(double x, double y);
protected:
	double x1, y1;
	double x2, y2;
	double sizeX, sizeY;
	sf::Texture texture;
	sf::Image image;
	sf::RenderWindow &window;
};

