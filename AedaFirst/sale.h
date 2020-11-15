#ifndef SALE_H
#define SALE_H

#include <iostream>
#include <vector>
#include <map>
#include "client.h"
#include "employee.h"


static unsigned next_sale_id = 1;

class Sale {
private:
    unsigned sale_id;
    Client* client;
    Store* store;
    Employee* employee;
    /**
     * Map of pairs that represent <product_pointer, <quantity, current_price>>
     */
    std::map<Product*, std::pair<unsigned, float>> products;
    unsigned appraisal;
    float discount;
    float totalAmount;
public:
    Sale();
    void setStore(Store* store);
    void setClient(Client* client);
    void setEmployee(Employee* employee);
    void addProduct(Product* product, unsigned qty);
    void setAppraisal(unsigned appraisal);
    void setDiscount(float discount);
    Store* getStore() const;
    Client* getClient() const;
    Employee* getEmployee() const;
    std::map<Product*,std::pair<unsigned, float>>& getProducts();
    unsigned getAppraisal() const;
    float getDiscount() const;
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
    void showSale(bool showAppraisal) const;
};

#endif //SALE_H
