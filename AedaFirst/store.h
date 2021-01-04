#ifndef STORE_H
#define STORE_H

#include <iostream>
#include <vector>
#include <unordered_set>
#include "product.h"
#include "employee.h"

struct Address{
  std::string street;
  std::string locality;
};


class Store {
private:
    /**
     * ID of the next store to be created.
     */
    static unsigned store_next_id;
    /**
     * ID of the store.
     */
    unsigned id;
    /**
     * Name of the store.
     */
    std::string name;
    /**
     * Structure with the street and locality of the store.
     */
    Address address;
    /**
     * Products belonging to the store.
     */
    std::vector<Product*> products;
    /**
     * Employees who work at the store.
     */
    std::unordered_set<EmployeePtr, hashEmployee, equalityEmployee> employees;

public:
    /**
     * Name of the file in data directory (stores.txt).
     */
    static const std::string FILENAME;
    /**
     * The constructor to use when loading from file.
     * @param mapping Pairs whose first element identifies the attribute and second has its data.
     * @param productsMapping Map with products values.
     * @param employeesMapping Map with employees values.
     */
    Store(const std::map<std::string, std::string> &mapping,
          const std::map<unsigned, Product*> &productsMapping,
          const std::map<unsigned, Employee*> &employeesMapping);
    /**
     * Initialize store setting its name, street and locality.
     * @param name Name of the store.
     * @param address Structure with the street and locality.
     */
    Store(std::string name, Address address);
    /**
     *
     * @return Id of the store.
     */
    unsigned getId() const;
    /**
     *
     * @return Name of the store.
     */
    std::string getName() const;
    /**
     *
     * @return Address of the store.
     */
    Address getAddress() const;
    /**
     *
     * @return Vector of pointers to products in store.
     */
    std::vector<Product *> getProducts() const;
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
    //std::vector<Employee*> getEmployees() const;
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
     * Add several products to the products available in the store.
     * @param products Vector of pointers to products to be added to the store.
     */
    void addAllProducts(const std::vector<Product*> &products);
    /**
     * Add an employee to the employees linked to the store.
     * @param employee Pointer to employee to be added to the store.
     */
    void addEmployee(Employee *employee);
    /**
     * Removes an employee from the store.
     * @param employee Pointer to the employee to be removed.
     * @return True if the employee was removed.
     */
    bool removeEmployee(Employee *employee);
    /**
     * Removes a product from the store.
     * @param product Pointer to the product to be removed.
     */
    void removeProduct(Product *product);
    /**
     * Search for a product in products available in the store.
     * @param id ID of searched product.
     * @return True if the store has the searched product, false otherwise.
     */
    bool findProduct(const unsigned &id) const;
    /**
     * Search for the employee linked to the store with less sales made.
     * @return Pointer to employee with less orders.
     */
    Employee* lessOrdered() const;
    /**
     * Compare two stores.
     * @param store Store to be compared.
     * @return True if both stores has the same ID, false otherwise.
     */
    bool operator==(const Store &store) const;
    /**
     * Compare two stores.
     * @param store Store to be compared.
     * @return True if ID of the first is smaller than of the second.
     */
    bool operator<(const Store &store) const;
    /**
     * Print all products available in the store in format:
     * <ID>  <CATEGORY>  <NAME>  <DETAILS>  <PRICE>
     */
    void showProducts() const;
    /**
     * Print all employees in the store in format:
     * <NIF>  <NAME>  <SALARY>  <NUM_ORDERS>
     */
    void showEmployees(const unsigned &order);
    /**
     * Print store info in format:\n
     * ID: <STORE_ID> Store: <STORE_NAME>
     */
    void showStore() const;
    /**
     * Increases wages of employees by 2% that have delivered at least the minNumber
     * @param minNumber
     */
    void increaseWages(unsigned minNumber);
    /**
     * Write store in the file.
     * @param os Stream where to save.
     * @param store Store to be saved.
     * @return Stream where was saved.
     */
    friend std::ostream& operator<< (std::ostream &os, Store &store);
};
#endif //STORE_H
