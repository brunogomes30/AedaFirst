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
    Store* store;
    std::vector<Product*> products;
    std::vector<unsigned> quantities;
    unsigned appraisal;
    bool discount;
    size_t findProduct(const Product &product);
public:
    Sale();
    void setClient(Client* client);
    void setStore(Store* store);
    void setProducts(std::vector<Product*> products, std::vector<unsigned> quantities);
    void addProduct(Product* product, unsigned qty);
    void setAppraisal(unsigned appraisal);
    void setDiscount(bool discount);
    Client* getClient() const;
    std::vector<Product*>& getProducts();
    std::vector<unsigned>& getQuantities();
    unsigned getAppraisal() const;
    /**
     * Print sale in format:
     * ID: <STORE_ID> Store: <STORE_NAME>
     * NIF: <CLIENT_NIF> Name: <CLIENT_NAME> Premium: <REGIME>
     * <PRODUCT_ID> <PRODUCT_NAME> <PRODUCT_PRICE> x <PRODUCT_QUANTITY>
     *
     * Total amount: <BILL>
     * Amount to pay after discount: <BILL_DISCOUNTED>
     * Client's appraisal: <APPRAISAL>
     */
    void showSale() const;
};

#endif //SALE_H
