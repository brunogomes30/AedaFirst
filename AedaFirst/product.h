//
// Created by ultra on 27/10/2020.
//
#include<iostream>
#ifndef MAIN_CPP_PRODUCT_H
#define MAIN_CPP_PRODUCT_H

static int next_id = 1;
class Product {

private:

    unsigned int id;
    std::string name;
    float price;
public:
    Product(unsigned id);
    Product(std::string name, float price);

    int getId() const;
    std::string getName() const;
    float getPrice() const;

    bool operator== (const Product &product2) const;

};


#endif //MAIN_CPP_PRODUCT_H
