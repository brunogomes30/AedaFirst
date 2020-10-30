#include "store.h"
using namespace std;

Store::Store(std::string name, Address address) {
    this->store_id = store_next_id++;
    this->name = name;
    this->address = address;
}

unsigned Store::getId() const {
    return store_id;
}

string Store::getName() const {
  return name;
}

Address Store::getAddress() const {
  return address;
}

Product* Store::getProduct(unsigned id) const {
    for (auto product:products) {
        if (product->getId() == id)
            return product;
    }
}

void Store::setName(std::string name) {
  this->name = name;
}

void Store::setAddress(Address address) {
  this->address = address;
}

void Store::addProduct(Product *product) {
    products.push_back(product);
}

bool Store::operator==(const Store &store) const {
    return store_id == store.getId();
}

void Store::showProducts() const {
    for (auto product:products){
        cout << product->getId() << " -> " << product->getName() << " " << product->getPrice() << " euros" << endl;
    }
}

void Store::showStore() const {
    cout << "ID: " << getId() << " Store: " << name << endl;
}

