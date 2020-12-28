#include "product.h"
#include <iomanip>

using namespace std;

unsigned Product::next_id = 1;


Product::Product(){}

Product::Product(string name, float price, Category ctg, unsigned presences){
    this->id = next_id++;
    this->name = name;
    this->price = price;
    this->category = ctg;
    this->status = true;
    this->presences = presences;
}

unsigned Product::getId() const{return id;}

string Product::getName() const{return name;}

float Product::getPrice() const{return price;}

Category Product::getCategory() const {return category;}

bool Product::getStatus() const{
    return this->status;
}

unsigned Product::getPresences() const {return presences;}

void Product::setName(std::string &name) {this->name = name;}

void Product::setPrice(float &price) {this->price = price;}

void Product::setStatus(bool status) {
    this->status = status;
}

void Product::addPresence() {presences++;}

bool Product::operator==(const Product &product) const{
    return id == product.getId();
}

void Product::showProduct() const {
    string categories[2] = {"Bread", "Cake"};

    cout << left << setw(5) << id << setw(10) << categories[category] << setw(20) << name;
}


ProductPtr::ProductPtr(Product * product) {
    this->product = product;
}

Product* ProductPtr::getProduct() const {return product;}

unsigned ProductPtr::getPresences() const {return product->getPresences();}

bool ProductPtr::operator<(const ProductPtr& prd) const{
    if (getPresences() == prd.getPresences()) {
        if (product->getCategory() == prd.getProduct()->getCategory()) {
            return product->getName() < prd.getProduct()->getName();
        }
        else
            return product->getCategory() == bread;
    }
    else
        return getPresences() < prd.getPresences();
}
