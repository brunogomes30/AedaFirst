#include <iostream>
#include "store.h"
#include "sale.h"
#include "client.h"
#include "product.h"
#include "utilities.h"
#include <algorithm>


using namespace std;

void chooseClientsSort(vector<Client*> &clients) {
    int operation;
    bool descending;
    do {
        cout << "0 -> Sort by name" << endl;
        cout << "1 -> Sort by nif" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 0 && operation != 1)) {
            cin.clear();
            operation = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == -1);
    descending = order();
    if (operation == 0)
        sortClientsByName(clients);
    else
        sortClientsByNif(clients);

    if (descending)
        reverse(clients.begin(), clients.end());

}

void chooseSalesVolumeByProductSort(vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    int operation;
    bool descending;
    do {
        cout << "0 -> Sort by quantity sold" << endl;
        cout << "1 -> Sort by income" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 0 && operation != 1)) {
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

/*void clientHistory(Client* &client, const vector<Sale*> &sales) {
    float totalSpent = 0;
    //map<Store*, map<Product*, unsigned>> allSales;
    map<Product*, pair<unsigned, float>> auxProducts;
    map<Product*, pair<unsigned, float>> products;
    for (auto sale:sales){
        if (sale->sameClient(client)){
            auxProducts = sale->getProducts();
            for (auto it = auxProducts.begin(); it != auxProducts.end(); it++){
                products[it->first] += it->second.first;
            }
        }
    }
    for (auto it=products.begin(); it != products.end();it++) {
        cout << it->first->getName() << "  " << it->second << " x " << it->first->getPrice()
                << " = " << it->second*it->first->getPrice() << endl;
        totalSpent += it->first->getPrice() * it->second;
    }
    cout << "Total spend: " << totalSpent << endl;
}*/

void opsClient(vector<Client*> &clients, Client* &client, const vector<Sale*> &sales) {
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
                //clientHistory(client, sales);
                break;
            case 3: // Remove client
                it = find(clients.begin(), clients.end(), client);
                delete *it;
                *it = nullptr;
                clients.erase(remove(clients.begin(), clients.end(), nullptr));
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void opsStores(vector<Store*> &stores, Store* &store, vector<Sale*> sales, const vector<Product*> &products) {
    int operation, op;
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
            case 1: // Print statistics
                break;
            case 2: // Print all sales
                for (auto sale:sales) {
                    if (sale->getStore() == store)
                        sale->showSale();
                }
                break;
            case 3: // Add a product
                do {
                    cout << "0 All Products" << endl;
                    showProducts(products);
                    cout << " Choose product to add:" << endl;
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
            case 4: // Remove store
                it = find(stores.begin(), stores.end(), store);
                delete *it;
                *it = nullptr;
                stores.erase(remove(stores.begin(), stores.end(), nullptr));
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void opsProduct(Product &product) {
    unsigned operation;
    do {
        cout << "[PRODUCT] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change name
                break;
            case 2: // Change price
                break;
            case 3: // Remove product
                break;
            case 4: // Number of products sold
                break;
            case 5: // Income
                break;
        }
    } while (operation != 0);
}

void makeOrder(const vector<Store*> &stores, const vector<Client*> &clients, Sale &sale) {
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
        setClientData(client_identifier);

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
        cout << "Choose a store ID:" << endl;
        cin >> store_id;

        if (cin.fail() || cin.peek() != '\n'){
            cin.clear();
            cin.ignore(100, '\n');
            cout << "That store doesn't exist." << endl;
            continue;
        }
        else
            cin.ignore(100, '\n');

        store = searchStore(stores, store_id);
        if (store != nullptr)
            error = false;
    } while (error);
    sale.setStore(store);

    // Choose products
    cout << "ID: 0 -> Stop adding" << endl;
    store->showProducts();
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
        if (cin.fail() || cin.peek() != '\n'){
            error = true;
            cin.clear();
            cout << "That quantity doesn't exist" << endl;
        }
        cin.ignore(100, '\n');

        if (!error) {
            sale.addProduct(store->getProduct(product_id), qnt);
        }
    } while (product_id != 0);

    // Bill
    bill = sale.getTotalAmount();
    for (auto it = sale.getProducts().begin(); it != sale.getProducts().end(); it++){
        cout << it->first->getId() << " " << it->first->getName() << " "
             << it->second.first << " x " << it->second.second << endl;
    }
    cout << endl << "Total amount: " << bill << endl;

    if (client->getDiscount()) {
        if (client->getRegime())
            bill *= 0.95;
        else
            bill *= 0.98;
        client->useDiscount();
        sale.setDiscount(true);
        cout << "Amount to pay after discount: " << bill << endl;
    }
    else
        sale.setDiscount(false);

    // Manage points
    client->addPoints(bill);
    cout << "You have " << client->getPoints() << " points." << endl;

    // Appraisal
    cout << "Your appraisal for the service (0-5): " << endl;
    cin >> appraisal; cin.ignore(100, '\n');
    sale.setAppraisal(appraisal);
}

void salesVolumeByProduct(const vector<Sale*> &sales) {
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
    for (auto p:vProducts) {
        cout << p.first->getId() << " " << p.first->getName() << " Total sold: " << p.second.first << " Total Income: " << p.second.second << endl;
    }
}
void salesVolumeByStore(const vector<Sale*> &sales, const vector<Store*> &stores) {
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
    for (auto s:vStores_incomes)
        cout << s.first->getId() << " " << s.first->getName() << " Total income: " << s.second << endl;
}
void opsSalesVolume(const vector<Sale*> &sales, const vector<Store*> &stores) {
    int operation;
    do {
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
                salesVolumeByProduct(sales);
                break;
            case 2:
                salesVolumeByStore(sales, stores);
                break;
            default:
                cout << "That operation doesn't exist" << endl;
                break;
        }
    } while (operation<0 || operation>2);
}

