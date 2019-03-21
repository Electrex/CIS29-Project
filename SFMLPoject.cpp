// Demonstrate primitve drawing in SFML

#include "SFML/Graphics.hpp"
#include <stdio.h>
#include "Game.h"
#include "NotificationWindow.h"
#include <string>

using namespace notify;

const char* startscreen = "../splash.png";
const char* endscreen = "../gameover.png";
const char* startbutton = "../button.png";
const char* endbutton = "../exit.png";

int main(int argc, char ** argv) {
	NotificationWindow win("Welcome to Red Hot Miami!", "OK", startscreen, startbutton);
	Game &game = Game::getInstance();
	game.play();
	NotificationWindow win2("Sorry you Lost the Game. You reached level " + std::to_string(game.getLevel()), "OK", endscreen, endbutton);
	}
