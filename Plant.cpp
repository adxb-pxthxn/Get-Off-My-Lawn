#include "Plant.hpp"

//constructor for plant class
Plant::Plant(const sf::Texture& texture, int initialHealth) : Character(){
    this->setTexture(texture);
    this->health = initialHealth;
    this->isAlive = true;
}

//overriding takeDamage() method
void Plant::takeDamage(int damage) {
    this->health -= damage;

    if (this->health <= 0) {
        this->isAlive = false;  //mark as dead when health drops to 0 or below
    }
}

//method checking if plant is dead
bool Plant::isDead() const {
    return !this->isAlive;
}