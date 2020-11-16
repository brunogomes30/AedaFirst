#include "menu.h"
#include "utilities.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

Menu::Menu(bool load) {}

Menu::Menu(vector<Store*> s, vector<Client*> c, vector<Client*> co, vector<Employee*> e,
           vector<Employee*> eo, vector<Product*> p, vector<Product*> po, vector<Sale*> sal) {
    stores = s;
    employees = e;
    oldEmployees = eo;
    clients = c;
    oldClients = co;
    products = p;
    oldProducts = po;
    sales = sal;
}
void Menu::chooseClientsSort() {
    int operation;
    do {
        cout << left << endl << setw(5) << "OP" << "Sort by" << endl;
        cout << setw(5) << "1" << "Name" << endl;
        cout << setw(5) << "2" << "NIF" << endl;
        cout << endl << "Choose sort:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 1 && operation != 2)) {
            cin.clear();
            operation = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == -1);
    if (operation == 1)
        sortClientsByName(clients);
    else
        sortClientsByNif(clients);

    if (order())
        reverse(clients.begin(), clients.end());
}

void Menu::chooseSalesVolumeByProductSort(vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    int operation;
    bool descending;
    do {
        cout << endl << setw(5) << "OP" << "Sort by" << endl;
        cout << setw(5) << "1" << "Quantity sold" << endl;
        cout << setw(5) << "2" << "Income" << endl;
        cout << endl << "Choose sort:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 1 && operation != 2)) {
            cin.clear();
            operation = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == -1);
    descending = order();
    if (operation == 0)
        sortByQuantitySold(vProducts);
    else
        sortByIncome(vProducts);

    if (descending)
        reverse(vProducts.begin(), vProducts.end());
}

