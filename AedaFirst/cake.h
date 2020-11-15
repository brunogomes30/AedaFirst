#ifndef CAKE_H
#define CAKE_H

#include "product.h"

/**
 * Enumerated type for specifying each layer of the cake.
 */
enum layer {
    crispy, // crocante
    puff,   // massa folhada
    sponge  // massa de pão de ló
};

class Cake : public Product{
private:
    /**
     * First layer of the cake.
     */
    layer layer1;
    /**
     * Second Layer of the cake.
     */
    layer layer2;
public:
    Cake(std::string name, float price, Category category, layer layer1, layer layer2);
    layer getLayer1() const;
    layer getLayer2() const;
    /**
     * Print product in format:
     * <ID>  <CATEGORY>  <NAME>  <LAYER1> / <LAYER2>  <PRICE>
     */
    void showProduct() const override;

};


#endif //CAKE_H
