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
    Store(std::string name, Address address);
    unsigned getId() const;
    std::string getName() const;
    Address getAddress() const;
    Product* getProduct(unsigned id) const;
    void setName(std::string name);
    void setAddress(Address address);
    void addProduct(Product *product);
    bool operator==(const Store &store) const;
    void showProducts() const;
    void showStore() const;
};


#endif //STORE_H
