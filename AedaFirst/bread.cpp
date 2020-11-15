#include "bread.h"
#include <iostream>
#include <iomanip>

using namespace std;

Bread::Bread(std::string name, float price, Category ctg, sizeType size):Product(name, price, ctg) {
    this->size = size;
}

sizeType Bread::getSize() {
    return size;
}

void Bread::showProduct() const {
    string sizes[2] = {"small", "big"};

    Product::showProduct();
    cout << setw(17) << sizes[size] << setw(6) << price << " euros" << endl;
}