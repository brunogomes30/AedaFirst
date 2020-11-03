//
// Created by ultra on 03/11/2020.
//

#include "bread.h"

Bread::Bread(int name, float price, int layer1, int layer2) {
    Product(name, price);
    this.layer1 = layer1;
    this.layer2 = layer2;
}


sizeType Bread::getSize() {
    return size;
}