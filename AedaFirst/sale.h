#ifndef SALE_H
#define SALE_H

#include <iostream>
#include <vector>
#include <map>
#include "store.h"
#include "client.h"
#include "employee.h"



class Sale {
private:
    /**
     * ID of the next order to be done.
     */
    static unsigned next_sale_id;
    /**
     * ID of the sale.
     */
    unsigned id;
    /**
     * Client who made the order.
     */
    Client* client;
    /**
     * Store where was made the sale.
     */
    Store* store;
    /**
     * Employee who made the sale.
     */
    Employee* employee;
    /**
     * Map of pairs that represent <product_pointer, <quantity, price_at_time>>
     */
    std::map<Product*, std::pair<unsigned, float>> products;
    /**
     * Appraisal of the order, given by the client.
     */
    unsigned appraisal;
    /**
     * Percentage of total amount that client has to pay.
     */
    float discount;
    /**
     * Sum of the amount to pay by each product.
     */
    float totalAmount;
public:
    /**
     * Name of the file in data directory (sales.txt).
     */
    const static std::string FILENAME;
    /**
     * The constructor to use when loading from file.
     * @param mapping Pairs whose first element identifies the attribute and second has its data.
     * @param storesMapping Map with stores values.
     * @param employeesMapping Map with employees values.
     * @param clientsMapping Map with clients values.
     * @param productsMapping Map with products values.
     */
    Sale(const std::map<std::string, std::string> &mapping,
         const std::map<unsigned, Store *>  &storesMapping,
         const std::map<unsigned, Employee *> &employeesMapping,
         const std::map<unsigned, Client *> &clientsMapping,
         const std::map<unsigned, Product *> &productsMapping);
    /**
     * Initialize setting only the total amount to 0.
     */
    Sale();
    /**
     * Initialize sale setting its client and store.
     * @param client Client who made the order.
     * @param store Store where was made the sale.
     */
 	Sale(Client* client, Store* store);

	void setStore(Store* store);
    void setClient(Client* client);
    /**
     *
     * @param employee Employee who made the sale.
     */
    void setEmployee(Employee* employee);
    /**
     * If product was already chose, their quantities are summed.
     * Price is setting with the current price of the product.
     * @param product Product to be added to the order.
     * @param qty Quantity of products <product>.
     */
    void addProduct(Product* product, unsigned qty);
    /**
     * If product was already chose, their quantities are summed.
     * @param product Product to be added to the order.
     * @param qty Quantity of products <product>.
     * @param price Price of the product. May not be the current price.
     */
    void addProduct(Product* product, unsigned qty, float price);
    /**
     * Set all products in the order and define the total amount.
     * @param products Structure with products, quantities and prices of the products at the time.
     * @param totalAmount Sum of the amount to pay for each product.
     */
    void setProducts(std::map<Product*, std::pair<unsigned, float>> &products, float totalAmount);
    /**
     *
     * @param appraisal Appraisal of the sale given by a client.
     */
    void setAppraisal(unsigned appraisal);
    /**
     *
     * @param discount Percentage to pay of the total amount.
     */
    void setDiscount(float discount);
    /**
     *
     * @return ID of the sale.
     */
    unsigned getId() const;
    /**
     *
     * @return  Pointer to the store where was mada the the sale.
     */
    Store* getStore() const;
    /**
     *
     * @return Pointer to the client who made the order.
     */
    Client* getClient() const;
    /**
     *
     * @return Pointer to the employee who made the sale.
     */
    Employee* getEmployee() const;
    /**
     *
     * @return Structure with the products bought in the sale.
     */
    std::map<Product*,std::pair<unsigned, float>>& getProducts();
    unsigned getAppraisal() const;
    /**
     *
     * @return Percentage to pay of the total amount.
     */
    float getDiscount() const;
    /**
     *
     * @return Sum of the amount to pay for each product, whitout discount.
     */
    float getTotalAmount() const;
    /**
     * Compare the client who mada the order with the <client>
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
    /**
     * Write sale in the file.
     * @param os Stream where to save.
     * @param sale Sale to be saved.
     * @return Stream where was saved.
     */
    friend std::ostream& operator<< (std::ostream &os, const Sale &sale);
};

#endif //SALE_H
