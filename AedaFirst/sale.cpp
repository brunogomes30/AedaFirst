#include "sale.h"
#include <algorithm>

using namespace std;

size_t Sale::findProduct(const Product &product) {
    for (size_t i = 0; i < products.size(); i++){
        if ((*products[i]) == product)
            return i;
    }
    return -1;
}

Sale::Sale() {}

void Sale::setClient(Client *client) {this->client = client;}

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
}

Client* Sale::getClient() const {return client;}

vector<Product*> Sale::getProducts() const {return products;}

vector<unsigned> Sale::getQuantities() const {return quantities;}

unsigned Sale::getAppraisal() const {return appraisal;}