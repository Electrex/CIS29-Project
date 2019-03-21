#include "Game.h"
#include "Wall.h"
#include "BadGuy.h"
#include "Room.h"
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
  if (!soundBuffer.loadFromFile("../bgmusic.wav")) {

		cerr << "Cannot load background music" << endl;
	}
	else {
		sound.setBuffer(soundBuffer);
		sound.setLoop(true);
		sound.play();
	}

  if (!bumpBuffer.loadFromFile("../hit.wav")) {

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

};

Game::Game(string filename) : window(sf::VideoMode(1280, 1024), "Demo Game"), curLevel(window, baseFilename + "1"), player(window, "Player") {
	baseFilename = filename;


};

void Game::registerObject(StaticThing *thing) {
	updateStaticObjects.push_back(thing);
}

void Game::flushObjects(void) {
	while (!deleteObjects.empty()) {
		Thing* myptr;
		auto obj = deleteObjects.begin();
		myptr = *(obj);
		deleteObjects.pop_front();
		if (dynamic_cast<StaticThing*>(myptr) != nullptr) {
			updateStaticObjects.remove(dynamic_cast<StaticThing*>(myptr));
		}
		else {
			updateMoveableObjects.remove(dynamic_cast<MoveableThing*>(myptr));
		}
		delete myptr;
	}
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
		if (((*it) != &me) && ((*it)->isAtLocation(x, y))) {
			bumpSound();
			(*it)->hit(me);
			if (me.getAttacked() == true)
                (*it)->takeDamage(50);
                me.resetAttacked();
			return false;
		}
	}

	return true;
}

bool Game::resolveCollisions(int x, int y, StaticThing & me)
{
	for (auto it = updateStaticObjects.begin(); it != updateStaticObjects.end(); ++it) {
		if (((*it) != &me) && ((*it)->isAtLocation(x,y))) {

			return false;
		}
	}
	for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {
		if ((*it)->isAtLocation(x, y)) {
			return false;
		}
	}

	return true;
}

bool Game::resolveCollisions(double x1, double y1, double x2, double y2, MoveableThing & me)
{
	if (x1 < 0.0 || y1 < 0.0)
		return false;

	bool ignore = false;
	for (auto it = updateStaticObjects.begin(); it != updateStaticObjects.end(); ++it) {

		if ((*it)->isAtLocation(x1, y1, x2, y2)) {
			bumpSound();
			return false;
		}
	}
	for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {
		if (((dynamic_cast<Bullet*>(*it)))!= nullptr) {
			ignore = true;
			try {
				dynamic_cast<Player&>(me);
			}
			catch(std::bad_cast) {
				ignore = false;
			}
		}
		if (((dynamic_cast<Player*>(*it))) != nullptr) {
			ignore = true;
			try {
				dynamic_cast<Bullet&>(me);
			}
			catch (std::bad_cast) {
				ignore = false;
			}
		}

		if (ignore)
			return true;
		if(((*it) != &me) && ((*it)->isAtLocation(x1, y1, x2, y2))) {		
			(*it)->hit(me);
			if (me.getAttacked() == true) {
				bumpSound();
				(*it)->takeDamage(50);
				me.resetAttacked();
			}
			//// test if player
			return false;
		}
	}
	return true;
}

bool Game::resolveCollisions(double x1, double y1, double x2, double y2, StaticThing & me)
{
	for (auto it = updateStaticObjects.begin(); it != updateStaticObjects.end(); ++it) {

		if (((*it) != &me) && ((*it)->isAtLocation(x1, y1, x2, y2))) {
			return false;
		}
	}
	for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {

		if ((*it)->isAtLocation(x1, y1, x2, y2)) {
			return false;
		}
	}

	return true;
}

void Game::registerObject(MoveableThing *obj) {
	updateMoveableObjects.push_back(obj);
}

void Game::deregisterObject(MoveableThing *obj) {
//	updateMoveableObjects.remove(obj);
	if(obj != nullptr)
		deleteObjects.push_back(obj);
}

void Game::deregisterObject(StaticThing *thing) {
//	updateStaticObjects.remove(thing);
	if(thing != nullptr)
		deleteObjects.push_back(thing);
}

int Game::play(void) {

	sf::Event event;

	Level *lvl = new Level(window, 1);
	Coords c = lvl->getEntry()->getCoords();
	player.moveTo((c.x2 + c.x1)/2, (c.y2 + c.y1)/2);	// starts player in center of the room	view.setCenter(player.getX(), player.getY());
	BadGuy *bg = new BadGuy(window, "Orc", c.x1+20, c.y1+20);
	registerObject(bg);
//	window.setView(view);
//	view.setCenter(player.getX(), player.getY());

	//InputManager input(player, playerSprite, view, window);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::EventType::Closed)
				window.close();
		}
		view.setCenter(player.getX(), player.getY());
		window.setView(view);
		window.clear();
		for(auto it=updateStaticObjects.begin(); it!= updateStaticObjects.end(); ++it) {
			(*it)->display();
		}
		for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {
			(*it)->takeTurn();
		}
		for (auto it = updateMoveableObjects.begin(); it != updateMoveableObjects.end(); ++it) {
			(*it)->display();
		}
		window.display();
		flushObjects();
	}
	return 0;
};


Game::~Game()
{
};
