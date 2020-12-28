#ifndef BREAD_H
#define BREAD_H

#include "product.h"
#include <map>

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
     * Specifies the size of the bread (small or big).
     */
    SizeType size;
public:
    /**
     * Name of the file in data directory (cakes.txt).
     */
    static const std::string FILENAME;
    /**
     * The constructor to use when loading from file.
     * @param mapping Pairs whose first element identifies the attribute and second has its data.
     */
    Bread(const std::map<std::string, std::string> &mapping);
    /**
     * Initialize bread setting its ID, name, price, category and size.
     * @param name Name of the bread.
     * @param price Price of the bread.
     * @param size Size (small or big) of the bread.
     */
    Bread(std::string name, float price, SizeType size, unsigned presences=0);

    SizeType getSize();
    /**
     * Print product in format:\n
     * <ID>  <CATEGORY>  <NAME>  <SIZE>  <PRICE>
     */
    void showProduct() const override;
    /**
     * Write bread in the file.
     * @param os Stream where to save.
     * @param bread Bread to be saved.
     * @return Stream where was saved.
     */
    friend std::ostream& operator<< (std::ostream &os, Bread &bread);
};


#endif //BREAD_H
