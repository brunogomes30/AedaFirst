#include "cake.h"
#include "files.h"
#include <iostream>
#include <iomanip>

using namespace std;

const string Cake::FILENAME = "cakes.txt";

Cake::Cake(unsigned id, string name, float price, Layer layer1, Layer layer2) : Product(id, name, price, Category::cake){
    this->layer1 = layer1;
    this->layer2 = layer2;
}

Cake::Cake(string name, float price, Layer layer1, Layer layer2):Product(name, price, Category::cake) {
    this->layer1 = layer1;
    this->layer2 = layer2;
}

Cake::Cake(const map<string, string> &mapping) {
    stringstream(mapping.at("id")) >> this->id;
    if(next_id <= this->id){
        next_id = this->id + 1;
    }
    stringstream(mapping.at("price")) >> this->price;
    stringstream(mapping.at("status")) >> this->status;
    int layerId;
    stringstream(mapping.at("layer1")) >> layerId;
    layer1 = (Layer) layerId;
    stringstream(mapping.at("layer2")) >> layerId;
    layer2 = (Layer) layerId;
    name = mapping.at("name");
    category = Category::cake;

}

Layer Cake::getLayer1() const {
    return layer1;
}

Layer Cake::getLayer2() const {
    return layer1;
}

void Cake::showProduct() const {
    string layers[3] = {"crispy", "puff", "sponge"};

    Product::showProduct();
    cout << setw(17) << layers[layer1] + " / " + layers[layer2]
        << setw(6) << setprecision(2) << fixed << price << " euros" << endl;
}

ostream& operator<< (ostream &os, Cake &cake){
    files::writeVariable(os, "id", cake.id);
    files::writeVariable(os, "name", cake.name);
    files::writeVariable(os, "price", cake.price);
    files::writeVariable(os, "layer1", cake.layer1);
    files::writeVariable(os, "layer2", cake.layer2);
    files::writeVariable(os, "status", cake.status);
    os << "\n";
    return os;
}