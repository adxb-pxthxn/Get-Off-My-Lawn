#include "Walnut.hpp"

//constructor for walnut class, health is set to 300
Walnut::Walnut(const sf::Texture& texture) : Plant(texture, 1500){ 
    this->damage = 0; //damage set to 0 as walnut does no damage
    this->price = 15;
}

void Walnut::shoot(std::vector<sf::Sprite>& peas, const sf::Texture& peaTexture) {
    //walnut does not shoot
}