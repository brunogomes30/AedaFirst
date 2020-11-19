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
    std::vector<Client *> clients;
    std::vector<Product *> products;
    std::vector<Sale *> sales;
    // Maps to help saving and loading files
    map<unsigned, Product *> productsMapping;
    map<unsigned, Employee *> employeesMapping;
    map<unsigned, Client *> clientsMapping;
    map<unsigned, Store *> storesMapping;


    /**
    * Manage options available to a store selected.
    * @param store Pointer to the store chose by user.
    */
    void opsStore(Store* &store);
    /**
    * Print client's history (opinion, points, number of orders, total money spent, number of discunts used, total money saved with discounts).
    * @param client  Pointer to the client chose by user.
    */
    void clientHistory(Client* &client);
    /**
    * Manage options available to a client selected.
    * @param client Pointer to the client chose by user.
    */
    void opsClient(Client* &client);
    /**
    * Manage options available to a employee selected.
    * @param employee Pointer to the employee chose by user
    */
    void opsEmployee(Employee* employee);
    /**
    * Manage options available to a product selected.
    * @param product Pointer to the product chose by the user.
    */
    void opsProduct(Product* &product);
    /**
    * Make an order. Asks for a client, a store, products and client appraisal.
    */
    void makeOrder();
    /**
    * Print sales volume by product after ordering.
    */
    void salesVolumeByProduct();
    /**
    * Print sales volume by store.
    */
    void salesVolumeByStore();
    /**
    * Manage options available to print sales volume.
    */
    void opsSalesVolume();
    /**
    * Manage options available to print sales.
    */
    void opsSales();
    /**
     * Read files with path ~/data/{breads, cakes, clients, employees, sales, stores}.txt
     * Initialize attributes of Menu with data loaded from these files.
     */
    void loadData();
public:
    /**
     * Constructor initializing from files data.
     * @param load Decide if the load will be done or not.
     */
    Menu(bool load);
    /**
     * Main Menu. Contains all the flow of program.
     */
    void mainMenu();
    /**
     * Save the current data in files with path ~/data/{breads, cakes, clients, employees, sales, stores}.txt
     */
    void saveData();

};





#endif //MENU_H
