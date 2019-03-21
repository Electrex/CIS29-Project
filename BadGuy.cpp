#include "BadGuy.h"
#include "Game.h"
#include <iostream>
#include <stdio.h>
#include <time.h>

std::random_device BadGuy::rd1;
std::random_device BadGuy::rd2;
static int numTurnsBeforeAction = 100;
static int currNumTurms = 0;
int newX = 0;
int newY = 0;

BadGuy::BadGuy(sf::RenderWindow& win, std::string name, double startX, double startY) : MoveableThing(win)
{
		x1 = startX;		// wherever we want the player to be
		y1 = startY;		// wherever we want the player to be
		x2 = startX+sizeX;		// diagonal for hit calculation
		y2 = startY+sizeY;		// diagonal for hit calculation


		this->name = name;

		//	if (!image.loadFromFile("player.png", sf::IntRect(0, 0, 62, 75)))	// this .png has multiple frames for animation
		//		cerr << "Error could not load player image" << endl;

		if (!image.loadFromFile("../badguy.png")) {				// changing to match how the download from git is structured - JW

			std::cerr << "Error could not load player image" << std::endl;
		}

		image.createMaskFromColor(sf::Color::White, 0);
		texture.loadFromImage(image, sf::IntRect(0, 0, sizeX, sizeY));
		bgImage.setTexture(texture);
		bgImage.setPosition(static_cast<float>(x1), static_cast<float>(y1));

}


BadGuy::~BadGuy()
{
//	Game::getInstance().deregisterObject(this);
}

void BadGuy::takeTurn()
{
    if (currNumTurms % numTurnsBeforeAction == 0)
    {
        currNumTurms++;
        //std::mt19937 gen1(rd1());
//		std::mt19937 gen2(rd2());
		std::uniform_int_distribution<> dis1(0, 3);
		std::uniform_int_distribution<> dis2(100, 400);


		int movecount = dis2(rd2 /*gen2*/);
		int distance = 7;
		int direction = dis1(rd1 /*gen1*/);	// 0=south, 1=north, 2=east, 3=west


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
			movecount = dis2(rd2 /*gen2*/);
			direction = dis1(rd1 /*gen1*/);
		}

		else
			--movecount;
    } else
    {
        this->move(newX, newY);
        currNumTurms++;
    }


}

bool BadGuy::move(double dx, double dy) {
		if (health <= 0)
        {
            std::cout << "BadGuy is dead" << std::endl;
        }

	if(resolveCollisions(x1+dx, y1+dy, x2+dx, y2+dy)) {

		x1 += dx;
		x2 += dx;
		y1 += dy;
		y2 += dy;

		bgImage.setPosition(static_cast<float>(x1), static_cast<float>(y1));

		return true;
	}
	return false;
}

void BadGuy::display(void) {
	window.draw(bgImage);
}

