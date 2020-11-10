#include "sale.h"

using namespace std;

Sale::Sale() {
    sale_id = next_sale_id++;
    totalAmount = 0;
}

void Sale::setClient(Client *client) {this->client = client;}

void Sale::setStore(Store *store) {this->store = store;}

void Sale::addProduct(Product *product, unsigned int qty) {
    map<Product*, pair<unsigned, float>>::iterator it;
    it = products.find(product);
    if (it == products.end()){
        products.insert(pair<Product*,pair<unsigned, float>>(product, pair<unsigned, float>(qty, product->getPrice())));
    }
    else {
        products[product].first += qty;
    }
    totalAmount += qty*product->getPrice();
}

void Sale::setAppraisal(unsigned int appraisal) {
    this->appraisal = appraisal;
    client->addAppraisal(appraisal);
}

void Sale::setDiscount(bool discount) {this->discount = discount;}

Store* Sale::getStore() const {return store;}

Client* Sale::getClient() const {return client;}

map<Product*,pair<unsigned, float>>& Sale::getProducts() {return products;}

unsigned Sale::getAppraisal() const {return appraisal;}

bool Sale::sameClient(Client *&client) const {
    return this->client == client;
}

void Sale::showSale() const {
    float bill = totalAmount;
    cout << endl << "---------------------------------------" << endl;
    cout << "SALE " << sale_id << endl;
    store->showStore();
    client->showClient();
    for (auto it = products.begin(); it != products.end(); it++){
        cout << it->first->getId() << " " << it->first->getName() << " "
             << it->second.first << " x " << it->second.second << endl;
    }
    cout << endl << "Total amount: " << bill << endl;
    if (discount) {
        if (client->getRegime())
            bill *= 0.95;
        else
            bill *= 0.98;
        cout << "Amount to pay after discount: " << bill << endl;
    }
    cout << "Client's appraisal: " << appraisal << endl;
    cout << "---------------------------------------" << endl;
}