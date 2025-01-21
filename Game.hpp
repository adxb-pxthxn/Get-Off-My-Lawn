#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <cmath>

#include "Money.hpp"
#include "Character.hpp"
#include "Zombie.hpp"
#include "RedZombie.hpp"
#include "Plant.hpp"
#include "Peashooter.hpp"
#include "Walnut.hpp"

#include <cstdlib>  //for rand() and srand()
#include <ctime>    //for time()

#include <fstream>


enum class GameState {
    MENU,
    GAME
};

class Game {
public:
    //constructor to set up the game
    Game();

    //main game loop
    void run();  

private:
    //member variables
    sf::RenderWindow window;
    GameState currentState;

    //clock to keep track of time
    sf::Clock scoreClock;
    //clock to handle spawning of zombies
    sf::Clock spawnClock;
    //clock to handle update function, reset once per frame
    sf::Clock frameClock;
    //clock to handle shooting peas
    sf::Clock peaShootClock; 

    //textures
    sf::Texture backGroundTexture;
    sf::Texture zombieTexture;
    sf::Texture peaShooterTexture;
    sf::Texture peaTexture;
    sf::Texture walnutTexture;

    //key values
    int highestScore;
    int score;
    int selectedPlant;
    Money playerMoney;
    int peaShooterCost;
    int walnutCost;

    //static sprites
    sf::Sprite backGroundSprite;

    //store all zombies
    std::vector<std::unique_ptr<Zombie>> zombies;
    //store all plants  
    std::vector<std::unique_ptr<Plant>> plants;
    //store pea sprites
    std::vector<sf::Sprite> peas;
    
    //member functions
    void spawnZombie();
    void shootPeas();
    void updatePeas(float deltaTime);
    void collisionDetection(float deltaTime);

    void handleEvents();   //handle user input
    void update();         //game state update logic
    void render();         //rendering logic

    void loadTextures();   //load all textures
    void setupSprites();   //setup initial sprite settings
    void handleMouseClick(); //handle mouse click events
    void placePlant(int x, int y); //lets you place a peashooter
    void peaZombieDetection(); //check if a pea has hit a zombie
    void calculateScore(); //calculates score based on time being playeds
    void handleMenu(); //setup menu
    void zombiePassed(); //checks if a zombie has passed the player, ends the game if it has occured
    void clearGrid(); //clears the grid of all plants, zombies, and peas 
    void saveHighestScore(); //saves the highest score to a text file
    void loadHighestScore(); //loads the highest score from a text file
    
};

#endif
