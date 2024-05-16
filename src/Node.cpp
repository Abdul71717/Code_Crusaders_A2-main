#include "Node.h"

Node::Node(FoodItem* item) : data(item), next(nullptr) {}

Node::~Node() {
    delete data;
}

Node::Node(const std::string& id, const std::string& name, const std::string& desc, double price)
    : next(nullptr) {
    data = new FoodItem();
    data->id = id;
    data->name = name;
    data->description = desc;
    data->price.dollars = static_cast<unsigned>(price);
    data->price.cents = static_cast<unsigned>((price - data->price.dollars) * 100);
    data->on_hand = DEFAULT_FOOD_STOCK_LEVEL;
}