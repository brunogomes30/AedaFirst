#ifndef BREAD_H
#define BREAD_H

#include "product.h"
#include<map>
/**
 * Enumerated type for specifying the size of the bread.
 */
enum SizeType{
    small,
    big
};

class Bread : public Product {
private:
    /**
     * Specifies the size of the bread.
     */
    SizeType size;

public:
    static const std::string FILENAME;

    Bread(unsigned int id, std::string name, float price, SizeType size);
    Bread(std::string name, float price, SizeType size);

    /**
     * The constructor to use when loading from file
     * @param mapping
     */
    Bread(const std::map<std::string, std::string> &mapping);

    SizeType getSize();
    /**
     * Print product in format:
     * <ID>  <CATEGORY>  <NAME>  <SIZE>  <PRICE>
     */
    void showProduct() const override;

    friend std::ostream& operator<< (std::ostream &os, Bread &bread);
};


#endif //BREAD_H
