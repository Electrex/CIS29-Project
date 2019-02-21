#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Invaders.h"

Invaders::Invaders()
    : direction(Right), speed(3.0f)
{
    // invaderTexture.loadFromFile(filename);
    sf::IntRect invaderImageLocationInTexture;
    invaderImageLocationInTexture.height = InvaderSize.y;
    invaderImageLocationInTexture.width = InvaderSize.x;
    invaderImageLocationInTexture.left = 0;

    for (auto row = 0; row < NumInvaders.x; ++row)
    {
        for (auto col = 0; col < NumInvaders.y; ++col)
        {
            // set texture for Invader (sf::RectangleShape)
            invaderImageLocationInTexture.top = row * InvaderSize.y;
            invader[row][col].setTextureRect(invaderImageLocationInTexture);
            invader[row][col].setTexture(&InvaderTexture);
        }
    }
}

void Invaders::moveInvadersToStartPosition()
{
    for (auto row = 0; row < NumInvaders.x; ++row)
    {
        for (auto col = 0; col < NumInvaders.y; ++col)
        {
            invader[row][col].setPosition(100+2*InvaderSize.x*col,100+2*InvaderSize.y*row);
        }
    }
}

sf::Vector2f Invaders::getInvaderPosition(int row, int col) const
{
    return invader[row][col].getPosition();
}

bool Invaders::move()
{
    bool moveDownFlag = false;
    float bottomOfInvaders;
    sf::IntRect invaderImageLocationInTexture;
    sf::Vector2f invaderCurrentPosition;
    if (invaderImageLocationInTexture.left == 0)
        invaderImageLocationInTexture.left = 32;
    else
        invaderImageLocationInTexture.left = 0;

    if (invader[0][getIndexOfRightmostInvaderColumn()].getPosition().x > MainWindowWidth - 2 * InvaderSize.x)
    {
        direction = Left;
        moveDownFlag = true;
    }
    if (invader[0][getIndexOfLeftmostInvaderColumn()].getPosition().x < InvaderSize.x)
    {
        direction = Right;
        moveDownFlag = true;;
    }

    for (auto row = 0; row < NumInvaders.x; ++row)
    {
        for (auto col = 0; col < NumInvaders.y; ++col)
        {
            invaderImageLocationInTexture = invader[row][col].getTextureRect();
            if (invaderImageLocationInTexture.left == 0)
                invaderImageLocationInTexture.left = 32;
            else
                invaderImageLocationInTexture.left = 0;

            invader[row][col].setTextureRect(invaderImageLocationInTexture);
            invaderCurrentPosition = getInvaderPosition(row,col);
            if (direction == Right)
                invaderCurrentPosition.x += speed;
            else
                invaderCurrentPosition.x -= speed;
            if (moveDownFlag)
            {
                // move down 10 pixels
                invaderCurrentPosition.y += 10.0f;
                //std::cout << "Max row index = " << getMaxIndexOfVisibleInvaders() << endl;
                bottomOfInvaders = invader[getMaxIndexOfVisibleInvaders()][0].getPosition().y;
                //std::cout << bottomOfInvaders << std::endl;
                // working here
                //
                //if (bottomOfInvaders <= gunpoition.y) return false;
            }
            invader[row][col].setPosition(invaderCurrentPosition);
        }
    }
    return true;
}

void Invaders::updateStatus()
{
    for (auto row = 0; row < NumInvaders.x; ++row)
    {
        for (auto col = 0; col < NumInvaders.y; ++col)
        {
            if (invader[row][col].getStatus() == Invader::Hit && invader[row][col].getExplosionCount() > 0)
                invader[row][col].incrementExplosionCount();
        }
    }
}

void Invaders::draw(sf::RenderWindow& window)
{
    for (auto row = 0; row < NumInvaders.x; ++row)
    {
        for (auto col = 0; col < NumInvaders.y; ++col)
        {
            if (invader[row][col].getStatus() != Invader::Invisible)
                window.draw(invader[row][col]);
        }
    }
}

// The return value represents the number of points for the invader hit
int Invaders::invaderHitByBullet(Bullet& bullet)
{
    sf::Vector2f invaderPosition;
    sf::Vector2f bulletPosition = bullet.getPosition();

    float invaderHalfSize = invader[0][0].getSize().y/2.0f;

    // if bullet is below bottom invaders skip the check for a hit
    if (getInvaderPosition(NumInvaders.x - 1,0).y + invaderHalfSize - bulletPosition.y <= 2.0f)
        return 0;

    for (int row = NumInvaders.x-1; row >= 0; --row)
    {
        for (auto col = 0; col < NumInvaders.y; ++col)
        {
            if (!invader[row][col].getStatus() == Invader::Visible)
                continue;

            invaderPosition = getInvaderPosition(row,col);
            if (std::fabs(invaderPosition.x - bulletPosition.x) < invaderHalfSize && std::fabs(invaderPosition.y - bulletPosition.y) < invaderHalfSize)
            {
                std::cout << "Invader hit at " << row << ',' << col << std::endl;

                // set explosion texture
                sf::IntRect explosionImageLocationInTexture;
                explosionImageLocationInTexture.height = InvaderSize.y;
                explosionImageLocationInTexture.width = InvaderSize.x;
                explosionImageLocationInTexture.left = (std::rand()%2) * 32.0f;
                explosionImageLocationInTexture.top = NumInvaders.x * InvaderSize.y;

                invader[row][col].setTextureRect(explosionImageLocationInTexture);
                invader[row][col].setTexture(&InvaderTexture);
                invader[row][col].setHitStatus();
                invader[row][col].incrementExplosionCount();
                increaseSpeed();
                return 5 - row;
            }
        }
    }
    return 0;
}

int Invaders::getMaxIndexOfVisibleInvaderByColumn(int column) const
{
    int maxIndex = -1;
    for (int row = 0; row < NumInvaders.x; ++row)
        if (invader[row][column].isVisible())
            maxIndex = row;
    return maxIndex;
}

int Invaders::getMaxIndexOfVisibleInvaders() const
{
    int maxIndex = -1;
    for (int row = NumInvaders.x - 1; row >= 0; --row)
    {
        for (int col = 0; col < NumInvaders.y; ++col)
        {
            if (invader[row][col].isVisible())
                return row;
        }
    }
    return maxIndex;
}

int Invaders::getIndexOfRightmostInvaderColumn() const
{
    for (int rightmostColumn = NumInvaders.y - 1; rightmostColumn >= 0; --rightmostColumn)
    {
        if (getMaxIndexOfVisibleInvaderByColumn(rightmostColumn) != -1)
            return rightmostColumn;
    }
    return -1;
}

int Invaders::getIndexOfLeftmostInvaderColumn() const
{
    for (int leftmostColumn = 0; leftmostColumn < NumInvaders.y - 1; ++leftmostColumn)
    {
        if (getMaxIndexOfVisibleInvaderByColumn(leftmostColumn) != -1)
            return leftmostColumn;
    }
    return -1;
}
