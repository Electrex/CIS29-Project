#ifndef THROWCOMMAND_HPP
#define THROWCOMMAND_HPP
#include "Command.hpp"

class ThrowCommand : public Command
{
    public:
        ThrowCommand();
        virtual ~ThrowCommand();
        void execute(Actor& actor) { actor.throwWeapon(); }
};

#endif // THROWCOMMAND_HPP
