#pragma once
#include <string>
#include <stdio.h>
#include "Level.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
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
	bool resolveCollisions(int x, int y, MoveableThing& me);


private:
	std::list<MoveableThing*> updateMoveableObjects;
	std::list<StaticThing*> updateStaticObjects;
	std::string baseFilename;
	sf::RenderWindow window;
	sf::View view = sf::View(sf::FloatRect(0.f, 0.1f, 800.f, 600.f));
	Level curLevel;
	Player player;
	static Game* thisInstance;
};

