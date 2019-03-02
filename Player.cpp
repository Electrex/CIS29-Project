#include "Player.h"
#include "Game.h"
#include <iostream>
#include <random>
#include <stdio.h>
#include "SFML/Graphics/Color.hpp"

// testing player sprite from http://gaurav.munjal.us/Universal-LPC-Spritesheet-Character-Generator/#?clothes=formal&formal-pants=1&formal-shirt=1&jacket=tabard&weapon=bow&hair=messy1_raven&shoes=boots_metal

using namespace std;

Player::Player(sf::RenderWindow& win, std::string name) : MoveableThing(win)
{
	x1 = 100;		// wherever we want the player to be
	y1 = 100;		// wherever we want the player to be
	x2 = 162;		// diagonal for hit calculation
	y2 = 175;		// diagonal for hit calculation
	sizeX = x2 - x1;
	sizeY = y2 - y1;
	playerLevel = 1;

	this->name = name;
	maxHealth = 10000;
	health = 10000;
	weaponDamage = 10;
	exp = 0;

//	if (!image.loadFromFile("player.png", sf::IntRect(0, 0, 62, 75)))
//		cerr << "Error could not load player image" << endl;
	if (!image.loadFromFile("../player.png")) {
		cerr << "Error could not load player image" << endl;
	}

	image.createMaskFromColor(sf::Color::White, 0);
	texture.loadFromImage(image, sf::IntRect(0,0, sizeX, sizeY));
	playerImage.setTexture(texture);
	playerImage.setPosition(x1, y1);
}


Player::~Player()
{

}

void Player::levelUp(void) {
	maxHealth *= 1.1;	// increase health by 10%
	health = maxHealth;
	weaponDamage *= 1.1;
	exp = 0;
	expNeeded *= 1.1;
	++playerLevel;
}

void Player::testTurn(void) {
	std::random_device rd1, rd2;
	std::mt19937 gen1(rd1());
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution<> dis1(0, 3);
	std::uniform_int_distribution<> dis2(1, 5);

	static int movecount = dis2(gen2);
	static int distance = 10;
	static int direction = dis1(gen1);	// 0=south, 1=north, 2=east, 3=west
	//int newX, newY;

	/*
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
    */
    sf::Vector2f movement(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        --movement.y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        ++movement.y;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        --movement.x;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        ++movement.x;
    if (movement.x != 0.f && movement.y != 0.f)
        movement *= 0.707f;
    //mPlayer.move(movement * mDeltaTime.asSeconds() * 500.f);

    /*
    if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end())
			mActionBinding[found->second]->execute(mPlayer);
	}
	*/
		if ((!this->move(movement.x, movement.y)) || movecount ==0) {
			movecount = dis2(gen2);
//			direction = (direction + 1) % 4;
			direction = dis1(gen1);
		}


};


bool Player::move(float dx, float dy) {
	if (resolveCollisions(((x1+x2)/2) + dx, ((y1+y2)/2)+ dy)) {
		x1 += 10*dx;	// From Julie: I think we should have the caller multiply
		x2 += 10*dx;	// instead of multiplying inside the functions
		y1 += 10*dy;
		y2 += 10*dy;
		playerImage.setPosition(x1,y1);

		return true;
	}
	return false;
}

void Player::takeTurn(void) {
	// do stuff
	this->testTurn();

	if (exp >= expNeeded) {
		this->levelUp();
	}
}

void Player::display(void) {
		window.draw(playerImage);
}
