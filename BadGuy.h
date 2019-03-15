#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
#include <iostream>
class BadGuy : public MoveableThing
{
public:

	BadGuy(sf::RenderWindow& win, std::string name, int startX, int startY);
	~BadGuy();
	void takeTurn(void);
	void display(void);
	bool move(float dx, float dy);
	void hit(MoveableThing& hitBy) {
		hitBy.takeDamage(10);
		//this->takeDamage(50);
	}
	int getHealth() const
	{
	    return health;
	}
	void takeDamage(int damage) {
        health -= damage;
        std::cout << "Badguy takes " << damage << "damage. Health is now " << health << std::endl;
        //if (health <= 0)
            //dele;
	}
	bool getAttacked(){
	}
	bool resetAttacked(){}

private:
	const int sizeX = 62;
	const int sizeY = 75;
	std::string name;
	int maxHealth = 100;
	int health = 100;
	int weaponDamage = 10;
	sf::Sprite bgImage;

};

