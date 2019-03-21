#pragma once
#include "MoveableThing.h"
#include "SFML/Graphics.hpp"
#include "Player.h"
#include <typeinfo>

class Bullet :
	public MoveableThing
{
public:
	Bullet(sf::RenderWindow& win, double startX, double startY, double targetX, double targetY);
	~Bullet();
	void takeTurn(void);
	void display(void);
	bool move(double dx, double dy);
	void hit(MoveableThing& hitBy) {
		try {
			dynamic_cast<Player&>(hitBy);
		}
		catch (std::bad_cast) {
			hitBy.takeDamage(1000);
		}
		// ignore if it was really the player == bullet does not harm player as it launches.
	};

	int getHealth() const
	{
		return 1;
	};
	void takeDamage(int damage) {
		return;
	};
	bool getAttacked() {
		return false;
	};
	bool resetAttacked() {
		return false;
	};

private:
	double targetX = 0;
	double targetY = 0;
	double moveX = 0;
	double moveY = 0;

	sf::CircleShape circle;

};



