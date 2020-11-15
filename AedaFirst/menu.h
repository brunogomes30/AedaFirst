#ifndef MENU_H
#define MENU_H

#include "store.h"
#include "sale.h"
#include "client.h"
#include "product.h"
#include "bread.h"
#include "cake.h"
#include "employee.h"


/**
 * Asks user for the way he wants to sort <clients> and sort it.
 * @param clients Vector of clients to be sorted.
 */
void chooseClientsSort(std::vector<Client*> &clients);
/**
 * Asks user for the way he wants to sort <vProducts> and sort it.
 * @param vProducts Vector of volume sales.
 */
void chooseSalesVolumeByProductSort(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);
/**
 * Store Menu
 * @param stores Vector of pointers to all stores.
 * @param store Pointer to the store chose by user.
 * @param sales Vector of pointers to all sales.
 * @param products Vector of pointers to all products.
 */
void opsStore(std::vector<Store*> &stores, Store* &store, std::vector<Sale*> &sales, const std::vector<Product*> &products);
/**
 * Print client's history (opinion, points, number of orders, total money spent, number of discunts used, total money saved with discounts).
 * @param client  Pointer to the client chose by user.
 * @param sales Vector of pointers to all sales.
 */
void clientHistory(Client* &client, const std::vector<Sale*> &sales);
/**
 * Client Menu
 * @param clients Vector of pointers to all clients.
 * @param oldClients Vector of pointers to clients removed.
 * @param client Pointer to the client chose by user.
 * @param sales Vector of pointers to all sales.
 */
void opsClient(std::vector<Client*> &clients, std::vector<Client*> &oldClients, Client* &client, const std::vector<Sale*> &sales);
/**
 * Employee Menu
 * @param stores Vector of pointers to all stores.
 * @param employees Vector of pointers to all employees.
 * @param oldEmployees Vector of pointers to employees removed.
 * @param employee Pointer to the employee chose by user
 */
void opsEmployee(std::vector<Store*> &stores, std::vector<Employee*> employees, std::vector<Employee*> oldEmployees, Employee* employee);
/**
 * Product Menu
 * @param products Vector of pointers to all products.
 * @param oldProducts Vector of pointers to products removed.
 * @param stores Vector of pointers to all stores.
 * @param product Pointer to the product chose by the user.
 */
void opsProduct(std::vector<Product*> &products, std::vector<Product*> &oldProducts, std::vector<Store*> &stores, Product* &product);
/**
 * Make an order. Asks for a client, a store, products client appraisal.
 * @param stores Vector of pointers to all stores.
 * @param clients Vector of pointers to all clients.
 * @param sale Sale to be created;
 */
void makeOrder(const std::vector<Store*> &stores, const std::vector<Client*> &clients, Sale &sale);
/**
 * Print sales volume by product.
 * @param sales Vector of pointers to all sales.
 */
void salesVolumeByProduct(const std::vector<Sale*> &sales);
/**
 * Print sales volume by store.
 * @param sales Vector of pointers to all sales.
 * @param stores Vector of pointers to all stores.
 */
void salesVolumeByStore(const std::vector<Sale*> &sales, const std::vector<Store*> &stores);
/**
 * Sales Volume Menu
 * @param sales Vector of pointers to all sales.
 * @param stores Vector of pointers to all stores.
 */
void opsSalesVolume(const std::vector<Sale*> &sales, const std::vector<Store*> &stores);
/**
 * Sales Menu
 * @param sales Vector of pointers to all sales.
 * @param stores Vector of pointers to all stores.
 * @param clients Vector of pointers to all clients.
 */
void opsSales(const std::vector<Sale*> &sales, const std::vector<Store*> &stores, const std::vector<Client*> &clients);
/**
 * Main Menu
 * @param stores Vector of pointers to all stores.
 * @param clients Vector of pointers to all clients.
 * @param oldClients Vector of pointers to clients removed.
 * @param products Vector of pointers to all products.
 * @param oldProducts Vector of pointers to products removed.
 * @param sales Vector of pointers to all sales.
 * @param employees Vector of pointers to all employees.
 * @param oldEmployees Vector of pointers to employees removed.
 */
void mainMenu(std::vector<Store*> &stores, std::vector<Client*> &clients, std::vector<Client*> &oldClients, std::vector<Product*> &products,
          std::vector<Product*> &oldProducts, std::vector<Sale*> &sales, std::vector<Employee*> &employees, std::vector<Employee*> &oldEmployees);



#endif //MENU_H
