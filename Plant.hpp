#ifndef PLANT_H
#define PLANT_H

#include "Character.hpp"
#include <SFML/Graphics.hpp>

//plant class, inheirits from character.
class Plant : public Character, public sf::Sprite {
protected:
    int price = 0; //plant price
public:
    //default constructor for plant class
    Plant(const sf::Texture& texture, int initialHealth);
    
    //default destructor for plant class
    virtual ~Plant() = default;

    //override takeDamage function
    void takeDamage(int damage) override;
    bool isDead() const;

    //virtual function to shoot peas, will be overriden by peashooter class
    virtual void shoot(std::vector<sf::Sprite>& peas, const sf::Texture& peaTexture) = 0;
};

#endif