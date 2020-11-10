#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <vector>
#include "product.h"

struct Address{
  std::string street;
  std::string locality;
};

static unsigned store_next_id = 1;

class Store {
private:
    unsigned store_id;
    std::string name;
    Address address;
    std::vector<Product*> products;
public:
    Store(unsigned id);
    Store(std::string name, Address address);
    unsigned getId() const;
    std::string getName() const;
    Address getAddress() const;
    /**
     *
     * @param id ID of the searched product.
     * @return Pointer to the product with ID id.
     */
    Product* getProduct(unsigned id) const;
    void setName(std::string name);
    void setAddress(Address address);
    /**
     * Add a product to the products available in the store.
     * @param product Pointer to Product object.
     */
    void addProduct(Product *product);
    bool findProduct(const unsigned &id) const;
    /**
     *
     * @param store Store to be compared.
     * @return True if both stores has the same ID, false otherwise.
     */
    bool operator==(const Store &store) const;
    bool operator<(const Store &store) const;
    /**
     * Print all products available in the store in format:
     * <PRODUCT_ID> -> <PRODUCT_NAME> <PRODUCT_PRICE> euros
     */
    void showProducts() const;
    /**
     * Print store info in format:
     * ID: <STORE_ID> Store: <STORE_NAME>
     */
    void showStore() const;
};


#endif //STORE_H