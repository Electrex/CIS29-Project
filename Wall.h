#pragma once
#include "StaticThing.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

class Wall :
	public StaticThing
{
public:
	Wall(sf::RenderWindow &win, int x1, int x2,int y1, int y2);
	~Wall();
	void display(void);
private:
	sf::RectangleShape rectangle;
};

