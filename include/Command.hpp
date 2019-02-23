#ifndef COMMAND_HPP
#define COMMAND_HPP
#include "Actor.hpp"

class Command
{
    public:
        virtual ~Command() {};
        virtual void execute(Actor& actor) = 0;
};

#endif // COMMAND_HPP
