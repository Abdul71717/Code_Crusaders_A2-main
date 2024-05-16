#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Node.h"
#include "LinkedList.h"

using std::cout;
using std::endl;
/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void print_usage() {
    std::cout << "Usage: ./ftt <foodsfile> <coinsfile>\n"
              << "Commands:\n"
              << "  --help: Display this help message\n"
              << "  load <foodsfile>: Load foods from the specified file\n"
              << "  remove <food_id>: Remove the food item with the specified ID\n"
              << "  add <food_id> <name> <description> <price>: Add a new food item\n";
}


void print_menu(){
    cout << "Main Menu:" << endl;
    // these should be indented \t is for indenting
    cout << "\t1. Display Meal Options" <<endl;
    cout << "\t2. Purchase Meal" <<endl;
    cout << "\t3. Save and Exit" <<endl;
    cout << "Administrator-Only Menu:" <<endl;
    // thes should also be indented \t is for indenting
    cout << "\t4. Add Food" <<endl;
    cout << "\t5. Remove Food" <<endl;
    cout << "\t6. Display Balance" <<endl;
    cout << "\t7. Abort Program" <<endl;
    cout << "Select your option (1-7) :" <<endl;
};

std::string take_input(){
    std::string input;
        std::getline(std::cin, input);
        std::cout<<std::endl;
        if (std::cin.eof()){
            std::cout<<"ctrl+d was detected, quitting"<<std::endl;
        }
    return input;
}


int take_main_menu_input(){
    bool valid_input = false;
    int ret = -1;
    while (!valid_input){
        // while the user has not provided valid input, keep prompting for input
        print_menu();
        
        std::string user_input = take_input();
        try{
            if (std::cin.eof()){
            //  check for end of file character (ctrl^d)
                throw std::invalid_argument("Input was EOF character");
            }
            try{
                // parse the string input as a number (this can throw an error hence it is wrapped in a try-catch statement)
                int user_input_as_num = stoi(user_input);
                if(user_input_as_num >= 1 || user_input_as_num <= 7){
                    valid_input = true;
                    ret = user_input_as_num;
                }else{
                    cout<<"you entered a number which is out of the range of the valid options"<<endl;
                }
            }catch(std::invalid_argument &e){
                // not a valid input, the user entered a letter
                cout<<"You did not enter a number\n"<<endl;
                
            }
        }catch(std::invalid_argument &e){
            ret = -1;
            valid_input = true;
        }
    }
    return ret;
}

bool load_foods(const std::string &foodsfile, LinkedList &list) {
    std::ifstream file(foodsfile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open foods data file: " << foodsfile << "\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string id, name, description, price_str;
        std::getline(stream, id, '|');
        std::getline(stream, name, '|');
        std::getline(stream, description, '|');
        std::getline(stream, price_str, '|');

        try {
            size_t pos = price_str.find('.');
            if (pos == std::string::npos) {
                throw std::invalid_argument("Invalid price format");
            }
            unsigned dollars = std::stoi(price_str.substr(0, pos));
            unsigned cents = std::stoi(price_str.substr(pos + 1));
            unsigned total_cents = dollars * 100 + cents;
            list.addNode(new Node(id, name, description, (double)(total_cents/100)));
        } catch (const std::invalid_argument &) {
            std::cerr << "Error: Invalid format in foods data file\n";
            return false;
        }
    }
    return true;
}

