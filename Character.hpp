#ifndef CHARACTER_H
#define CHARACTER_H

//character class, is the base class for all characters in the game
class Character {
 protected:
  int health; //health of the character
  int damage; //damage of the character
  bool isAlive = 0; //is the character alive

 public:
  //constructor for character class
  Character();

  //setters and getters for health, damage, and isAlive
  void set_isAlive();
  void set_health(int cHealth);
  void set_damage(int cDamage);
  int get_health();
  int get_damage();
  bool get_isAlive();

  //destructor for character class
  ~Character();


  //virtual function for taking damage and updating the character
  virtual void takeDamage(int damage)=0;
};

#endif