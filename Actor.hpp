#ifndef ACTOR_HPP
#define ACTOR_HPP
#include <SFML/Graphics.hpp>

class Actor
{
    public:
        Actor(sf::View& view) : mView(view) {}
        virtual ~Actor();
        virtual void attack() {}
        virtual void pickup() {}
        virtual void dropWeapon() {}
        virtual void throwWeapon() {}

        void move(sf::Vector2f movement) { mView.move(movement); }

    protected:

    private:
        sf::View& mView;
};

#endif // ACTOR_HPP
