#include "Bullet.h"
#include "Game.h"
#include <iostream>
#include <random>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "SFML/Graphics.hpp"



Bullet::Bullet(sf::RenderWindow& win, double startX, double startY, double targetX, double targetY) : MoveableThing(win), circle(8)
{
	x1 = startX;		// wherever we want the bullet to be
	y1 = startY;		// wherever we want the bullet to be
	x2 = startX + 8;		// diagonal for hit calculation
	y2 = startY + 8;		// diagonal for hit calculation
	sizeX = sizeY = 8;
	this->targetX = targetX;
	this->targetY = targetY;
	double distance = sqrt(((targetY - y1)*(targetY - y1))+((targetX - x1)*(targetX - x1)));
	moveX = (targetX - x1) / distance;
	moveY = (targetY - y1) / distance;

	circle.setFillColor(sf::Color::Red);
	circle.move(static_cast<float>(x1), static_cast<float>(y1));

	Game::getInstance().registerObject(this);
};


Bullet::~Bullet()
{
//	Game::getInstance().deregisterObject(this);
}

void Bullet::takeTurn()
{
	double newX, newY;
	const int distance = 18;

	newX = x1 + moveX * distance;
	newY = y1 + moveY * distance;

//	std::cout << "Bullet moves to: (" << newX << ", " << newY << ")" << std::endl;

	if ((!this->move(newX, newY))) {
		Game::getInstance().deregisterObject(this);
	}
};

bool Bullet::move(double x, double y) {

	if(resolveCollisions(x, y,x+sizeX, y+sizeY)) {

		x1= x;	// From Julie: I think we should have the caller multiply
		x2=x+sizeX;	// instead of multiplying inside the functions
		y1 = y;
		y2=y+sizeY;

		circle.setPosition(static_cast<float>((x2+x1)/2), static_cast<float>((y2+y1)/2));

		return true;
	}
	return false;
}

void Bullet::display(void) {
	window.draw(circle);
}
