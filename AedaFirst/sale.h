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
    unsigned id;
    Client* client;
    Store* store;
    Employee* employee;
    /**
     * Map of pairs that represent <product_pointer, <quantity, price_at_time>>
     */
    std::map<Product*, std::pair<unsigned, float>> products;
    unsigned appraisal;
    float discount;
    float totalAmount;
public:
    const static std::string FILENAME;
    Sale();

 	Sale(Client* client, Store* store);
	Sale(const std::map<std::string, std::string> &mapping,
         const std::map<unsigned, Store *>  &storesMapping,
         const std::map<unsigned, Employee *> &employeesMapping,
         const std::map<unsigned, Client *> &clientsMapping,
         const std::map<unsigned, Product *> &productsMapping);    void setStore(Store* store);
    void setClient(Client* client);
    void setEmployee(Employee* employee);
    void addProduct(Product* product, unsigned qty);
    void addProduct(Product* product, unsigned qty, float price);
    void setProducts(std::map<Product*, std::pair<unsigned, float>> &products, float totalAmount);
    void setAppraisal(unsigned appraisal);
    void setDiscount(float discount);
    Store* getStore() const;
    Client* getClient() const;
    Employee* getEmployee() const;
    std::map<Product*,std::pair<unsigned, float>>& getProducts();
    unsigned getAppraisal() const;
    float getDiscount() const;
    float getTotalAmount() const;
    /**
     *
     * @param client Pointer to client to be compared.
     * @return True if client of the sale has the same of <client>, false otherwise.
     */
    bool sameClient(Client* &client) const;
    /**
     * Print sale in format:\n\n
     *
     * ID: <STORE_ID> Store: <STORE_NAME> \n
     * <EMPLOYEE_NIF>  <EMPLOYEE_NAME> \n
     * <CLIENT_NIF>  <CLIENT_NAME>  <REGIME>\n\n
     *
     * <PRODUCT_ID> <PRODUCT_NAME> <PRODUCT_QUANTITY> x <PRODUCT_PRICE>\n\n
     *
     * Total amount: <BILL>\n
     * Discount: <DISCOUNT>%  Amount to pay: <BILL_DISCOUNTED>\n
     * Appraisal: <APPRAISAL>
     */
    void showSale(bool showAppraisal) const;

    friend std::ostream& operator<< (std::ostream &os, const Sale &sale);
};

#endif //SALE_H
