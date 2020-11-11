#ifndef SALE_H
#define SALE_H

#include <iostream>
#include <vector>
#include <map>
#include "client.h"

static unsigned next_sale_id = 1;

class Sale {
private:
    unsigned sale_id;
    Client* client;
    Store* store;
    /**
     * Map of pairs that represent <product_pointer, <quantity, current_price>>
     */
    std::map<Product*, std::pair<unsigned, float>> products;
    unsigned appraisal;
    bool discount;
    float totalAmount;
public:
    Sale();
    void setClient(Client* client);
    void setStore(Store* store);
    void addProduct(Product* product, unsigned qty);
    void setAppraisal(unsigned appraisal);
    void setDiscount(bool discount);
    Store* getStore() const;
    Client* getClient() const;
    std::map<Product*,std::pair<unsigned, float>>& getProducts();
    unsigned getAppraisal() const;
    float getTotalAmount() const;
    bool sameClient(Client* &client) const;
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
