#ifndef INVADER_H
#define INVADER_H

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

const sf::Vector2f InvaderSize{32.0f,32.0f};

class Invader : public sf::RectangleShape
{
    public:
        enum Status {Visible,Hit,Invisible};
        Invader();
        virtual ~Invader();
        Status getStatus() const { return status; }
        void setStatus(Status status) { this->status = status;  explosionCount = 1;}
        bool isVisible() const { return status == Visible; }
        void setHitStatus() { status = Hit; }
        void setExplosionCount() { explosionCount = 1; }
        unsigned getExplosionCount() const { return explosionCount; }
        void incrementExplosionCount() { ++explosionCount; if (explosionCount > 100) status = Invisible; }
      //  sf::Vector2f getPosition() const { return getPosition(); }
    protected:

    private:
        Status status;
        unsigned explosionCount;
};

#endif // INVADER_H
