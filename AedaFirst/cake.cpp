#include "cake.h"
#include <iostream>
#include <iomanip>

using namespace std;

Cake::Cake(std::string name, float price, Category ctg, layer ly1, layer ly2):Product(name, price, ctg) {
    layer1 = ly1;
    layer2 = ly2;
}

layer Cake::getLayer1() const {
    return layer1;
}

layer Cake::getLayer2() const {
    return layer1;
}

void Cake::showProduct() const {
    string layers[3] = {"crispy", "puff", "sponge"};

    Product::showProduct();
    cout << setw(17) << layers[layer1] + " / " + layers[layer2]
        << setw(6) << price << " euros" << endl;
}