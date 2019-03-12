#include "BadGuy.h"
#include <iostream>
#include <random>
#include <stdio.h>
#include <time.h>



BadGuy::BadGuy(sf::RenderWindow& win, std::string name, int startX, int startY) : MoveableThing(win)
{
        srand(time(0));
		x1 = startX;		// wherever we want the player to be
		y1 = startY;		// wherever we want the player to be
		x2 = startX+sizeX;		// diagonal for hit calculation
		y2 = startX+sizeY;		// diagonal for hit calculation

		this->name = name;

		//	if (!image.loadFromFile("player.png", sf::IntRect(0, 0, 62, 75)))	// this .png has multiple frames for animation
		//		cerr << "Error could not load player image" << endl;
		if (!image.loadFromFile("../badguy.png")) {				// changing to match how the download from git is structured - JW
			std::cerr << "Error could not load player image" << std::endl;
		}

		image.createMaskFromColor(sf::Color::White, 0);
		texture.loadFromImage(image, sf::IntRect(0, 0, sizeX, sizeY));
		bgImage.setTexture(texture);
		bgImage.setPosition(x1, y1);

};


BadGuy::~BadGuy()
{
}

void BadGuy::takeTurn()
{
		static std::random_device rd1;
		static std::random_device rd2;
		std::mt19937 gen1(rd1());
		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<> dis1(0, 3);
		std::uniform_int_distribution<> dis2(1, 5);

		static int movecount = dis2(gen2);
		static int distance = 1;
		static int direction = dis1(gen1);	// 0=south, 1=north, 2=east, 3=west
		std::cout << "Direction: " << direction << std::endl;
		int newX, newY;


		switch (direction) {
		case 0: {
			newX = 0;
			newY = distance;
			break;
		}
		case 1: {
			newX = 0;
			newY = -distance;
			break;
		}
		case 2: {
			newX = distance;
			newY = 0;
			break;
		}
		case 3: {
			newX = -distance;
			newY = 0;
			break;
		}
		}


		if ((!this->move(newX, newY)) || movecount == 0) {
			movecount = dis2(gen2);
			direction = dis1(gen1);
		}
};

bool BadGuy::move(float dx, float dy) {
	if (resolveCollisions(((x1 + x2) / 2) + dx, ((y1 + y2) / 2) + dy)) {
		x1 += dx;	// From Julie: I think we should have the caller multiply
		x2 += dx;	// instead of multiplying inside the functions
		y1 += dy;
		y2 += dy;
		bgImage.setPosition(x1, y1);

		return true;
	}
	return false;
}

void BadGuy::display(void) {
	window.draw(bgImage);
}
