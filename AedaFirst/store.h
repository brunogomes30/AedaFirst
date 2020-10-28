#ifndef STORE_H
#define STORE_H

#include <iostream>

struct Address{
  std::string street;
  std::string locality;
};

class Store {
private:
  std::string name;
  Address address;
public:
  Store(std::string name, Address address);
  std::string getName() const;
  Address getAddress() const;
  void setName(std::string name);
  void setAddress(Address address);
};


#endif //STORE_H
