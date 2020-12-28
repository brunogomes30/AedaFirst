#ifndef CAKE_H
#define CAKE_H

#include "product.h"
#include <map>
/**
 * Enumerated type for specifying each layer of the cake.
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
    /**
     * Name of the file in data directory (bread.txt).
     */
    static const std::string FILENAME;
    /**
     * The constructor to use when loading from file.
     * @param mapping Pairs whose first element identifies the attribute and second has its data.
     */
    Cake(const std::map<std::string, std::string> &mapping);
    /**
     * Initialize cake setting its ID, name, price, category and layers.
     * @param name Name of the cake.
     * @param price Price of the cake.
     * @param layer1 First layer of the cake.
     * @param layer2 Second layer of the cake.
     */
    Cake(std::string name, float price, Layer layer1, Layer layer2, unsigned presences=0);

    Layer getLayer1() const;
    Layer getLayer2() const;
    /**
     * Print product in format:\n
     * <ID>  <CATEGORY>  <NAME>  <LAYER1> / <LAYER2>  <PRICE>\n
     */
    void showProduct() const override;
    /**
     * Write cake in the file.
     * @param os Stream where to save.
     * @param cake Cake to be saved.
     * @return Stream where was saved.
     */
    friend std::ostream& operator<< (std::ostream &os, Cake &cake);
};


#endif //CAKE_H
