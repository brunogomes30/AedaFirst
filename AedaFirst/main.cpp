#include <iostream>
#include "store.h"
#include "sale.h"
#include "client.h"
#include "product.h"

using namespace std;

void showClients(const vector<Client*> &clients) {
    for (auto client:clients)
        cout << client->getNif() << " " << client->getName() << endl;
}

void showStores(const vector<Store*> &stores) {
    for (auto store:stores){
        cout << store->getId() << " -> " << store->getName() << endl;
    }
}

Client* searchClient(const vector<Client*> &clients, string &identifier) {
    for (auto client:clients) {
        if (client->same(identifier))
            return client;
    }
    return nullptr;
}

Store* searchStore(const vector<Store*> &stores, unsigned id) {
    for (auto store:stores){
        if (id == store->getId()){
            return store;
        }
    }
    return nullptr;
}

void makeOrder(const vector<Store*> &stores, const vector<Client*> &clients, Sale &sale) {
    Store* store;
    Client* client;
    string client_name;
    unsigned appraisal, store_id, product_id, qnt;
    float bill=0;
    bool error;

    // Choose client
    showClients(clients);
    do {
        error = true;
        cout << "Client's name:" << endl;
        getline(cin, client_name);

        client = searchClient(clients, client_name);
        if (client != nullptr)
            error = false;
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
        if (cin.fail() || cin.peek() != '\n'){
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

        if (!error)
            sale.addProduct(store->getProduct(product_id), qnt);
    } while (product_id != 0);

    // Bill
     for (auto it = sale.getProducts().begin(); it != sale.getProducts().end(); it++){
         bill += it->second * it->first->getPrice();
         cout << it->first->getId() << " " << it->first->getName() << " "
              << it->first->getPrice() << " x " << it->second << endl;
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

void setClientData(string &identifier) {
    bool error;
    do {
        error = false;
        cout << "Client's name or NIF:" << endl;
        getline(cin, identifier);
        if (identifier.length() == 0)
            error = true;
    } while (error);
}

void setClientData(string &name, unsigned &nif, bool &regime) {
    bool error;
    // Set client's name
    do {
        error = false;
        cout << "New client's name:" << endl;
        getline(cin, name);
        if (name.length() == 0)
            error = true;
    } while (error);
    // Set client's NIF
    do {
        error = false;
        cout << "New client's NIF:" << endl;
        cin >> nif;
        if (cin.fail() || cin.peek() != '\n' || nif > 999999999 || nif < 1) {
            cin.clear();
            cout << "That's not a NIF number!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
    // Set client's regime
    cout << "0 -> Normal regime" << endl;
    cout << "1 -> Premium regime" << endl;
    do {
        error = false;
        cout << "New client's regime:" << endl;
        cin >> regime;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cout << "That's not a regime!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
}

void setStoreData(string &name, Address &address) {
    bool error;
    // Set store's name
    do {
        error = false;
        cout << "New store's name:" << endl;
        getline(cin, name);
        if (name.length() == 0)
            error = true;
    } while (error);
    // Set store's street
    do {
        error = false;
        cout << "New store's street:" << endl;
        getline(cin, address.street);
        if (address.street.length() == 0)
            error = true;
    } while (error);
    // Set store's locality
    do {
        error = false;
        cout << "New store's locality:" << endl;
        getline(cin, address.locality);
        if (address.locality.length() == 0)
            error = true;
    } while (error);
}

void searchEmployee() {}

void searchProduct() {}

void opsClient(vector<Client*> &clients, Client* &client) {
    unsigned operation;
    do {
        cout << "[CLIENT] Select operation:" << endl;
        cin >> operation;
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
                break;
            case 3: // Remove client
                //auto it = find(clients.begin(), clients.end(), client);

                break;
        }
    } while (operation != 0);
}

void opsProduct(Product &product) {
    unsigned operation;
    do {
        cout << "[PRODUCT] Select operation:" << endl;
        cin >> operation;
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


int main() {
    vector<Store *> stores;
    vector<Client *> clients;
    vector<Product *> products;
    vector<Sale *> sales;

    string name;
    unsigned nif;
    bool regime;
    float price;
    Address address;
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

    stores.push_back(new Store("Baker Porto", Address({"Rua do douro", "Porto"})));
    stores.push_back(new Store("Baker Lisboa", Address({"Rua do Tejo", "Lisboa"})));

    for (auto store:stores) {
        store->addProduct(&p1);
        store->addProduct(&p2);
    }

    int operation;
    do {
        cout << "[MENU] Select operation:" << endl;
        cin >> operation;
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                cout << "End of program" << endl;
                break;
            case 1: // Make an order
                sales.push_back(new Sale());
                makeOrder(stores, clients, (*sales[sales.size() - 1]));
                break;
            case 2: // Show all sales
                for (auto sale:sales) {
                    sale->showSale();
                }
                break;
            case 3: // Add a client
                setClientData(name, nif, regime);
                clients.push_back(new Client(name, nif, regime));
                break;
            case 4: // Search a client
                setClientData(name);
                client = searchClient(clients, name);
                opsClient(clients, client);
                break;
            case 5: // Add a product
                break;
            case 6: // Add a product to stores
                break;
            case 7: // Search a product
                break;
            case 8: // Add a store
                setStoreData(name, address);
                stores.push_back(new Store(name, address));
                break;

            default:
                cout << "Doesn't exist such operation!" << endl;
                break;
        }
    } while (operation != 0);
}