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
        for (auto c:clients){
            if (c->getName() == client_name) {
                error = false;
                client = c;
            }
        }
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

        for (auto s:stores){
            if (store_id == s->getId()){
                error = false;
                store = s;
            }
        }
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

void addClient() {}

void searchClient() {}

void searchEmployee() {}

void searchProduct() {}


int main() {
    vector<Store*> stores;
    vector<Client*> clients;
    vector<Product*> products;
    vector<Sale*> sales;

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

    for (auto store:stores){
        store->addProduct(&p1);
        store->addProduct(&p2);
    }

    int operation;
    while (operation != 0) {
        cout << "Select operation:" << endl;
        cin >> operation; cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Make an order
                sales.push_back(new Sale());
                makeOrder(stores, clients, (*sales[sales.size()-1]));
                break;
            case 2: // Show all sales
                for (auto sale:sales) {
                    sale->showSale();
                }
                break;

            default:
                break;
        }
    }



}
