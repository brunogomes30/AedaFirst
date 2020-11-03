//
// Created by ultra on 03/11/2020.
//

#include "bread.h"

Bread::Bread(std::string name, float price, sizeType size):Product(name, price) {
    this->size = size;
}


sizeType Bread::getSize() {
    return size;
}