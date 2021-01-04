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
    /**
     * Number of presences in an order.
     */
     unsigned presences;
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
    Product(std::string name, float price, Category ctg, unsigned presences=0);
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
     * @return
     */
    unsigned getPresences() const;
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
     * Increments the number of presences in an order by 1.
     */
    void addPresence();
    /**
     * Checks equality of two products.
     * @param product2 Product to be compared.
     * @return True if both products has the same ID, false otherwise.
     */
    bool operator== (const Product &product2) const;
    /**
     * Print product in format:\n
     * <ID>  <CATEGORY>  <NAME>
     */
    virtual void showProduct() const;
};
/**
 * Class that represent a product
 */
class ProductPtr {
private:
    /**
     * Pointer to a product.
     */
    Product* product;
public:
    /**
     * Constructor of ProductPtr.
     * @param product Pointer to product.
     */
    ProductPtr(Product* product);
    /**
     *
     * @return Pointer to product.
     */
    Product* getProduct() const;
    /**
     *
     * @return Number of presences in sales.
     */
    unsigned getPresences() const;
    /**
     * Compare presences.
     * @param prd ProductPtr to compare with.
     * @return True if prd has more presences than the first.
     */
    bool operator<(const ProductPtr& prd) const;
};

#endif //PRODUCT_H
