#pragma once
#include <string>
#include <stdio.h>
#include <iomanip>
#include "SFML/Graphics.hpp"

class Level
{
private:
	static std::string levelDirectory;
	sf::RenderWindow& window;

public:
	Level(sf::RenderWindow& win, int lvl);
	Level(sf::RenderWindow& win, std::string filename);
	~Level();
};

