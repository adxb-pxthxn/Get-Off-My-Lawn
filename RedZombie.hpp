#ifndef REDZOMBIE_H
#define REDZOMBIE_H

#include "Zombie.hpp"

//class for RedZombie, inherits from zombie class
class RedZombie : public Zombie{
    public:
    //constructor for RedZombie
    RedZombie(const sf::Texture& texture);
};
#endif