void Menu::opsStore(Store* &store) {
    int operation, op; string name; Address address;
    vector<Store*>::iterator it;
    do {
        showStoreOperations();
        cout << "\n[STORE] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                break;
            case 1: // Print statistics
                //store->statistics(sales);
                break;
            case 2: // Print all sales
                for (auto sale:sales) {
                    if (sale->getStore() == store)
                        sale->showSale(true);
                }
                break;
            case 3: // Add products
                do {
                    cout << endl << setw(5) << "ID" << setw(20) << "Name" << "Price" << endl;
                    cout << setw(5) << "0" << "All Products" << endl;
                    showProducts(products);
                    cout << endl << "Choose product's ID:" << endl;
                    cin >> op;
                    if (cin.fail() || cin.peek()!='\n') {
                        cin.clear();
                        op = -1;
                        cout << "That product doesn't exist" << endl;
                    }
                    cin.ignore(100, '\n');
                    switch (op) {
                        case -1:
                            break;
                        case 0:
                            store->addAllProducts(products);
                            break;
                        default:
                            store->addProduct(searchProduct(products, op));
                            break;
                    }
                } while (op==-1);
                break;
            case 4: // Change name
                askName(name, "Store");
                store->setName(name);
                break;
            case 5: // Change address
                askAddress(address);
                store->setAddress(address);
                break;
            case 6: // Remove store
                it = find(stores.begin(), stores.end(), store);
                for (auto it2=sales.begin(); it2!=sales.end();it2++) {
                    if ((*it2)->getStore() == (*it)) {
                        delete *it2;
                        *it2 = nullptr;
                    }
                }
                sales.erase(remove(sales.begin(), sales.end(), nullptr), sales.end());
                delete (*it);
                *it = nullptr;
                stores.erase(remove(stores.begin(), stores.end(), nullptr), stores.end());
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Menu::clientHistory(Client* &client) {
    unsigned nSales = 0, nDiscounts = 0;
    float totalSpent = 0, totalDiscount = 0;
    for (auto sale:sales){
        if (sale->sameClient(client)){
            nSales++;
            if (sale->getDiscount() != 1)
                nDiscounts++;
            totalDiscount += (1-sale->getDiscount()) * sale->getTotalAmount();
            totalSpent += sale->getDiscount() * sale->getTotalAmount();
        }
    }
    client->showClient(false);
    if (client->getOpinion())
        cout << "Opinion:\t\t" << "Positive" << endl;
    else
        cout << "Opinion:\t\t" << "Negative" << endl;
    cout << "Number of points:\t" << client->getPoints() << endl;
    cout << "Number of orders:\t" << nSales << endl;
    cout << "Total spent:\t\t" << totalSpent << endl;
    cout << "Discounts used:\t\t" << nDiscounts << endl;
    cout << "Total saved:\t\t" << totalDiscount << endl << endl;

}

void Menu::opsClient(Client* &client) {
    unsigned operation;
    vector<Client*>::iterator it;
    do {
        showClientOperations();
        cout << "\n[CLIENT] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change regime
                client->setRegime(!client->getRegime());
                if (client->getRegime())
                    cout << client->getName() << " is now Premium regime" << endl;
                else
                    cout << client->getName() << " is now Normal regime" << endl;
                break;
            case 2: // View history
                clientHistory(client);
                break;
            case 3: // Remove client
                it = find(clients.begin(), clients.end(), client);
                oldClients.push_back(*it);
                clients.erase(it);
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Menu::opsEmployee(Employee* employee) {
    unsigned operation;
    vector<Employee*>::iterator it;
    do {
        showEmployeeOperations();
        cout << endl << "[EMPLOYEE] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change employee's salary
                bool error;
                float salary;
                askSalaryOrPrice(salary, "Employee's new");
                employee->setSalary(salary);
                break;
            case 2: // Remove employee
                it = find(employees.begin(), employees.end(), employee);
                for (auto store:stores) {
                    store->removeEmployee(*it);
                }
                oldEmployees.push_back(*it);
                employees.erase(it);
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Menu::opsProduct(Product* &product) {
    int operation;
    string name;
    vector<Product*>::iterator it;
    vector<Store*> filterStores;

    do {
        showProductOperations();
        cout << endl << "[PRODUCT] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change name
                askName(name, "Product's new");
                product->setName(name);
                break;
            case 2: // Change price
                float price;
                askSalaryOrPrice(price, "Product's new price");
                product->setPrice(price);
                break;
            case 3: // Add to stores
                filterStores.clear();
                askStores(stores, filterStores);
                for (auto store:filterStores) {
                    if (!store->findProduct(product->getId()))
                        store->addProduct(product);
                }
                break;
            case 4: // Remove product
                it = find(products.begin(), products.end(), product);
                for (auto store:stores) {
                    store->removeProduct(*it);
                }
                oldProducts.push_back(*it);
                products.erase(it);
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Menu::makeOrder(Sale &sale) {
    Store* store;
    Client* client;
    string client_identifier;
    unsigned appraisal, store_id, product_id, qnt;
    float bill=0;
    bool error;

    // Choose client
    showClients(clients);
    do {
        error = true;
        askPersonData(client_identifier, "Client");

        client = searchClient(clients, client_identifier);
        if (client != nullptr)
            error = false;
        else
            cout << "That client doesn't exist." << endl;
    } while (error);
    sale.setClient(client);

    // Choose store
    showStores(stores);
    do {
        error = true;
        askId(store_id, "Store");
        store = searchStore(stores, store_id);
        if (store != nullptr)
            error = false;
        else
            cout << "That store doesn't exist." << endl;
    } while (error);
    sale.setStore(store);

    // Choose products
    cout << endl;
    store->showProducts();
    cout << "Press 0 to stop adding" << endl << endl;
    do {
        cout << "Product you want:" << endl;
        cin >> product_id;
        if (cin.fail() || cin.peek() != '\n' || (!store->findProduct(product_id) && product_id != 0)) {
            product_id = 1;
            cin.clear();
            cin.ignore(100, '\n');
            cout << "That product doesn't exist" << endl;
            continue;
        }
        else
            cin.ignore(100, '\n');
        if (product_id == 0)
            continue;

        error = false;
        cout << "How many:" << endl;
        cin >> qnt;
        if (cin.fail() || cin.peek() != '\n' || qnt == 0){
            error = true;
            cin.clear();
            cout << "That quantity is not possible" << endl;
        }
        cin.ignore(100, '\n');

        if (!error) {
            sale.addProduct(store->getProduct(product_id), qnt);
        }
    } while (product_id != 0);

    // Set employee
    sale.setEmployee(sale.getStore()->lessOrdered());
    sale.getEmployee()->addOrders(1);

    // Bill
    bill = sale.getTotalAmount();

    // Discount
    if (client->getDiscount()) {
        if (client->getRegime())
            sale.setDiscount(0.95);
        else
            sale.setDiscount(0.98);
        client->useDiscount();
    }
    else
        sale.setDiscount(1);

    sale.showSale(false);

    // Manage points
    client->addPoints(bill);
    cout << "You have " << client->getPoints() << " points." << endl;

    if (client->getDiscount())
        if (client->getRegime())
            cout << "Discount of 5% in next order" << endl;
        else
            cout << "Discount of 2% in next order" << endl;

    // Appraisal
    cout << "Your appraisal for the service (0-5): " << endl;
    do {
        cin >> appraisal;
        if (cin.fail() || cin.peek()!= '\n') {
            cin.clear();
            appraisal = -1;
        }
        cin.ignore(100, '\n');
    } while (appraisal < 0 || appraisal > 5);

    sale.setAppraisal(appraisal);
}

void Menu::salesVolumeByProduct() {
    map<Product*, pair<unsigned, float>> auxProducts;
    map<Product*, pair<unsigned, float>> products;
    for (auto sale:sales) {
        auxProducts = sale->getProducts();
        for (auto it=auxProducts.begin(); it != auxProducts.end(); it++) {
            if (products.find(it->first) == products.end())
                products[it->first] = pair<unsigned, float>(it->second.first, it->second.first*it->second.second);
            else {
                products[it->first].first += it->second.first;
                products[it->first].second += it->second.first*it->second.second;
            }
        }
    }
    vector<pair<Product*, pair<unsigned, float>>> vProducts;
    for (auto &it:products)
        vProducts.push_back(it);
    chooseSalesVolumeByProductSort(vProducts);
    cout << endl << setw(5) << "ID" << setw(20) << "Name" << right << setw(14) << "Total sold" << setw(14) << "Total income" << left << endl;
    for (auto p:vProducts) {
        cout << setw(5) << p.first->getId() << setw(20) << p.first->getName() << right << setw(14)
            << p.second.first << setw(14) << p.second.second << left << endl;
    }
}
void Menu::salesVolumeByStore() {
    map<Product*, pair<unsigned, float>> auxProducts;
    map<Store*, float> stores_incomes;
    for (auto store:stores)
        stores_incomes[store] = 0;
    for (auto sale:sales) {
        auxProducts = sale->getProducts();
        for (auto it=auxProducts.begin(); it != auxProducts.end(); it++)
            stores_incomes[sale->getStore()] += it->second.first*it->second.second;
    }
    vector<pair<Store*, float>> vStores_incomes;
    for (auto &it:stores_incomes)
        vStores_incomes.push_back(it);
    sort(vStores_incomes.begin(), vStores_incomes.end(), [](pair<Store*, float> &p1, pair<Store*, float> &p2) {return p1.second > p2.second;});
    cout << endl << setw(5) << "ID" << setw(20) << "Name" << right << setw(14) << "Total income" << left << endl;
    for (auto s:vStores_incomes)
        cout << setw(5) << s.first->getId() << setw(20) << s.first->getName()
            << right << setw(14) << s.second << left << endl;
}
void Menu::opsSalesVolume() {
    int operation;
    do {
        cout << endl << "[SALES VOLUME]" << endl;
        cout << " 0 -> Back" << endl;
        cout << " 1 -> Sales volume by product" << endl;
        cout << " 2 -> Sales volume by store" << endl;
        cout << "\n[SALES VOLUME] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                break;
            case 1:
                salesVolumeByProduct();
                break;
            case 2:
                salesVolumeByStore();
                break;
            default:
                cout << "That operation doesn't exist" << endl;
                break;
        }
    } while (operation != 0);
}

void Menu::opsSales() {
    int operation;
    string name;
    Client* auxC;
    vector<Store*> filterStores = stores;
    vector<Client*> filterClients = clients;
    do {
        cout << endl << "[SALES]" << endl;
        cout << " 0 -> Back" << endl;
        cout << " 1 -> Print all sales" << endl;
        cout << " 2 -> Print filter sales (Use filters first)" << endl;
        cout << " 3 -> Filter stores" << endl;
        cout << " 4 -> Filter clients" << endl;
        cout << "\n[SALES] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                break;
            case 1:
                for (auto sale:sales)
                    sale->showSale(true);
                break;
            case 2:
                for (auto sale:sales)
                    if (searchStore(filterStores, sale->getStore()->getId()) != nullptr &&
                        searchClient(filterClients, sale->getClient()->getName()) != nullptr)
                        sale->showSale(true);
                break;
            case 3:
                filterStores.clear();
                askStores(stores, filterStores);
                break;
            case 4:
                filterClients.clear();
                showClients(clients);
                cout << "Press  0  to finish the filter" << endl;
                do {
                    askPersonData(name, "Client");
                    auxC = searchClient(clients, name);
                    if (auxC != nullptr && searchClient(filterClients, name) == nullptr)
                        filterClients.push_back(auxC);
                } while (name != "0");
                break;
            default:
                cout << "That operation doesn't exist" << endl;
                break;
        }
    } while (operation != 0);
}

void Menu::mainMenu() {
    string name;
    unsigned nif_or_id;
    float price_or_salary;
    Store* store; Address address;
    Product *product; Category ctg; sizeType size; layer ly1;layer ly2;
    Client *client; bool regime;
    Employee *employee;

    int operation;
    do {
        showMenuOperations();
        cout << "\n[MENU] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');

        // MAIN MENU
        switch (operation) {
            case 0: // Exit
                cout << "End of program" << endl;
                break;
            case 1: // Print stores by ID
                showStores(stores);
                cout << endl;
                break;
            case 2: // Add a store
                setStoreData(name, address);
                stores.push_back(new Store(name, address));
                break;
            case 3: // Search a store
                showStores(stores);
                askId(nif_or_id, "Store");
                store = searchStore(stores, nif_or_id);
                if (store != nullptr)
                    opsStore(store);
                else
                    cout << "That store doesn't exist" << endl;
                break;
            case 4: // Print clients
                chooseClientsSort();
                showClients(clients);
                nif_or_id = 0;
                for (auto client:clients) {
                    if (client->getRegime() == true)
                        nif_or_id++;
                }
                cout << "Normal: " << clients.size() - nif_or_id << "     Premium: " << nif_or_id << endl;
                break;
            case 5: // Add a client
                setClientData(name, nif_or_id, regime);
                clients.push_back(new Client(name, nif_or_id, regime));
                break;
            case 6: // Search a client
                showClients(clients);
                askPersonData(name, "Client");
                client = searchClient(clients, name);
                if (client != nullptr)
                    opsClient(client);
                else
                    cout << "That client doesn't exist" << endl;
                break;
            case 7: // Print employees
                showEmployees(stores);
                break;
            case 8: // Add an employee
                setEmployeeData(name, nif_or_id, price_or_salary, stores, store);
                employees.push_back(new Employee(name, nif_or_id, price_or_salary));
                store->addEmployee(employees.back());
                break;
            case 9: // Search an employee
                showEmployees(stores);
                askPersonData(name, "Employee");
                employee = searchEmployee(employees, name);
                if (employee != nullptr)
                    opsEmployee(employee);
                else
                    cout << "That employee doesn't exist" << endl;
                break;
            case 10: // Print products by ID
                showProducts(products);
                break;
            case 11: // Add a product
                setProductData(name, price_or_salary, ctg, size, ly1, ly2);
                if (ctg == bread)
                    products.push_back(new Bread(name, price_or_salary, ctg, size));
                else
                    products.push_back(new Cake(name, price_or_salary, ctg, ly1, ly2));
                break;
            case 12: // Search a product
                showProducts(products);
                askId(nif_or_id, "Product");
                product = searchProduct(products, nif_or_id);
                if (product != nullptr)
                    opsProduct(product);
                else
                    cout << "That product doesn't exist" << endl;
                break;
            case 13: // Make an order
                sales.push_back(new Sale());
                makeOrder((*sales[sales.size() - 1]));
                break;
            case 14: // Print sales volume
                opsSalesVolume();
                break;
            case 15: // Print all sales
                opsSales();
                break;
            default:
                cout << "Doesn't exist such operation!" << endl;
                break;
        }
    } while (operation != 0);
}