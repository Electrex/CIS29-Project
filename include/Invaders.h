#ifndef INVADERS_H
#define INVADERS_H
#include <string>
#include "Bullet.h"
#include "Invaders.h"
#include "Invader.h"

extern const sf::Vector2u NumInvaders;
extern sf::Texture InvaderTexture;
const unsigned MainWindowWidth = 1024;
const unsigned MainWindowHeight = 720;

class Bullet;  // forward declaration

class Invaders
{
    public:
        Invaders();
        void moveInvadersToStartPosition();
        void draw(sf::RenderWindow& window);
        bool move();   // return false if unable to move
        enum Direction {Right, Left};
        Invader& getInvader(int row, int col) { return invader[row][col]; }
        sf::Vector2f getInvaderPosition(int row, int col) const;
        int invaderHitByBullet(Bullet& bullet);
        void updateStatus();
        int getMaxIndexOfVisibleInvaderByColumn(int column) const;
        int getMaxIndexOfVisibleInvaders() const;
        int getIndexOfRightmostInvaderColumn() const;
        int getIndexOfLeftmostInvaderColumn() const;
        void increaseSpeed() { speed *= 1.03; }  // 3% increase

    protected:

    private:
        Invader invader[5][12];
        Direction direction;
        float speed;
};

#endif // INVADERS_H
