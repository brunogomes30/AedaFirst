#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>


/**
 * Enumerated type for specifying the category of product.
 */
enum Category {
    bread,
    cake
};

class Product {
protected:
    static unsigned next_id;
    unsigned id;
    std::string name;
    float price;
    Category category;
    bool status;
public:
    Product();
    Product(unsigned int id);
    Product(unsigned int id, std::string name, float price, Category ctg);
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

    bool getStatus() const;
    void setStatus(bool status);

};

#endif //PRODUCT_H
