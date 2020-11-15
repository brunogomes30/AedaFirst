#include "sale.h"

using namespace std;

Sale::Sale() {
    sale_id = next_sale_id++;
    totalAmount = 0;
}

void Sale::setStore(Store *store) {this->store = store;}

void Sale::setClient(Client *client) {this->client = client;}

void Sale::setEmployee(Employee* employee) {this->employee = employee;}

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

void Sale::setDiscount(float discount) {this->discount = discount;}

Store* Sale::getStore() const {return store;}

Client* Sale::getClient() const {return client;}

Employee* Sale::getEmployee() const {return employee;}

map<Product*,pair<unsigned, float>>& Sale::getProducts() {return products;}

unsigned Sale::getAppraisal() const {return appraisal;}

float Sale::getDiscount() const {return discount;}

float Sale::getTotalAmount() const {return totalAmount;}

bool Sale::sameClient(Client *&client) const {
    return this->client == client;
}

void Sale::showSale(bool showAppraisal) const {
    cout << endl << "---------------------------------------" << endl;
    cout << "SALE " << sale_id << endl;
    store->showStore();
    cout << "Employee: "; employee->showEmployee(0);
    cout << "Client: "; client->showClient(0);
    for (auto it = products.begin(); it != products.end(); it++){
        cout << it->first->getId() << " " << it->first->getName() << " "
             << it->second.first << " x " << it->second.second << endl;
    }
    cout << endl << "Total amount: " << totalAmount << endl;
    if (discount!=1) {
        cout << "Discount: " << (1-discount)*100 << "%   Amount to pay : " << totalAmount*discount << endl;
    }
    if (showAppraisal)
        cout << "Appraisal: " << appraisal << endl;
    cout << "---------------------------------------" << endl;
}