bool load_coins(const std::string &coinsfile, std::vector <Coin> coins) {
    std::ifstream file(coinsfile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open coins data file: " << coinsfile << "\n";
        return false;
    }

    std::string line;
    
        // Coin loading logic
        std::ifstream coinFileStream(coinsfile);
        if (!coinFileStream) {
            std::cerr << "Error: Cannot open coins file " << coinsfile << std::endl;
            exit(EXIT_FAILURE);
        }
        
        while (std::getline(coinFileStream, line)) {
            std::stringstream ss(line);
            int count;
            int denomination;

            if (ss >> denomination && ss.get() == ',' && ss >> count) {

                Denomination denom = Coin::castToDenom(denomination);
                coins.push_back(Coin(denom, count));

            } else {
                std::cerr << "Error: Invalid format in coins file" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    
    return true;
}
void handle_command(const std::string& command, LinkedList& list) { 
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;
    std::cout << "Command: " << cmd << std::endl; // Debug

    if (cmd == "add") {
        std::string id, name;
        std::string description;
        double price;
        iss >> id >> name;
        std::getline(iss, description);
        iss >> price;
        description = description.substr(1); // Remove leading space
        std::cout << "Parsed add command: id=" << id << ", name=" << name << ", description=" << description << ", price=" << price << std::endl; // Debug

        FoodItem* item = new FoodItem{id, name, description, {static_cast<unsigned>(price), static_cast<unsigned>((price - static_cast<unsigned>(price)) * 100)}, DEFAULT_FOOD_STOCK_LEVEL};
        list.addNode(item);
    } else if (cmd == "remove") {
        std::string id;
        iss >> id;
        std::cout << "Parsed remove command: id=" << id << std::endl; // Debug
        if (!list.removeNode(id)) {
            std::cerr << "Failed to remove item with ID " << id << std::endl;
        }
    } else if (cmd == "display") {
        std::cout << "Displaying list:" << std::endl; // Debug
        list.displayList();
    } else {
        std::cerr << "Unknown command: " << cmd << std::endl;
        print_usage();
    }
}


int main(int argc, char **argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <foodsfile> <coinsfile>" << std::endl;
        return EXIT_FAILURE;
    }
    
    /*
        take input as long as the user hasn't requested the input for exiting or abort
        boolean value = True
        while loop which checks value = true
            input = take_input
            try{
                input_as_num = stoi(input);
            }catch(std::invalid_argument &e){
                cout<<"Some error message"<<endl;
            }

            if input == 3 || input == 7:
                value = false;
                // end everything as user wanted to abort/ exit
                return 0; 
            some_other_function(input); 
            value = false when user enter the exit input
    */

    LinkedList list;
    //  use a vector for simplicity there's no need for a coin array 
    std::vector<Coin> coins;
    
    if (!load_foods(argv[1], list)) {
        std::cerr << "Failed to load foods from " << argv[1] << std::endl;
        return EXIT_FAILURE;
    }

    if (!load_coins(argv[2], coins)) {
        std::cerr << "Failed to load coins from " << argv[2] << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Files provided: " << argv[1] << ", " << argv[2] << std::endl;

    
   int input_num = take_main_menu_input();
    while(input_num != -1 && input_num !=3 && input_num !=7){
        if(input_num ==1){
            // TODO
            cout<<"Display meal options"<<endl;
            input_num = take_main_menu_input();
        }else if (input_num == 2){
            // TODO
            list.purchaseItems(coins);
            input_num = take_main_menu_input();
        }else if (input_num==4){
            // TODO
            cout<<"Add food"<<endl;
            input_num = take_main_menu_input();
        }else if (input_num==4){
            // TODO
            cout<<"Remove Foode"<<endl;
            input_num = take_main_menu_input();
        }else if (input_num==4){
            // TODO
            cout<<"Display Balance"<<endl;
            input_num = take_main_menu_input();
        }
        
    }
    // printing out the different scenarios under which the while loop would exit (i.e. the user wants to exit)
    if (input_num == -1){
            // should never happen as the while loop should run infinitely until valid input is given
            cout<<"detected EOF, exiting gracefuly"<<endl;
            // exit main gracefully
            return 0;
    }else if (input_num == 3){
        
        cout<<"Exiting the program"<<endl;
        return 0;
    }else if (input_num == 7){
        
        cout<<"Aborting the program"<<endl;
    }


    // Continue with program initialization
    std::cout << "Files provided: " << argv[1] << ", " << argv[2] << std::endl;

    // Initialization and loading logic here

    return EXIT_SUCCESS;
}
