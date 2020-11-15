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
 * 
 * @param stores Vector of pointers to stores.
 * @param store Pointer to the store that the user chose.
 * @param sales
 * @param products
 */
void opsStore(std::vector<Store*> &stores, Store* &store, std::vector<Sale*> &sales, const std::vector<Product*> &products);

void clientHistory(Client* &client, const std::vector<Sale*> &sales);

void opsClient(std::vector<Client*> &clients, std::vector<Client*> &oldClients, Client* &client, const std::vector<Sale*> &sales);

void opsEmployee(std::vector<Store*> &stores, std::vector<Employee*> employees, std::vector<Employee*> oldEmployees, Employee* employee);

void opsProduct(std::vector<Product*> &products, std::vector<Product*> &oldProducts, std::vector<Store*> &stores, Product* &product);

void makeOrder(const std::vector<Store*> &stores, const std::vector<Client*> &clients, Sale &sale);

void salesVolumeByProduct(const std::vector<Sale*> &sales);
void salesVolumeByStore(const std::vector<Sale*> &sales, const std::vector<Store*> &stores);
void opsSalesVolume(const std::vector<Sale*> &sales, const std::vector<Store*> &stores);

void opsSales(const std::vector<Sale*> &sales, const std::vector<Store*> &stores, const std::vector<Client*> &clients);

void mainMenu(std::vector<Store*> &stores, std::vector<Client*> &clients, std::vector<Client*> &oldClients, std::vector<Product*> &products,
          std::vector<Product*> &oldProducts, std::vector<Sale*> &sales, std::vector<Employee*> &employees, std::vector<Employee*> &oldEmployees);



#endif //MENU_H
