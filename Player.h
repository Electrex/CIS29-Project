#pragma once
#include <string>
#include <stdio.h>
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"


class Player : public MoveableThing
{
public:
	Player(sf::RenderWindow & win, std::string name);
	~Player();
	void levelUp(void);
	void takeTurn(void);
	void display(void);
	int getX(void) { return (abs(x1 + x2) / 2); }
	int getY(void) { return (abs(y1 + y2) / 2); }
	bool move(float dx, float dy);
	void hit(MoveableThing& hitBy);
	bool getAttacked()
	{
	    return attacked;
	}
	bool resetAttacked()
	{
	    attacked = false;
	}



private:
	std::string name;
	int maxHealth;
	int health;
	int weaponDamage;
	int exp;
	int expNeeded = 100;	// level up at this xp
	int playerLevel;
	int newX = 0, newY = 0; // make accessible to other members
	sf::Sprite playerImage;
	void testTurn(void);
	void testTurn2(void);
	void takeDamage(int damage);
    sf::Time mDeltaTime;
    sf::Clock mClock;
    sf::Vector2f movement;
    bool attacked = false;

};

