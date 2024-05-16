#include "Coin.h"
 
 // implement functions for managing coins; this may depend on your design.



Coin::Coin() : denom(FIVE_CENTS), count(0) {} //denom needs a default 0 value therefore set to five_cents can add NO_DENOMINATION to enum in coin.h

//constructor 
Coin::Coin(Denomination denom, int count) : denom(denom), count(count) {}

int Coin::getDenomination(){
    if (denom == FIVE_CENTS){
        return 5;
    }else if (denom == TEN_CENTS){
        return 10;   
    }else if (denom == TWENTY_CENTS){
        return 20;   
    }else if (denom == FIFTY_CENTS){
        return 50;   
    }else if (denom == ONE_DOLLAR){
        return 100;   
    }else if (denom == TWO_DOLLARS){
        return 200;   
    }else if (denom == FIVE_DOLLARS){
        return 500;   
    }else if (denom == TEN_DOLLARS){
        return 1000;   
    }else if (denom == TWENTY_DOLLARS){
        return 2000;   
    }else if (denom == FIFTY_DOLLARS){
        return 5000;   
    }
    throw std::invalid_argument("invalid denomination given");
}
Denomination Coin::castToDenom(int denom){
    if(denom == 5){
        return FIVE_CENTS;
    }else if(denom == 10){
        return TEN_CENTS;
    }else if(denom == 20){
        return TWENTY_CENTS;
    }else if(denom == 50){
        return FIFTY_CENTS;
    }else if(denom == 100){
        return ONE_DOLLAR;
    }else if(denom == 200){
        return TWO_DOLLARS;
    }else if(denom == 500){
        return FIVE_DOLLARS;
    }else if(denom == 1000){
        return TEN_DOLLARS;
    }else if(denom == 2000){
        return TWENTY_DOLLARS;
    }else if(denom == 5000){
        return FIFTY_DOLLARS;
    }
    throw std::invalid_argument("invalid denomination given");
}

int Coin::getCount() const {
    return count;
}

void Coin::incrementCount(int amount) {
    count += amount;
}

void Coin::decrementCount(int amount) {
    count -= amount;
}

bool Coin::operator==(const Coin &other) const {
    return denom == other.denom;
}

// Updated input stream operator to handle enum type
std::istream &operator>>(std::istream &input, Coin &coin) {
    int denomInt, quantity;
    if (input >> denomInt && input.get() == ',' && input >> quantity) {
        coin.denom = static_cast<Denomination>(denomInt);
        coin.count = quantity;
    }
    return input;
}

// output stream operator to handle enum type
std::ostream &operator<<(std::ostream &output, const Coin &coin) {
    output << static_cast<int>(coin.denom) << "," << coin.count;
    return output;
}