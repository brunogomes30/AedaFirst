//
// Created by ultra on 03/11/2020.
//

#ifndef MAIN_CPP_BREAD_H
#define MAIN_CPP_BREAD_H

#include<iostream>
enum sizeType{
    small = "pequeno",
    big = "grande";
};

class Bread : public Product{
private:
    sizeType size;

public:
    Bread(std::string name, float price, layer layer1, layer layer2);
    sizeType getSize();
};


#endif //MAIN_CPP_BREAD_H
