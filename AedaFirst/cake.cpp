//
// Created by ultra on 27/10/2020.
//

#include "cake.h"

Cake::Cake(std::string name, float price, layer layer1, layer layer2):Product(name, price) {
    this->layer1 = layer1;
    this->layer2 = layer2;
}

layer Cake::getLayer1() const {
    return layer1;
}

layer Cake::getLayer2() const {
    return layer1;
}