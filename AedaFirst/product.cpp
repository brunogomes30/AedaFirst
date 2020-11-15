#include "product.h"
#include <iomanip>

using namespace std;

Product::Product(unsigned id) {
    this->id = id;
}
Product::Product(string name, float price, Category ctg){
    this->id = next_id++;
    this->name = name;
    this->price = price;
    this->category = ctg;
}

unsigned Product::getId() const{return id;}

string Product::getName() const{return name;}

float Product::getPrice() const{return price;}

void Product::setName(std::string &name) {this->name = name;}

void Product::setPrice(float &price) {this->price = price;}

bool Product::operator==(const Product &product) const{
    return id == product.getId();
}

void Product::showProduct() const {
    string categories[2] = {"Bread", "Cake"};

    cout << left << setw(5) << id << setw(10) << categories[category] << setw(20) << name;
}
