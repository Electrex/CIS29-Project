#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
class BadGuy :
	public MoveableThing
{
public:

	BadGuy(sf::RenderWindow& win, std::string name, int startX, int startY);
	~BadGuy();
	void takeTurn(void);
	void display(void);
	bool move(float dx, float dy);
	void  hit(MoveableThing& hitBy) {
		hitBy.takeDamage(10);
	}

private:
	const int sizeX = 62;
	const int sizeY = 75;
	std::string name;
	int maxHealth = 100;
	int health = 100;
	int weaponDamage = 10;
	sf::Sprite bgImage;

};

