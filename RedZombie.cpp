#include "RedZombie.hpp"

RedZombie::RedZombie(const sf::Texture& texture) : Zombie(texture) { //call the base Zombie constructor
    this->setColor(sf::Color(255,100,100));
    this->health = 200;  //more health than a regular Zombie
    this->damage = 5;    //more damage than a regular Zombie
    this->setScale(0.45f, 0.45f);  //larger size for more powerful appearance
    this->isAlive = true; //assuming a new zombie is alive
}