#pragma once
#include "SFML/Graphics.hpp"

class Thing
{
public:
	~Thing();
	virtual void display() {};
	Thing(sf::RenderWindow& win);
	virtual bool isAtLocation(double x, double y);
	virtual bool isAtLocation(double x1, double y1, double x2, double y2);
	double getx1(void) { return x1; };
	double getx2(void) { return x2; };
	double gety1(void) { return y1; };
	double gety2(void) { return y2; };
protected:
	double x1, y1;
	double x2, y2;
	double sizeX, sizeY;
	sf::Texture texture;
	sf::Image image;
	sf::RenderWindow &window;
};

