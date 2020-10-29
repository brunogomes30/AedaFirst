#ifndef SALE_H
#define SALE_H

#include <iostream>
#include <vector>
#include "client.h"

static unsigned next_sale_id = 1;

class Sale {
private:
    unsigned sale_id;
    Client* client;
    std::vector<Product*> products;
    std::vector<unsigned> quantities;
    unsigned appraisal;
    bool discount;
    size_t findProduct(const Product &product);
public:
    Sale();
    void setClient(Client* client);
    void setProducts(std::vector<Product*> products, std::vector<unsigned> quantities);
    void addProduct(Product* product, unsigned qty);
    void setAppraisal(unsigned appraisal);
    Client* getClient() const;
    std::vector<Product*> getProducts() const;
    std::vector<unsigned> getQuantities() const;
    unsigned getAppraisal() const;
};

#endif //SALE_H
