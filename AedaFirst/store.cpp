#include "store.h"
using namespace std;

Store::Store(std::string name, Address address) {
  this->name = name;
  this->address = address;
}

string Store::getName() const {
  return name;
}

Address Store::getAddress() const {
  return address;
}

void Store::setName(std::string name) {
  this->name = name;
}

void Store::setAddress(Address address) {
  this->address = address;
}