int main() {
    vector<Store *> stores;
    vector<Client *> clients;
    vector<Product *> products;
    vector<Product *> oldProducts;
    vector<Sale *> sales;

    string name;
    unsigned nif_or_id;
    bool regime;
    float price;
    Address address;
    Store* store;
    Product *product;
    Client *client;

    Client c1("Joca", 111111, true);
    Client c2("Ambrosio", 222222, false);

    Product p1("pao de agua", 0.20);
    Product p2("bico de pato", 0.40);

    products.push_back(&p1);
    products.push_back(&p2);
    clients.push_back(&c1);
    clients.push_back(&c2);

    stores.push_back(new Store("Baker Porto", Address({"Rua do Douro", "Porto"})));
    stores.push_back(new Store("Baker Lisboa", Address({"Rua do Tejo", "Lisboa"})));
    stores.push_back(new Store("Baker Faro", Address({"Rua do Mediterraneo", "Faro"})));
    stores.push_back(new Store("Baker Aveiro", Address({"Rua do Vouga", "Aveiro"})));


    for (auto s:stores) {
        s->addProduct(&p1);
        s->addProduct(&p2);
    }

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
                setStoreData(nif_or_id);
                store = searchStore(stores, nif_or_id);
                if (store != nullptr)
                    opsStores(stores, store, sales, products);
                else
                    cout << "That store doesn't exist" << endl;
                break;
            case 4: // Print clients
                chooseClientsSort(clients);
                showClients(clients);
                break;
            case 5: // Add a client
                setClientData(name, nif_or_id, regime);
                clients.push_back(new Client(name, nif_or_id, regime));
                break;
            case 6: // Search a client
                showClients(clients);
                setClientData(name);
                client = searchClient(clients, name);
                if (client != nullptr)
                    opsClient(clients, client, sales);
                else
                    cout << "That client doesn't exist" << endl;
                break;
            case 7: // Print employees
                break;
            case 8: // Add an employee
                break;
            case 9: // Search an employee
                break;
            case 10: // Print products by ID
                break;
            case 11: // Add a product
                break;
            case 12: // Search a product
                break;
            case 13: // Make an order
                sales.push_back(new Sale());
                makeOrder(stores, clients, (*sales[sales.size() - 1]));
                break;
            case 14: // Print sales volume
                opsSalesVolume(sales, stores);
                break;
            case 15: // Show all sales
                for (auto sale:sales)
                    sale->showSale();
                break;
            default:
                cout << "Doesn't exist such operation!" << endl;
                break;
        }
    } while (operation != 0);
}