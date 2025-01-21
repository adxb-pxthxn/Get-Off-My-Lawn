#include "Zombie.hpp"

//constructor for zombie
Zombie::Zombie(const sf::Texture& texture) 
    : Character(), sf::Sprite(){ //call the Character constructor
    this->setTexture(texture);
    this->health = 100; //set the initial health from the constructor parameter
    this->damage = 1; //set a default damage value for zombies
    this->isAlive = true; //assuming a new zombie is alive
    this->setScale(0.4f, 0.4f);  //adjust the size of the zombie
}

//override takeDamage method
void Zombie::takeDamage(int damage) {
    this->health -= damage;
    if (this->health <= 0) {
        this->isAlive = false; 
    }
}

//check if zombie is dead
bool Zombie::isDead() const {
    return !this->isAlive;
}

void Zombie::update(float deltaTime) {
    this->move(-speed * deltaTime, 0);  //move the zombie to the left
}
