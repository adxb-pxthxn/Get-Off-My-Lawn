#include "Character.hpp"

//constructor for character class
Character::Character() {}

//set isAlive based on health
void Character::set_isAlive() {
  if (health > 0) {
    isAlive = 1;
  } else {
    isAlive = 0;
  }
}

//setters and getters for health, damage, and isAlive
void Character::set_health(int cHealth) { health = cHealth; }
void Character::set_damage(int cDamage) { damage = cDamage; }
int Character::get_health() { return health; }
int Character::get_damage() { return damage; }
bool Character::get_isAlive() { return isAlive; }

//destructor for character class
Character::~Character() {}