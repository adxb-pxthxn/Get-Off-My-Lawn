#include "Game.hpp"

Game::Game() : playerMoney(), window(sf::VideoMode(1268, 720), "Get Off My Lawn"), currentState(GameState::MENU) {

    //load textures and set up sprites
    loadTextures();
    setupSprites();

    //restart score clock for new gameplay session
    scoreClock.restart();
    highestScore = 0;
    score = 0;
    peaShooterCost = 20;
    walnutCost = 10;
    selectedPlant = 1;

    //seed random number generator with current time
    std::srand(std::time(0));

}

//runs all the code neccesary for the game to work
void Game::run() {
    while (window.isOpen()) {
        handleEvents();  //poll for events

        if (currentState == GameState::MENU) {
            handleMenu();  //show the menu when in the MENU state
            clearGrid(); //clear the game grid when in MENU state
            loadHighestScore(); //load highest score when in MENU state
            playerMoney.restartFunds(); //reset players money
        
        } else if (currentState == GameState::GAME) {
            update();  //run game logic
            render();  //draw the game
        }
    }
}

//runs in real time in order to use user input
void Game::handleEvents() {
    sf::Event event; //initialise SFML event object to capture inputs
    while (window.pollEvent(event)) { //while window is open, continuosly fetch all pending events from queue
        if (event.type == sf::Event::Closed) { //if x button on window pressed, close window
            window.close();
        }

        //handle "Escape" to return to the start menu
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                currentState = GameState::MENU;  //return to the start menu
            }

            //set selectedPlant through num key inputs
            if(event.key.code == sf::Keyboard::Num1){
                selectedPlant = 1;
            }
            else if(event.key.code == sf::Keyboard::Num2){
                selectedPlant = 2;
            }
        }

        //handle mouse click input
        if (currentState == GameState::GAME) {
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                handleMouseClick(); //call specific function
            }
        }
    }
}



//updates game logic
void Game::update() {
    float deltaTime = frameClock.restart().asSeconds();  //restart clock once per frame
    
    if(currentState == GameState::GAME){
        const float spawnInterval = 4.0f;  //spawn a sprite every 4 seconds
        if (spawnClock.getElapsedTime().asSeconds() >= spawnInterval) { //call spawn function periodically
            spawnZombie();
        }

        calculateScore(); 
        saveHighestScore();

        shootPeas();
        updatePeas(deltaTime);
        peaZombieDetection();
        collisionDetection(deltaTime);
        zombiePassed();
        playerMoney.makeMoneyPerSec();
    }
}

//renders all the sprites
void Game::render() {
    window.clear(sf::Color::White);
    window.draw(backGroundSprite);

    //set up text for the game title, instructions, and highest score
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) { //load a font (replace with your path)
        std::cerr << "Error loading font!" << std::endl;
    }

    //draw the current score
    sf::Text scoreText("Score: " + std::to_string(score), font, 30);
    scoreText.setPosition(50, 20);  // Position at the top-left corner
    scoreText.setFillColor(sf::Color::Black);
    window.draw(scoreText);

    //draw the current score
    sf::Text moneyText("Money: $" + std::to_string(playerMoney.getMoney()), font, 30);
    moneyText.setPosition(200, 20);  // Position at the top-left corner
    moneyText.setFillColor(sf::Color::Black);
    window.draw(moneyText);

    //draw plant name and price
    if(selectedPlant == 1){
        sf::Text selectedPlantText("Selected Plant: Peashooter Cost: $" + std::to_string(peaShooterCost), font, 30);
        selectedPlantText.setPosition(400, 20);
        selectedPlantText.setFillColor(sf::Color::Black);
        window.draw(selectedPlantText);
    }
    else if(selectedPlant == 2){
        sf::Text selectedPlantText("Selected Plant: Walnut Cost: $" + std::to_string(walnutCost), font, 30);
        selectedPlantText.setPosition(400, 20);
        selectedPlantText.setFillColor(sf::Color::Black);
        window.draw(selectedPlantText);
    }

    sf::Text escapeText("Press esc: to quit and go to menu", font, 30);
    escapeText.setPosition(850, 10);
    escapeText.setFillColor(sf::Color::Black);
    window.draw(escapeText);


    //draw all peashooters
    for (const auto& plant : plants) {
        window.draw(*plant);
    }

    //draw all zombies
    for (const auto& zombie : zombies) {
        window.draw(*zombie);
    }

    //draw all peas
    for (const auto& pea : peas) {
        window.draw(pea);
    }

    window.display();
}



