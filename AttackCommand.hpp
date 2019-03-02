#ifndef ATTACKCOMMAND_HPP
#define ATTACKCOMMAND_HPP
#include "Command.hpp"

class AttackCommand : public Command
{
    public:
        AttackCommand();
        virtual ~AttackCommand();
        void execute(Actor& actor) { actor.attack(); }
};

#endif // ATTACKCOMMAND_HPP
