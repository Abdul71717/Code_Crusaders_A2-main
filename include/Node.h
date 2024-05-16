#ifndef NODE_H
#define NODE_H
#include <string> 
#include "Coin.h"

// The length of the id string not counting the null terminator
#define IDLEN 5

// The maximum length of a food item name not counting the null terminator
#define NAMELEN 40

// The maximum length of a food item description not counting the null terminator
#define DESCLEN 255

// The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

// The possible default food stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_FOOD_STOCK_LEVEL 20

// The number of denominations of currency available in the system 
#define NUM_DENOMS 8

/**
 * A structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
class Price
{
public:
    // The dollar value, and the cents value for some price
    unsigned dollars, cents;
};

/**
 * Data structure to represent a food item within the system
 **/
class FoodItem
{
public:
    // The unique id for this food item
    std::string id;

    // The name of this food item
    std::string name;
    
    // The description of this food item   
    std::string description;
    
    // The price of this food item
    Price price;
    
    // How many of this food item do we have on hand? 
    unsigned on_hand;    
};

/**
 * The node that holds the data about a food item stored in memory
 **/
class Node
{
public:
    Node(FoodItem* item = nullptr); // Added FoodItem for easier deletion of data
    ~Node();
    Node(const std::string& id, const std::string& name, const std::string& desc, double price);
    // Pointer to the data held for the node 
    FoodItem* data;
    
    // Pointer to the next node in the list 
    Node* next;

    // Pointer to the previous node in the list (for doubly linked list)
    Node* prev;
};

#endif // NODE_H