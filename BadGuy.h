#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Bullet.h"
#include "Game.h"

class BadGuy : public MoveableThing
{
public:
	BadGuy(sf::RenderWindow& win, std::string name, double startX, double startY);
	~BadGuy();
	void takeTurn(void);
	void display(void);
	bool move(double dx, double dy);
	void  hit(MoveableThing& hitBy) {
		hitBy.takeDamage(10);
		try {
			dynamic_cast<Bullet&>(hitBy);
		}
		catch (std::bad_cast) {
			return;	// not a bullet
		}
		takeDamage(100);
	};

	int getHealth() const
	{
	    return health;
	};
	void takeDamage(int damage) {
        health -= damage;
        std::cout << "Badguy takes " << damage << "damage. Health is now " << health << std::endl;
		if (health <= 0)
			Game::getInstance().deregisterObject(this);
	};
	bool getAttacked(){
		return false;
	};
	bool resetAttacked() {
		return false;
	};

private:
	const int sizeX = 62;
	const int sizeY = 75;

	std::string name;
	int maxHealth = 100;
	int health = 100;
	int weaponDamage = 10;
	sf::Sprite bgImage;

};

