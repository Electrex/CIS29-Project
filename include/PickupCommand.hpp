#ifndef PICKUPCOMMAND_HPP
#define PICKUPCOMMAND_HPP
#include "Command.hpp"

class PickupCommand : public Command
{
    public:
        PickupCommand();
        virtual ~PickupCommand();
        void execute(Actor& actor) { actor.pickup(); }
};

#endif // PICKUPCOMMAND_HPP
