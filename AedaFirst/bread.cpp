#include "bread.h"
#include <iostream>
#include <iomanip>
#include "files.h"
using namespace std;
const string Bread::FILENAME = "breads.txt";

Bread::Bread(std::string name, float price, Category ctg, SizeType size):Product(name, price, Category::bread) {
    this->size = size;
}

Bread::Bread(unsigned int id, std::string name, float price, Category ctg, SizeType size):Product(id, name, price, Category::bread){
    this->size = size;
}

Bread::Bread(const map<string, string> &mapping) : Product() {
    stringstream(mapping.at("id")) >> this->id;
    stringstream(mapping.at("price")) >> this->price;
    name = mapping.at("name");
    int sizeId;
    stringstream(mapping.at("size")) >> sizeId;
    this->size = (SizeType) sizeId;
    this->category = Category::bread;


}
SizeType Bread::getSize() {
    return size;
}

void Bread::showProduct() const {
    string sizes[2] = {"small", "big"};

    Product::showProduct();
    cout << setw(17) << sizes[size] << setw(6) << setprecision(2) << fixed << price << " euros" << endl;
}

ostream& operator<< (std::ostream &os, Bread &bread){
    files::writeVariable(os, "id", bread.id);
    files::writeVariable(os, "name", bread.name);
    files::writeVariable(os, "price", bread.price);
    files::writeVariable(os, "size", bread.size);
    os << "\n";

    return os;
}