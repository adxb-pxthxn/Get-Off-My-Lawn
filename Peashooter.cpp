#include "Peashooter.hpp"

//peashooter constructor 
Peashooter::Peashooter(const sf::Texture& texture) : Plant(texture, 100){
    this->health = 100;
    this->damage = 25;
    this->price = 20;  
    this->isAlive = true;
}

//method to fire pea
void Peashooter::shoot(std::vector<sf::Sprite>& peas, const sf::Texture& peaTexture) {
    sf::Sprite newPea(peaTexture);
    newPea.setScale(0.1f, 0.1f);  //set pea size
    newPea.setColor(sf::Color(255,150,255));
    newPea.setPosition(this->getPosition().x + this->getGlobalBounds().width ,  //start in front of the Peashooter
                       this->getPosition().y +10);  //align vertically with Peashooter
    peas.push_back(newPea);  //add the new pea to the peas vector
}


