#ifndef COIN_H
#define COIN_H

#include <iostream>
#include <iomanip>
#include <string>

// Coin.h defines the coin structure for managing currency in the system.
#define DELIM "," // delimiter

// enumeration representing the various types of currency available in the system.
enum Denomination
{
    FIVE_CENTS,
    TEN_CENTS,
    TWENTY_CENTS,
    FIFTY_CENTS,
    ONE_DOLLAR,
    TWO_DOLLARS,
    FIVE_DOLLARS,
    TEN_DOLLARS,
    TWENTY_DOLLARS,
    FIFTY_DOLLARS
};

// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
private:
    // the denomination type
    enum Denomination denom;

    // the count of how many of these are in the cash register
    unsigned count;

public:
    Coin();
    Coin(Denomination denom, int count);

    int getDenomination();
    static Denomination castToDenom(int denom);

    int getCount() const;

    void incrementCount(int amount = 1);
    void decrementCount(int amount = 1);

    bool operator==(const Coin &other) const;                                // for comparing demonation
    friend std::istream &operator>>(std::istream &input, Coin &coin);        // For reading Coin data from stream
    friend std::ostream &operator<<(std::ostream &output, const Coin &coin); // For writing Coin data to stream
};

#endif // COIN_H