//load all the textures to be avlaiable
void Game::loadTextures() {
    if (!peaTexture.loadFromFile("icons/pea2.png") || 
        !backGroundTexture.loadFromFile("icons/lawn.jpg") || 
        !peaShooterTexture.loadFromFile("icons/peaShooter.png") || 
        !zombieTexture.loadFromFile("icons/zombie.png") ||
        !walnutTexture.loadFromFile("icons/Walnut.png")) {
        std::cerr << "Error: Could not load the image from the path!" << std::endl;
    }
}

//sets up the main background sprite 
void Game::setupSprites() {
    backGroundSprite.setTexture(backGroundTexture);
}


//what is called to use the mouse click value
void Game::handleMouseClick() {
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    
    placePlant(mousePosition.x,mousePosition.y);
    
}

void Game::placePlant(int x, int y){
    std::unique_ptr<Plant> newPlant = nullptr;

    if(selectedPlant == 1){
        if(playerMoney.checkIfFundsAvaliable(peaShooterCost)){
            newPlant = std::make_unique<Peashooter>(peaShooterTexture);
            playerMoney.spendMoney(peaShooterCost);
        }
    }
    else if(selectedPlant == 2){
        if(playerMoney.checkIfFundsAvaliable(walnutCost)){
            newPlant = std::make_unique<Walnut>(walnutTexture);
            playerMoney.spendMoney(walnutCost);
        }
    }

    if(newPlant){
        if((x >= 303 && x <= 1150) && (y >= 99 && y <= 681)){
            int MouseX = x, MouseY = y;
            float xOffset = 345, yOffset = 152;
            float xDiv = 95.625, yDiv = 118;

            float xScale = (MouseX - xOffset) / xDiv;
            float yScale = (MouseY - yOffset) / yDiv;

            int alteredMouseX = (xScale - std::floor(xScale) > std::ceil(xScale) - xScale) ? 
                                (std::ceil(xScale) * xDiv) + xOffset : 
                                (std::floor(xScale) * xDiv) + xOffset;
            int alteredMouseY = (yScale - std::floor(yScale) > std::ceil(yScale) - yScale) ? 
                                (std::ceil(yScale) * yDiv) + yOffset : 
                                (std::floor(yScale) * yDiv) + yOffset;

            newPlant->setPosition(alteredMouseX - newPlant->getGlobalBounds().width / 2,
                                alteredMouseY - newPlant->getGlobalBounds().height / 2);

            plants.push_back(std::move(newPlant));    
        }
    }
}

void Game::spawnZombie(){
    if (currentState == GameState::MENU) {
        return; 
    }

    int randomRow = std::rand() % 5;
    int yPosition = 152 + (118 * randomRow);

    bool isRed = (std::rand() % 5 == 0);
    std::unique_ptr<Zombie> newZombie;

    if(isRed){
        newZombie = std::make_unique<RedZombie>(zombieTexture);
    }
    else{
        newZombie = std::make_unique<Zombie>(zombieTexture);
    }

    newZombie->setPosition(1200 - newZombie->getGlobalBounds().width/2, yPosition - newZombie->getGlobalBounds().height/2);

    zombies.push_back(std::move(newZombie)); 
    spawnClock.restart();
}

//checks if a zombie has collided with a peashooter if not move
void Game::collisionDetection(float deltaTime) {
    for (size_t i = 0; i < zombies.size(); i++) {
        bool collisionDetected = false;

        //check for collisions with plants
        for (size_t j = 0; j < plants.size(); ++j) {
            if (zombies[i]->getGlobalBounds().intersects(plants[j]->getGlobalBounds())) {
                collisionDetected = true;
                
                if(auto peaShooter = dynamic_cast<Peashooter*>(plants[j].get())){
                    int zombieDamage = zombies[i]->get_damage();
                    peaShooter->takeDamage(zombieDamage);

                    if(peaShooter->isDead()){
                        plants.erase(plants.begin() + j);
                        break;
                    }
                }

                if(auto walnut = dynamic_cast<Walnut*>(plants[j].get())){
                    int zombieDamage = zombies[i]->get_damage();
                    walnut->takeDamage(zombieDamage);

                    if(walnut->isDead()){
                        plants.erase(plants.begin() + j);
                        break;
                    }
                }
            }
        }

        //if no collision is detected, move the zombie
        if (!collisionDetected) {
            zombies[i]->update(deltaTime);  //move zombie using its own update method
        }
    }
}

