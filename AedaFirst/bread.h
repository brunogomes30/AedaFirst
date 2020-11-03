//
// Created by ultra on 03/11/2020.
//

#ifndef MAIN_CPP_BREAD_H
#define MAIN_CPP_BREAD_H

#include "product.h"
#include <iostream>

enum sizeType{
    small = "pequeno",
    big = "grande"
};

class Bread : public Product{
private:
    sizeType size;

public:
    Bread(std::string name, float price, sizeType size);
    sizeType getSize();
};


#endif //MAIN_CPP_BREAD_H
