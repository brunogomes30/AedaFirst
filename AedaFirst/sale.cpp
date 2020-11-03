#include "sale.h"

using namespace std;

Sale::Sale() {
    sale_id = next_sale_id++;
}

void Sale::setClient(Client *client) {this->client = client;}

void Sale::setStore(Store *store) {this->store = store;}


void Sale::addProduct(Product *product, unsigned int qty) {
    map<Product*,unsigned>::iterator it;
    it = products.find(product);
    if (it == products.end()){
        products.insert(pair<Product*,unsigned>(product, qty));
    }
    else {
        products[product] += qty;
    }
}

void Sale::setAppraisal(unsigned int appraisal) {
    this->appraisal = appraisal;
    client->addAppraisal(appraisal);
}

void Sale::setDiscount(bool discount) {this->discount = discount;}

Client* Sale::getClient() const {return client;}

map<Product*,unsigned>& Sale::getProducts() {return products;}

unsigned Sale::getAppraisal() const {return appraisal;}

void Sale::showSale() const {
    float bill = 0;
    cout << endl << endl;
    cout << "SALE" << endl;
    store->showStore();
    client->showClient();
    for (auto it = products.begin(); it != products.end(); it++){
        bill += it->second * it->first->getPrice();
        cout << it->first->getId() << " " << it->first->getName() << " "
             << it->first->getPrice() << " x " << it->second << endl;
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
    cout << endl << endl;
}