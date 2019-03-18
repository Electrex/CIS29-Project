#pragma once
#include <string>
#include <stdio.h>
#include "Level.h"
#include <iostream>
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "MoveableThing.h"
#include "StaticThing.h"
#include <list>

class Game
{
public:
	static Game& getInstance(void);
	Game(std::string filename);	// creates levels from a files, appending lvl number to this base
	Game();							// creates random levels
	~Game();
	int play(void);
	void registerObject(MoveableThing* obj);
	void registerObject(StaticThing* obj);
	void deregisterObject(MoveableThing* obj);
	void deregisterObject(StaticThing* obj);
	bool resolveCollisions(int x, int y, MoveableThing& me);

	bool resolveCollisions(double x1, double y1, double x2, double y2, MoveableThing & me);

	void gameOver(void) {
		std::cout << "You Lost" << std::endl;
		exit(0);	// end the game
	}
	void bumpSound(void);


private:
	const float FPS = 60.0f; // desired update rate
	bool redraw = true;		// do we need to update?
	static sf::Clock clock;

	std::list<MoveableThing*> updateMoveableObjects;
	std::list<StaticThing*> updateStaticObjects;
	std::string baseFilename;
	sf::RenderWindow window;
	sf::View view = sf::View(sf::FloatRect(0.f, 0.1f, 1280.f, 1024.f));
	Level curLevel;
	Player player;
	static Game* thisInstance;
	sf::SoundBuffer soundBuffer;
	sf::SoundBuffer bumpBuffer;
	sf::Sound sound;
	sf::Sound sfsound;
};

