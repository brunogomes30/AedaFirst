#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include "store.h"
#include "client.h"
#include "product.h"
#include "bread.h"
#include "cake.h"
#include "sale.h"
#include "algorithm"

/**
 * Print all stores passed as an argument in table format.
 * @param stores Vector of pointers to object Store.
 */
void showStores(const std::vector<Store*> &stores);
/**
 * Print all clients passed as an argument in table format.
 * @param clients Vector of pointers to object Client.
 */
void showClients(const std::vector<Client*> &clients);
/**
 * Print all employees of all stores passed as an argument in table format, ordered by store.
 * @param stores Vector of pointers to object Store.
 */
void showEmployees(const std::vector<Store*> &stores, const unsigned &order = 1);
/**
 * Print all products passed as an argument in table format.
 * @param products Vector of pointers to object Product.
 */
void showProducts(const std::vector<Product*> &products);
/**
 * Print a bar chart according to the most selling product.
 * @param sales Vector of pointers to object Sale.
 * @param store Store to see the statistics.
 */
void showStoreStatistics(const std::vector<Sale *> &sales, const Store *store);
/**
 * Print possible operations in Main Menu and respective input keys.
 */
void showMenuOperations();
/**
 * Print possible operations in Store Menu and respective input keys.
 */
void showStoreOperations();
/**
 * Print possible operations in Client Menu and respective input keys.
 */
void showClientOperations();
/**
 * Print possible operations in Employee Menu and respective input keys.
 */
void showEmployeeOperations();
/**
 * Print possible operations in Product Menu and respective input keys.
 */
void showProductOperations();
/**
 * Transform string in lower case.
 * @param str String to be transformed.
 * @return New string.
 */
std::string toLower(std::string str);
/**
 * Asks user for an ID.
 * @param id Save the user answer.
 * @param object String with text to complement outputs.
 */
void askId(unsigned &id, std::string object);
/**
 * Asks user for a name or a nif.
 * @param identifier Save the user answer.
 * @param person String with text to complement outputs.
 */
void askPersonData(std::string &identifier, std::string person);
/**
 * Asks user for an address.
 * @param address Save the user answer.
 */
void askAddress(Address &address);
/**
 * Asks user for a name.
 * @param name Save the user answer.
 * @param object String with text to complement outputs.
 */
/**
 * Asks user for the minimum number of deliveries of the employees to increase their salary
 * @param minNumber
 */
void askMinNumber(unsigned &minNumber);
void askName(std::string &name, std::string object);
/**
 * Asks user for a nif of a person.
 * @param nif Save the user answer.
 * @param object String with text to complement outputs.
 */
void askNif(unsigned &nif, std::string object);
/**
 * Asks user for a regime of a client.
 * @param regime Save the user answer.
 */
void askRegime(bool &regime);
/**
 * Asks user for a salary or a price of an employee or a product, respectively.
 * @param price_salary Save the user answer.
 * @param object String with text to complement outputs.
 */
void askSalaryOrPrice(float &price_salary, std::string object);
/**
 * Asks user for a category of a product.
 * @param ctg Save the user answer.
 */
void askCategory(Category &ctg);
/**
 * Asks user for a size of a bread.
 * @param size Save the user answer.
 */
void askBreadSize(SizeType &size);
/**
 * Asks user for a Layer of a cake.
 * @param ly Save the user answer.
 * @param object String with text to complement outputs.
 */
void askCakeLayer(Layer &ly, std::string object);
/**
 * Asks user for stores.
 * @param stores Vector with all possible stores to choose.
 * @param filterStores Vector, passed by reference, that will be modified with the chosen stores.
 */
void askStores(const std::vector<Store*> &stores, std::vector<Store*> &filterStores);
/**
 * Set a name and a address.
 * @param name Name of a store.
 * @param address Address of a store.
 */
void setStoreData(std::string &name, Address &address);
/**
 * Set a name, a NIF and a regime of a client.
 * @param name Name of a client.
 * @param nif NIF of a client.
 * @param regime Regime of a client
 */
void setClientData(std::string &name, unsigned &nif, bool &regime);
/**
 * Set a name, a nif, a salary of a employee and a store to he be linked to.
 * @param name Name of an employee.
 * @param nif NIF of an employee
 * @param salary Salary of an employee.
 * @param stores Stores where employee can be linked.
 * @param store Store linked to an employee.
 */
void setEmployeeData(std::string &name, unsigned &nif, float &salary, const std::vector<Store*> &stores, Store* &store);
/**
 * Set a name, a price, a category and a size or layers of a product.
 * @param name Name of a product.
 * @param price Price of a product.
 * @param ctg Category of a product.
 * @param size Size of a bread.
 * @param ly1 First layer of a cake.
 * @param ly2 Second layer of a cake.
 */
void setProductData(std::string &name, float &price, Category &ctg, SizeType &size, Layer &ly1, Layer &ly2);
/**
 * Search for a store by its ID.
 * @param stores  Vector of pointers to stores.
 * @param id ID of the store searched.
 * @return Pointer to the store with ID <id> if found in <stores>, nullptr otherwise.
 */
Store* searchStore(const std::vector<Store*> &stores, unsigned id);
/**
 * Search for a client by their name or NIF.
 * @param clients Vector of pointers to clients.
 * @param identifier Name or NIF of the client searched.
 * @return Pointer to the client with name or NIF <identifier> if found in <clients>, nullptr otherwise.
 */
Client* searchClient(const std::vector<Client*> &clients, const std::string &identifier);
/**
 * Search for an employee by their name or NIF.
 * @param employees Vector of pointers to employees.
 * @param identifier Name or NIF of the employee searched.
 * @return Pointer to the employee with name or NIF <identifier> if found in <employees>, nullptr otherwise.
 */
