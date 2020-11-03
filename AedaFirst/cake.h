//
// Created by ultra on 27/10/2020.
//

#ifndef MAIN_CPP_CAKE_H
#define MAIN_CPP_CAKE_H
#include "product.h"
#include <iostream>
enum layer {
    crispy = "crocante",
    puff = "massa folhada",
    sponge = "massa de pão de ló"
};
class Cake : public Product{
private:
    layer layer1;
    layer layer2;
public:
    Cake(std::string name, float price, layer layer1, layer layer2);
    layer getLayer1() const;
    layer getLayer2() const;

};


#endif //MAIN_CPP_CAKE_H
