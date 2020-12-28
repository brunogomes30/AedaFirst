#include "bread.h"
#include <iostream>
#include <iomanip>
#include "files.h"

using namespace std;

const string Bread::FILENAME = "breads.txt";

Bread::Bread(const map<string, string> &mapping) : Product() {
    stringstream(mapping.at("id")) >> this->id;
    if(next_id <= this->id){
        next_id = this->id + 1;
    }

    stringstream(mapping.at("price")) >> this->price;
    stringstream(mapping.at("status")) >> this->status;
    stringstream (mapping.at("presences")) >> this->presences;
    name = mapping.at("name");
    int sizeId;
    stringstream(mapping.at("size")) >> sizeId;
    this->size = (SizeType) sizeId;
    this->category = Category::bread;


}

Bread::Bread(std::string name, float price, SizeType size, unsigned presences):Product(name, price, Category::bread, presences) {
    this->size = size;
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
    files::writeVariable(os, "status", bread.status);
    files::writeVariable(os, "presences", bread.presences);
    os << "\n";

    return os;
}