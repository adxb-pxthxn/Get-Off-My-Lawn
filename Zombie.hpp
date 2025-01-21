#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <SFML/Graphics.hpp>
#include "Character.hpp"

//Zombie class, inherits from Character
class Zombie : public Character, public sf::Sprite {
private:
   static constexpr float speed = 30.0f;


public:
    //constructor for zombie
    Zombie(const sf::Texture& texture);

    void takeDamage(int damage) override; //override the pure virtual function
    bool isDead() const; //you can keep this if it serves a purpose
    void update(float deltaTime); //update zombie's movement
};

#endif