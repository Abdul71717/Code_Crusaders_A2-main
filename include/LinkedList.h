#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <iostream>
#include <vector>


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    void purchaseItems(std::vector<Coin> ftt_coins);

    // Add a node to the linked list
    void addNode(FoodItem* item);
    void addNode(Node* node);

    // Remove a node from the linked list by id
    bool removeNode(const std::string& id);

    // Display all nodes in the linked list
    void displayList() const;

private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
     

  
    // The end of the list (for doubly linked list)
    Node* tail;


    // Helper function to delete all nodes
    void deleteAllNodes();
};

#endif  // LINKEDLIST_H


