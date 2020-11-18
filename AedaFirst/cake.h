#ifndef CAKE_H
#define CAKE_H

#include "product.h"
#include<map>
/**
 * Enumerated type for specifying each Layer of the cake.
 */
enum Layer {
    crispy, // crocante
    puff,   // massa folhada
    sponge  // massa de pão de ló
};

class Cake : public Product{
private:
    /**
     * First Layer of the cake.
     */
    Layer layer1;
    /**
     * Second Layer of the cake.
     */
    Layer layer2;
public:
    static const std::string FILENAME;

    /**
     * The constructor to use when loading from file
     * @param mapping
     */
    Cake(const std::map<std::string, std::string> &mapping);
    Cake(unsigned id, std::string name, float price, Layer layer1, Layer layer2);
    Cake(std::string name, float price, Layer layer1, Layer layer2);
    Layer getLayer1() const;
    Layer getLayer2() const;
    /**
     * Print product in format:
     * <ID>  <CATEGORY>  <NAME>  <LAYER1> / <LAYER2>  <PRICE>
     */
    void showProduct() const override;

    friend std::ostream& operator<< (std::ostream &os, Cake &cake);
};


#endif //CAKE_H
