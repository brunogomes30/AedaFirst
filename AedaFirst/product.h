#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>

static int next_id = 1;

/**
 * Enumerated type for specifying the category of product.
 */
enum Category {
    bread,
    cake
};

class Product {
protected:
    unsigned id;
    std::string name;
    float price;
    Category category;
public:
    Product(unsigned id);
    Product(std::string name, float price, Category ctg);

    unsigned getId() const;
    std::string getName() const;
    float getPrice() const;
    Category getCategory() const;
    void setName(std::string &name);
    void setPrice(float &price);
    /**
     * Checks equality of two products.
     * @param product2 Product to be compared.
     * @return True if both products has the same ID, false otherwise.
     */
    bool operator== (const Product &product2) const;
    /**
     * Print product in format:
     * <ID>  <CATEGORY>  <NAME>
     */
    virtual void showProduct() const;
};

#endif //PRODUCT_H
