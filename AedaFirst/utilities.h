#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include "store.h"
#include "client.h"
#include "product.h"
#include "sale.h"
#include "algorithm"

void showClients(const std::vector<Client*> &clients);

void showStores(const std::vector<Store*> &stores);

void showProducts(const std::vector<Product*> &products);

void showMenuOperations();

void showClientOperations();

void showStoreOperations();

void setClientData(std::string &identifier);

void setClientData(std::string &name, unsigned &nif, bool &regime);

void setStoreData(unsigned &id);

void setStoreData(std::string &name, Address &address);

Client* searchClient(const std::vector<Client*> &clients, const std::string &identifier);

Store* searchStore(const std::vector<Store*> &stores, unsigned id);

void searchEmployee();

Product* searchProduct(const std::vector<Product*> &products, unsigned id);

bool order();
bool cmpByIncome(const std::pair<Product*, std::pair<unsigned, float>> &p1, const std::pair<Product*, std::pair<unsigned, float>> &p2);
bool cmpByQuantitySold(const std::pair<Product*, std::pair<unsigned, float>> &p1, const std::pair<Product*, std::pair<unsigned, float>> &p2);
void sortByIncome(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);
void sortByQuantitySold(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);

bool cmpClientsByName(Client* &client1, Client* &client2);

bool cmpClientsByNif(Client* &client1, Client* &client2);

void sortClientsByName(std::vector<Client*> &clients);

void sortClientsByNif(std::vector<Client*> &clients);

#endif //UTILITIES_H
