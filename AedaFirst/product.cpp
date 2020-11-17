#include "product.h"
#include <iomanip>

using namespace std;
Product::Product(){

}

Product::Product(unsigned id) {
    this->id = id;
}

Product::Product(unsigned int id, std::string name, float price, Category ctg){
    this->id = id;
    this->name = name;
    this->price = price;
    this->category = ctg;
}
Product::Product(string name, float price, Category ctg){
    this->id = next_id++;
    this->name = name;
    this->price = price;
    this->category = ctg;
    this->status = true;
}

unsigned Product::getId() const{return id;}

string Product::getName() const{return name;}

float Product::getPrice() const{return price;}

Category Product::getCategory() const {return category;}

void Product::setName(std::string &name) {this->name = name;}

void Product::setPrice(float &price) {this->price = price;}

bool Product::operator==(const Product &product) const{
    return id == product.getId();
}

void Product::showProduct() const {
    string categories[2] = {"Bread", "Cake"};

    cout << left << setw(5) << id << setw(10) << categories[category] << setw(20) << name;
}

bool Product::getStatus() const{
    return this->status;
}

void Product::setStatus(bool status) {
    this->status = status;
}
