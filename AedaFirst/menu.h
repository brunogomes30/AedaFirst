#ifndef MENU_H
#define MENU_H

#include <vector>
#include "store.h"
#include "sale.h"
#include "client.h"
#include "product.h"
#include "bread.h"
#include "cake.h"
#include "employee.h"
using namespace std;
class Menu {
private:
    std::vector<Store *> stores;
    std::vector<Employee*> employees;
    std::vector<Employee*> oldEmployees;
    std::vector<Client *> clients;
    std::vector<Client *> oldClients;
    std::vector<Product *> products;
    std::vector<Product *> oldProducts;
    std::vector<Sale *> sales;

    /**
     * Asks user for the way he wants to sort <clients> and sort it.
     */
    void chooseClientsSort();
    /**
    * Asks user for the way he wants to sort <vProducts> and sort it.
     * @param vProducts Vector of volume sales.
    */
    void chooseSalesVolumeByProductSort(std::vector<std::pair<Product*, std::pair<unsigned, float>>> &vProducts);
    /**
    * Store Menu
    * @param store Pointer to the store chose by user.
    */
    void opsStore(Store* &store);
    /**
    * Print client's history (opinion, points, number of orders, total money spent, number of discunts used, total money saved with discounts).
    * @param client  Pointer to the client chose by user.
    */
    void clientHistory(Client* &client);
    /**
    * Client Menu
    * @param client Pointer to the client chose by user.
    */
    void opsClient(Client* &client);
    /**
    * Employee Menu
    * @param employee Pointer to the employee chose by user
    */
    void opsEmployee(Employee* employee);
    /**
    * Product Menu
    * @param product Pointer to the product chose by the user.
    */
    void opsProduct(Product* &product);
    /**
    * Make an order. Asks for a client, a store, products client appraisal.
    * @param sale Sale to be created;
    */
    void makeOrder(Sale &sale);
    /**
    * Print sales volume by product.
    */
    void salesVolumeByProduct();
    /**
    * Print sales volume by store.
    */
    void salesVolumeByStore();
    /**
    * Sales Volume Menu
    */
    void opsSalesVolume();
    /**
    * Sales Menu
    */
    void opsSales();
public:
    Menu(bool load);
    Menu(vector<Store*> s, vector<Client*> c, vector<Client*> co, vector<Employee*> e,
         vector<Employee*> eo, vector<Product*> p, vector<Product*> po, vector<Sale*> sal);
    /**
    * Main Menu
    */
    void mainMenu();
};





#endif //MENU_H
