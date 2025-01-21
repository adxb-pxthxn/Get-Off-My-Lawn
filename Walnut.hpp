#ifndef WALNUT_H
#define WALNUT_H

#include "Plant.hpp"

//walnut class, inherits from plant class
class  Walnut : public Plant{
public:
    //constructor for walnut class
    Walnut(const sf::Texture& texture);

    void shoot(std::vector<sf::Sprite>& peas, const sf::Texture& peaTexture) override;
};


#endif