Employee* searchEmployee(const std::vector<Employee*> &employees, const std::string &identifier);
/**
 * Search for a product by its id.
 * @param products Vector of pointers to products.
 * @param id ID of the product searched.
 * @return Pointer to the product with ID <id> if found in <products>, nullptr otherwise.
 */
Product* searchProduct(const std::vector<Product*> &products, unsigned id);
/**
 * Asks user for the way he wants to order (ascending/descending).
 * @return True for descending order, false to ascending.
 */
bool order();
/**
 * Compare two pairs (sales volume) by its total value, quantity * price.
 * @param p1 First pair (sales volume) to be compared.
 * @param p2 Second pair (sales volume) to be compared.
 * @return True if total value of <p1> is smaller than that of <p2>, false otherwise.
 */
bool cmpByIncome(const std::pair<Product*, std::pair<unsigned, float>> &p1, const std::pair<Product*, std::pair<unsigned, float>> &p2);
/**
 * Compare two pairs (sales volume) by its quantity.
 * @param p1 First pair (sale volume) to be compared.
 * @param p2 Second pair (sale volume) to be compared.
 * @return True if quantity of <p1> is smaller than that of <p2>, false otherwise.
 */
bool cmpByQuantitySold(const std::pair<Product*, std::pair<unsigned, float>> &p1, const std::pair<Product*, std::pair<unsigned, float>> &p2);
/**
 * Sort pairs by its total value, quantity * price.
 * @param vProducts Vector of sales volume to be sorted.
 */
void sortByIncome(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);
/**
 * Sort pairs by its quantity.
 * @param vProducts Vector of sales volume to be sorted.
 */
void sortByQuantitySold(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);
/**
 * Compare two clients or two employees by their names.
 * @tparam T Template type in order to be used with Client and Employee objects.
 * @param person1 First person (client/employee) to be compared.
 * @param person2 Second person (client/employee) to be compared.
 * @return True if name of <person1> is alphabetically smaller than that of <person2>, false otherwise.
 */
template<class T>
bool cmpPersonsByName(T* &person1, T* &person2);
/**
 * Compare two clients or two employees by their NIFs.
 * @tparam T Template type in order to be used with Client and Employee objects.
 * @param person1 First person (client/employee) to be compared.
 * @param person2 Second person (client/employee) to be compared.
 * @return True if NIF of <person1> is smaller than that of <person2>, false otherwise.
 */
template<class T>
bool cmpPersonsByNif(T* &client1, T* &client2);
/**
 * Compare two employees by their salary.
 * @param employee1 First employee to be compared.
 * @param employee2 Second employee to be compared.
 * @return True if salary of the first is smaller than of the other
 */
bool cmpEmployeesBySalary(Employee* &employee1, Employee* &employee2);
/**
 * Compare two products by their IDs.
 * @param product1 First product to be compared.
 * @param product2 Second product to be compared.
 * @return True if ID of the first is smaller than of the second.
 */
bool cmpProductsById(Product* &product1, Product* &product2);
/**
 * Compare two products by their categories.
 * @param product1 First product to be compared.
 * @param product2 Second product to be compared.
 * @return True if category of the first is bread and the of the second is cake.
 * @return If both have the same category return true if the name of the first is alphabetically smaller than the name of the second, false otherwise.
 */
bool cmpProductsByCategory(Product* &product1, Product* &product2);
/**
 * Compare two products by their prices.
 * @param product1 First product to be compared.
 * @param product2 Second product to be compared.
 * @return True if price of the first is smaller than of the second.
 */
bool cmpProductsByPrice(Product* &product1, Product* &product2);
/**
 * Sort employees by their names.
 * @param employees Vector of employees' pointers.
 */
void sortEmployeesByName(std::vector<Employee*> &employees);
/**
 * Sort employees by their NIFs.
 * @param employees Vector of employees' pointers.
 */
void sortEmployeesByNif(std::vector<Employee*> &employees);
/**
 * Sort employees by their salaries.
 * @param employees Vector of employees' pointers.
 */
void sortEmployeesBySalary(std::vector<Employee*> &employees);
/**
 * Sort products by their IDs.
 * @param products Vector of products' pointers.
 */
void sortProductsById(std::vector<Product*> &products);
/**
 * Sort products by their categories and names.
 * @param products Vector of products' pointers.
 */
void sortProductsByCategory(std::vector<Product*> &products);
/**
 * Sort products by their prices.
 * @param products Vector of products' pointers.
 */
void sortProductsByPrice(std::vector<Product*> &products);
/**
 * Sort clients by their names.
 * @param clients Vector of clients to be sorted.
 */
void sortClientsByName(std::vector<Client*> &clients);
/**
 * Sort clients by their NIFs.
 * @param clients Vector of clients to be sorted.
 */
void sortClientsByNif(std::vector<Client*> &clients);
/**
 * Ask the user for the way to sort employees.
 * @return Number between 1-6. Each number represent a sort.
 */
unsigned chooseEmployeesSort();
/**
 * Ask the user for the way to sort products and sort them.
 * @param products Products to be sorted.
 */
void chooseProductsSort(std::vector<Product*> &products);
/**
 * Ask the user for the way to sort clients and sort them.
 * @param clients Clients to be sorted.
 */
void chooseClientsSort(std::vector<Client*> &clients);
/**
 * Asks user for the way he wants to sort <vProducts> and sort it.
 * @param vProducts Vector of volume sales.
 */
void chooseSalesVolumeByProductSort(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);

#endif //UTILITIES_H
