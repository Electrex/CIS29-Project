#include "Game.h"
#include "Wall.h"
#include "BadGuy.h"
using namespace std;

Game* Game::thisInstance = nullptr;

Game& Game::getInstance(void) {
	if (!thisInstance)
		thisInstance = new Game();
	return *thisInstance;
}

void Game::bumpSound(void) {
	sfsound.setBuffer(bumpBuffer);
	sfsound.play();
}

Game::Game() : window(sf::VideoMode(800, 600), "Demo Game"), curLevel(window, baseFilename + "1"), player(window, "Player")
{
	if (!soundBuffer.loadFromFile("bgmusic.wav")) {
		cerr << "Cannot load background music" << endl;
	}
	else {
		sound.setBuffer(soundBuffer);
		sound.setLoop(true);
		sound.play();
	}
	if (!bumpBuffer.loadFromFile("hit.wav")) {
		cerr << "Cannot load hit sound effect" << endl;
	}
	else {
		sound.setBuffer(soundBuffer);
		sound.setLoop(true);
		sound.play();
	}

	window.setFramerateLimit(FPS);
	baseFilename = "";
	registerObject(&player);
	// for testing
	Wall *tmpwall = new Wall(window, 100, 100, 500, 110);
	registerObject(tmpwall);
	tmpwall = new Wall(window, 100, 100, 110, 500);
	registerObject(tmpwall);
	tmpwall = new Wall(window, 100, 500, 510, 510);
	registerObject(tmpwall);
	tmpwall = new Wall(window, 500, 100, 510, 500);
	registerObject(tmpwall);
	tmpwall = new Wall(window, 300, 300, 500, 310);
	registerObject(tmpwall);
	BadGuy *bg = new BadGuy(window, "Orc", 200, 200);
	registerObject(bg);
};

Game::Game(string filename) : window(sf::VideoMode(800, 600), "Demo Game"), curLevel(window, baseFilename+"1"), player(window, "Player") {
	baseFilename = filename;


};

void Game::registerObject(StaticThing *thing) {
	updateStaticObjects.push_back(thing);
}

bool Game::resolveCollisions(int x, int y, MoveableThing & me)
{
	for (auto it = updateStaticObjects.begin(); it != updateStaticObjects.end(); ++it) {
		if ((*it)->isAtLocation(x, y)) {
			bumpSound();
			// collision, so don't move here for static objects
			return false;
		}
	}
	for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {
		if(((*it) != &me) && ((*it)->isAtLocation(x, y))) {
			bumpSound();
			(*it)->hit(me);
			return false;
		}
	}

	return true;
}

void Game::registerObject(MoveableThing *thing) {
	updateMoveableObjects.push_back(thing);
}

int Game::play(void) {

	sf::Event event;

	view.setCenter(player.getX(), player.getY());
	window.setView(view);
	//InputManager input(player, playerSprite, view, window);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}

		window.clear();
		for(auto it=updateStaticObjects.begin(); it!= updateStaticObjects.end(); ++it) {
			(*it)->display();
		}
		for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {
			(*it)->takeTurn();
			(*it)->display();
		}
		player.takeTurn();
		view.setCenter(player.getX(), player.getY());
		window.setView(view);
		window.display();
	}
	return 0;
};


Game::~Game()
{
};
