#include "Money.hpp"


Money::Money(){
    amountOfFunds = 50;
    moneyPerSec = 4;
    elapsedTime = 1.0;
    startMoneyGen = false;
}

void Money::spendMoney(int amount){
    amountOfFunds = amountOfFunds - amount;
}

void Money::restartFunds(){
    amountOfFunds = 50;
}

bool Money::checkIfFundsAvaliable(int amount){
    if(amountOfFunds<amount){
        return false;
    }
    else{
        return true;
    }

}

int Money::getMoney(){
    return amountOfFunds;
}



void Money::makeMoneyPerSec(){
    if(!startMoneyGen){
        startTime = std::chrono::high_resolution_clock::now();
    }

    startMoneyGen = true;
    currentTime = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsedTime = currentTime - startTime;

    if(elapsedTime.count() >= 1.0){
        amountOfFunds = amountOfFunds + moneyPerSec;
        startMoneyGen = false;
    }
}