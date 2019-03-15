// Demonstrate primitve drawing in SFML

#include "SFML/Graphics.hpp"
#include <stdio.h>
#include "Game.h"

using namespace std;

int main(int argc, char ** argv) {
	Game &game = Game::getInstance();
	game.play();
}