void Game::shootPeas() {
    const float shootInterval = 2.0f;
    if (peaShootClock.getElapsedTime().asSeconds() >= shootInterval) {
        for (auto& plant : plants) {
            plant->shoot(peas, peaTexture);
        }
        peaShootClock.restart();
    }
}

//update to move pea 
void Game::updatePeas(float deltaTime){
    const float peaSpeed = 200.0f;
    // Move all the peas
    for(auto& pea : peas){  // Changed from peaSprites to peas
        pea.move(peaSpeed * deltaTime, 0);  // Move peas to the right
    }

    // Remove peas that go off the screen
    peas.erase(std::remove_if(peas.begin(), peas.end(), [&](sf::Sprite& pea) {
        return pea.getPosition().x > window.getSize().x;
    }), peas.end());
}

//checks if a pea has hit a zombie
void Game::peaZombieDetection() {
    for (size_t i = 0; i < peas.size(); ++i) {
        bool peaHit = false;

        //check for collision between peas and zombies
        for (size_t j = 0; j < zombies.size(); ++j) {
            if (peas[i].getGlobalBounds().intersects(zombies[j]->getGlobalBounds())) {

                int peaDamage = 15;


                zombies[j]->takeDamage(peaDamage);  // Reduce zombie health by 25

                if (zombies[j]->isDead()) {
                    zombies.erase(zombies.begin() + j);
                    j--;  //decrement index to prevent skipping zombies
                }

                peaHit = true;
                break;
            }
        }

        if(peaHit){
            peas.erase(peas.begin() + i);
            i--;  //decrement index to prevent skipping peas
        }
    }
}

 
void Game::zombiePassed(){
    for (size_t i = 0; i < zombies.size(); ++i) {
        if(zombies[i]->getPosition().x <= 220){
            calculateScore();
            currentState = GameState::MENU;  // Return to the start menu
        }
    }
}



//calculates the score based on time
void Game::calculateScore(){
    score = scoreClock.getElapsedTime().asSeconds();

    if(score > highestScore){
        highestScore = score;
    }
}



void Game::handleMenu() {
    // Clear the window with a background color
    window.clear(sf::Color::White);
    
    // Set up text for the game title, instructions, and highest score
    sf::Font font;
    if (!font.loadFromFile("font.ttf")) { // Load a font (replace with your path)
        std::cerr << "Error loading font!" << std::endl;
    }
    
    // Set up the title text
    sf::Text title("Get Off My Lawn", font, 50);
    title.setPosition(400, 100);  // Position at the center-top of the window
    title.setFillColor(sf::Color::Black);

    // Set up the description text
    sf::Text description("Shoot zombies with Peashooters. Slow them down with Walnuts. \n Survive as long as possible! \n Place plants on grid by using your mouse with a left Click. \n Press 1 to select Peashooter, 2 to select Walnut.",  font, 30);
    description.setPosition(350, 200);  // Adjust position as needed
    description.setFillColor(sf::Color::Black);


    // Display the highest score
    sf::Text highScoreText("Highest Score: " + std::to_string(highestScore), font, 50);
    highScoreText.setPosition(350, 500);  // Adjust position as needed
    highScoreText.setFillColor(sf::Color::Black);
    
    // Add a "Press Enter to Start" message
    sf::Text startText("Press Enter to Start", font, 30);
    startText.setPosition(350, 600);  // Adjust position as needed
    startText.setFillColor(sf::Color::Green);

    // Draw the text elements
    window.draw(title);
    window.draw(description);
    window.draw(highScoreText);
    window.draw(startText);

    window.display();  // Render the screen

    // Event handling for the menu
    sf::Event event;
    while (window.pollEvent(event)) {
        // Allow closing the window
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        // Wait for user to press Enter to start the game
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Enter) {
                currentState = GameState::GAME;  // Switch to game state
                scoreClock.restart();  // Reset the score clock for a new game
            }
        }

    }
}



//clear grid function, called when game state is MENU
void Game::clearGrid(){
    plants.clear();
    zombies.clear();
    peas.clear();
}


//function to save highscore to text file
void Game::saveHighestScore(){
    std::ofstream saveFile("highestScore.txt");
    if(saveFile.is_open()){
        saveFile << highestScore;
        saveFile.close();
    }
    else {
        std::cerr << "Error: Could not save score" << std::endl;
    }
}

//function to load score from text file
void Game::loadHighestScore(){
    std::ifstream loadFile("highestScore.txt");
    if(loadFile.is_open()){
        loadFile >> highestScore;
        loadFile.close();
    }
    else {
        std::cerr << "Error: Could not load score" << std::endl;
    }
}