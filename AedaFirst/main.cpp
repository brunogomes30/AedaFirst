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

    // Choose client
    showClients(clients);
    cout << "Client's name:" << endl;
    getline(cin, client_name);
    for (auto c:clients){
        if (c->getName() == client_name)
            client = c;
    }
    sale.setClient(client);

    // Choose store
    showStores(stores);
    cout << "Choose a store ID:" << endl;
    cin >> store_id; cin.ignore(100, '\n');
    for (auto s:stores){
        if (store_id == s->getId())
            store = s;
    }
    sale.setStore(store);

    // Choose products
    store->showProducts();
    cout << "ID: 0 -> Stop adding" << endl;
    do {
        cout << "Product you want:" << endl;
        cin >> product_id; cin.ignore(100, '\n');
        if (product_id == 0)
            break;
        cout << "How many:" << endl;
        cin >> qnt; cin.ignore(100, '\n');
        sale.addProduct(store->getProduct(product_id), qnt);
    } while (product_id != 0);

    // Bill
    for (size_t i = 0; i < sale.getQuantities().size(); i++){
        bill += sale.getQuantities()[i]*sale.getProducts()[i]->getPrice();
        cout << sale.getProducts()[i]->getId() << " " << sale.getProducts()[i]->getName() << " "
            << sale.getProducts()[i]->getPrice() << " x " << sale.getQuantities()[i] << endl;
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

    // Appraisal
    cout << "Your appraisal for the service (0-5): " << endl;
    cin >> appraisal; cin.ignore(100, '\n');
    //client->addAppraisal(appraisal);
    sale.setAppraisal(appraisal);
}

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


    showStores(stores);

    for (int i = 0; i < 3; i++){
        sales.push_back(new Sale());
        makeOrder(stores, clients, (*sales[i]));
    }

    for (auto sale:sales) {
        sale->showSale();
    }

}
