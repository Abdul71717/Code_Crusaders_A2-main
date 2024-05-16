#include "LinkedList.h"
#include<iostream>

using std::cout;
using std::endl;
using std::vector;
LinkedList::LinkedList() {
   head = nullptr;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
}

void LinkedList::addNode(FoodItem* item) {
    Node* newNode = new Node(item);

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}
void LinkedList::addNode(Node* node){
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    count++;
}

bool LinkedList::removeNode(const std::string& id) {
    Node* current = head;
    while (current) {
        if (current->data->id == id) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }

            delete current;
            count--;
            return true;
        }
        current = current->next;
    }
    return false;
}

// we take ftt_coins as a parameter so that we can change the coins that the ftt program has of its own when a purchase is successful
void LinkedList::purchaseItems(std::vector<Coin> ftt_coins){
    cout<<"Purchase Item\n"
        <<"-------------\n"
        <<"Please enter the id of the item you wish to purchase: ";
    std::string itemID;
    std::cin>>itemID;
    bool checkID = false;
    if (this->head == nullptr){
        //  there are no items in the food linkedlist
        cout<<"No items found"<<endl;
    }else{
       // bool check = false;
        Node* head = this->head;
        FoodItem* item = nullptr;
        // iterate through the linkedlist and check whether the item exists or not
        while (head->next !=nullptr && !checkID){
            FoodItem* cur = head->data;
            if (cur->id == itemID){
                
                checkID = true;
                item = cur;
                cout<<"found item with details: "<<endl;
                cout<<"ID: "<<item->id<<endl;
                cout<<"Name: "<<item->name<<endl;
                cout<<"Description: "<<item->description<<endl;
                cout<<"Stock: "<<item->on_hand<<endl;
            }
        }
        if (item == nullptr){
            cout<<"item not found"<<endl;
        }else{
            // check whether there is enough stock
            if (item->on_hand == 0){
                cout<<"Out of stock"<<endl;
            }else{
                cout<<"You have selected \""<<item->name<<" - "<<item->description<<"\". This will cost you $ "
                <<item->price.dollars<<"."<<item->price.cents<<".\nPlease hand over the money - type in the value of each note/coin in cents.\n"
                <<"Press enter or ctrl-d on a new line to cancel this purchase:\n";
               // int amount;
                int to_pay = item->price.dollars*100 + item->price.cents;
                //keep taking input until to_pay is 0
                std::string str;
                bool exit = false;
                // create a vector of coins to hold temporarily incase the purchase doesn't go through, 
                // we will have a record of what was added, we initially have all coins' amounts to be 0 as the user hasn't entered anything
                // as they enter valid coin denominations, we will add to here
                std::vector<Coin*> temp_coins{
                    new Coin(Denomination::FIFTY_DOLLARS, 0),
                    new Coin(Denomination::TWENTY_DOLLARS, 0),
                    new Coin(Denomination::TEN_DOLLARS, 0),
                    new Coin(Denomination::FIVE_DOLLARS, 0),
                    new Coin(Denomination::TWO_DOLLARS, 0),
                    new Coin(Denomination::ONE_DOLLAR, 0),
                    new Coin(Denomination::FIFTY_CENTS, 0),
                    new Coin(Denomination::TWENTY_CENTS, 0),
                    new Coin(Denomination::TEN_CENTS, 0),
                    new Coin(Denomination::FIVE_CENTS, 0),
                };
                while(to_pay > 0 && !exit){
                    if(to_pay > 99){
                        // get to_pay in dollars
                        float price = (float)to_pay /100;
                        cout<<"You still need to give us $";
                        printf("%.2f:",price);
                    }else if (to_pay > 0){
                        cout<<"You still need to give us "<<to_pay<<"c";
                    }else{
                        // set exit to true and skip this iteration of the while loop (make it exit without forcing it with a break statement)
                        // or at least that's what i intended it to do, idk if that's how continue works in c++
                        exit = true;
                        break;
                    }
                    // take new input
                    getline(std::cin, str);
                    if (str == ""){
                        // break out of the while loop

                        exit = true;

                    }else{
                        try{
                            int amount = stoi(str);
                            // if the value they entered was not a valid denomination
                           if (amount!=5 && amount!=10 && amount!=20 && amount!=50 && amount!=100 && amount!=200 && amount!=500 &&amount!=1000 && amount!=5000){
                            float amount_as_dollars = (float) amount /100;
                            printf("Error %.2f is not a valid denomination of money. Please try again.\n",amount_as_dollars);
                           }else{
                                /*
                                found a valid coin denomination, now we want to increment the correct denomination in our temp_coins
                                so that we can keep track of it 
                                */
                                for(auto &i:temp_coins){
                                    if (i->getDenomination() == amount){
                                        i->incrementCount();
                                    }
                                }
                                // Decrease the payable amount
                                to_pay -= amount;
                           }
                        }catch(std::invalid_argument &e){
                            // the user entered something that wasnt a number
                            cout<<" you didn't enter a valid input, nothing has changed"<<endl;
                        }
                    }
                }  
                // the user exited before paying off all the amount, so we want to give them a refund of all the coins they gave us
                if (to_pay > 0){
                    // check if we need to return any coins back to the user or not

                    for(auto &i: temp_coins){
                        if (i->getCount() > 0){
                            // print something out here that we have returned them this amount of money
                            // #### TODO ####
                            // dummy print statement please change later
                            std::cout<<"Returned: "<<i->getDenomination()<<" x "<<i->getCount()<<std::endl;
                            // make the count back to 0;
                            i->decrementCount(i->getCount());
                        }
                    }
                }
                else{
                    // either to_pay =0 or to_pay < 0 (the customer gave more money than the item was worth)
                    int change = abs(to_pay);
                    if (to_pay < 0){
                        // the customer paid more so we will need to give them some money back, in the case that we cannot, 
                        // then we will need to refund them all the coins they gave us
                        int total_value_of_coins = 0;
                        // go through the temp coins to get the value of the coins that were given
                        for(auto &i: temp_coins){
                            // increase the total value by the denomination x count
                            total_value_of_coins += i->getDenomination()* i->getCount();
                        }
                        // go through the ftt_coins to get the value of the coins that we already have                  
                        for(auto &i: ftt_coins){
                            // increase the total value by the denomination x count
                            total_value_of_coins += i.getDenomination()* i.getCount();
                        }
                        if (total_value_of_coins < change){
                            // if we do not have enough money to give back:
                            for(auto &i: temp_coins){
                                if (i->getCount() > 0){
                                    // print something out here that we have returned them this amount of money
                                    // #### TODO ####
                                    // dummy print statement please change later
                                    std::cout<<"Returned: "<<i->getDenomination()<<" x "<<i->getCount()<<std::endl;
                                    // make the count back to 0;
                                    i->decrementCount(i->getCount());
                                }
                            }
                        }else{
                            // we have enough money to give back but first we will add the temp coins to our balance so we can use them
                            for(size_t i = temp_coins.size()-1; i>0; i--){
                                // increment the coins of ftt 
                                // but because temp coins is actually backwards (starting from $50 and going down to 5c)
                                // we need to go backwards in temp_coins and go forwards in ftt_coins
                                ftt_coins[temp_coins.size()-i].incrementCount(temp_coins[i]->getCount());
                            }                           
                            // use temp_coins as the vector for holding the refund coins which we will need to print out later 
                            while (change > 0){
                                for(size_t i = 0; i<temp_coins.size(); i++){
                                    if (change >=ftt_coins[i].getDenomination() && ftt_coins[i].getCount() > 0){
                                        change -= ftt_coins[i].getDenomination();
                                        ftt_coins[i].decrementCount();
                                        temp_coins[i]->incrementCount();
                                        continue;
                                    }
                                }
                            }
                            // successful purchase decrement the stock we have left
                            item->on_hand -=1;
                            cout<<"Here is your item"<<item->name<<"and change of ";
                            float temp = (float)change/100;
                            printf("%.2f: ",temp);
                            for(auto &i:temp_coins)
                            {
                                if (i->getCount() > 0){
                                    for(int x =0; x<i->getCount(); x++){
                                        // print with either the "$" or "c"
                                        if(i->getDenomination() >= 100){
                                            cout<<"$ "<<i->getDenomination()/100<<" ";
                                        }else{
                                            cout<<i->getDenomination()/100<<"c ";
                                        }
                                    }
                                }
                            }
                        }
                    }else{
                        // to_pay was infact 0
                        // #### TODO ####
                        // dummy print statement, please change later
                        cout<<"Here's your "<<item->name<<""<<endl;
                        item->on_hand -=1;
                    }
                }
            }
        }
    }
}

void LinkedList::displayList() const {
    Node* current = head;
    while (current) {
        std::cout << "ID: " << current->data->id
                  << ", Name: " << current->data->name
                  << ", Price: $" << current->data->price.dollars << "." << current->data->price.cents
                  << ", On Hand: " << current->data->on_hand << std::endl;
        current = current->next;
    }
}

void LinkedList::deleteAllNodes() {
    Node* current = head;
    while (current) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    count = 0;
}

