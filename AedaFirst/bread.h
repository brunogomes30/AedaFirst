#ifndef BREAD_H
#define BREAD_H

#include "product.h"
/**
 * Enumerated type for specifying the size of the bread.
 */
enum sizeType{
    small,
    big
};

class Bread : public Product {
private:
    /**
     * Specifies the size of the bread.
     */
    sizeType size;

public:
    Bread(std::string name, float price, Category category, sizeType size);
    sizeType getSize();
    /**
     * Print product in format:
     * <ID>  <CATEGORY>  <NAME>  <SIZE>  <PRICE>
     */
    void showProduct() const override;
};


#endif //BREAD_H
