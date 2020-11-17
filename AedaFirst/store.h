#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <vector>
#include "product.h"
#include "employee.h"

struct Address{
  std::string street;
  std::string locality;
};

static unsigned store_next_id = 1;

class Store {
private:
    unsigned id;
    std::string name;
    Address address;
    std::vector<Product*> products;
    std::vector<Employee*> employees;
    bool status;
public:
    static const std::string FILENAME;
    Store(unsigned id);
    Store(std::string name, Address address);
 	Store(unsigned int id, std::string name, Address address);

    /**
    * The constructor to use when loading from file
    * @param mapping
    */
    Store(const std::map<std::string, std::string> &mapping,
          const std::map<unsigned, Product*> &productsMapping,
          const std::map<unsigned, Employee*> &employeesMapping);

    /**
     *
     * @return Store's ID.
     */
    unsigned getId() const;

    /**
     *
     * @return Store's name.
     */
    std::string getName() const;
    /**
     *
     * @return Store's address.
     */
    Address getAddress() const;
    friend std::ostream& operator<< (std::ostream &os, Store &store);
    friend std::istream& operator>> (std::istream &is, Store &store);

    /**
     *
     * @param id ID of the searched product.
     * @return Pointer to the product with ID <id> if found, nullptr otherwise.
     */
    Product* getProduct(unsigned id) const;
    /**
     *
     * @return Vector with employees linked to the store.
     */
    std::vector<Employee*> getEmployees() const;
    /**
     *
     * @param name New name of the store.
     */
    void setName(const std::string &name);
    /**
     *
     * @param address New address of the store.
     */
    void setAddress(const Address &address);
    /**
     * Add a product to the products available in the store.
     * @param product Pointer to product to be added to the store.
     */
    void addProduct(Product* product);
    /**
     *
     * @param products Vector of pointers to products to be added to the store.
     */
    void addAllProducts(const std::vector<Product*> &products);
    /**
     *
     * @param employee Pointer to employee to be added to the store.
     */
    void addEmployee(Employee *employee);
    /**
     *
     * @param employee Pointer to the employee to be removed
     */
    void removeEmployee(Employee *employee);
    /**
     *
     * @param product Pointer to the product to be removed
     */
    void removeProduct(Product *product);
    /**
     *
     * @param id ID of searched product
     * @return True if the store has the searched product, false otherwise.
     */
    bool findProduct(const unsigned &id) const;
    /**
     *
     * @return Pointer to employee with less orders.
     */
    Employee* lessOrdered() const;
    /**
     *
     * @param store Store to be compared.
     * @return True if both stores has the same ID, false otherwise.
     */
    bool operator==(const Store &store) const;
    /**
     *
     * @param store Store to be compared.
     * @return True if ID of the first is smaller than of the second.
     */
    bool operator<(const Store &store) const;
    /**
     * Print all products available in the store in format:
     * <ID>  <CATEGORY>  <NAME>  <DETAILS>  <PRICE> euros
     */
    void showProducts() const;
    /**
     * print all employees in the store in format:
     * <NIF>  <NAME>  <SALARY>  <N. ORDERS>
     */
    void showEmployees() const;
    /**
     * Print store info in format:
     * ID: <STORE_ID> Store: <STORE_NAME>
     */
    void showStore() const;

    bool getStatus() const;

    //void Store::statistics(const std::vector<Sale*> &sales) const;
};


#endif //STORE_H
