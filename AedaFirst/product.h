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
    /**
     * ID of the next product to be created.
     */
    static unsigned next_id;
    /**
     * ID of the product.
     */
    unsigned id;
    /**
     * Name of the product.
     */
    std::string name;
    /**
     * Price of the product
     */
    float price;
    /**
     * Category of the product.
     */
    Category category;
    /**
     * Activation status of the product. True if it was not removed.
     */
    bool status;
public:
    /**
     * Initialize empty class base.
     */
    Product();
    /**
     * Initialize product with a respective name, price and category.
     * @param name Name of the product.
     * @param price Price of the product.
     * @param ctg Category of the product.
     */
    Product(std::string name, float price, Category ctg);
    /**
     *
     * @return ID of the product
     */
    unsigned getId() const;
    /**
     *
     * @return Name of the product.
     */
    std::string getName() const;
    /**
     *
     * @return Price of the product
     */
    float getPrice() const;
    /**
     *
     * @return Category (bread or cake) of the product.
     */
    Category getCategory() const;
    /**
     *
     * @return True if product was not removed, false otherwise.
     */
    bool getStatus() const;
    /**
     *
     * @param name New name of the product.
     */
    void setName(std::string &name);
    /**
     *
     * @param price New price of the product
     */
    void setPrice(float &price);
    /**
     *
     * @param status True for valid product, false for removed product.
     */
    void setStatus(bool status);
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
