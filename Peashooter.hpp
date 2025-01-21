#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <vector>
#include "Plant.hpp"

//peashooter class, inherits from plant class
class Peashooter : public Plant {
private:
    //peashooter ROF
    int rateOfFire = 5;

public:
    //constructor for peashooter
    Peashooter(const sf::Texture& texture);

    //method to shoot peas
    void shoot(std::vector<sf::Sprite>& peas, const sf::Texture& peaTexture) override;

};

#endif
