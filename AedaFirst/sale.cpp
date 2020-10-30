#include "sale.h"

using namespace std;

size_t Sale::findProduct(const Product &product) {
    for (size_t i = 0; i < products.size(); i++){
        if ((*products[i]) == product)
            return i;
    }
    return -1;
}

Sale::Sale() {
    sale_id = next_sale_id++;
}

void Sale::setClient(Client *client) {this->client = client;}

void Sale::setStore(Store *store) {this->store = store;}

void Sale::setProducts(std::vector<Product *> products, std::vector<unsigned int> quantities) {
    this->products = products;
    this->quantities = quantities;
}

void Sale::addProduct(Product *product, unsigned int qty) {
    size_t n = findProduct((*product));
    if (n == -1) {
        products.push_back(product);
        quantities.push_back(qty);
    }
    else {
        quantities[n] += qty;
    }
}

void Sale::setAppraisal(unsigned int appraisal) {
    this->appraisal = appraisal;
    client->addAppraisal(appraisal);
}

void Sale::setDiscount(bool discount) {this->discount = discount;}

Client* Sale::getClient() const {return client;}

vector<Product*>& Sale::getProducts() {return products;}

vector<unsigned>& Sale::getQuantities() {return quantities;}

unsigned Sale::getAppraisal() const {return appraisal;}

void Sale::showSale() const {
    float bill = 0;
    cout << endl << endl;
    store->showStore();
    client->showClient();
    for (size_t i = 0; i < quantities.size(); i++){
        bill += quantities[i]*products[i]->getPrice();
        cout << products[i]->getId() << " " << products[i]->getName() << " "
             << products[i]->getPrice() << " x " << quantities[i] << endl;
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
}