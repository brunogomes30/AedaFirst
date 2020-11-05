#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <vector>
#include "store.h"
#include "client.h"
#include "product.h"
#include "sale.h"

void showClients(const std::vector<Client*> &clients);

void showStores(const std::vector<Store*> &stores);

void showMenuOperations();

void showClientOperations();

void showStoreOperations();

Client* searchClient(const std::vector<Client*> &clients, const std::string &identifier);

Store* searchStore(const std::vector<Store*> &stores, const unsigned &id);




#endif //UTILITIES_H
