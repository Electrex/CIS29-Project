#ifndef DROPCOMMAND_HPP
#define DROPCOMMAND_HPP
#include "Command.hpp"

class DropCommand : public Command
{
    public:
        DropCommand();
        virtual ~DropCommand();
        void execute(Actor& actor) { actor.dropWeapon(); }
};

#endif // DROPCOMMAND_HPP
