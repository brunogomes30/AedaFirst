//
// Created by ultra on 27/10/2020.
//

#include "product.h"

using namespace std;

Product::Product(unsigned id) {
    this->id = id;
}
Product::Product(string name, float price){
    this->id = next_id++;
    this->name = name;
    this->price = price;
}

int Product::getId() const{
    return id;
}

string Product::getName() const{
    return name;
}

float Product::getPrice() const{
    return price;
}

bool Product::operator==(const Product &product) const{
    return id == product.getId();
}

