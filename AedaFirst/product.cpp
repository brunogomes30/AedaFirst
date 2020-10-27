//
// Created by ultra on 27/10/2020.
//

#include "product.h"

using namespace std;


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

bool Product::operator==(const Product &product){
    return id == product.getId();
}

