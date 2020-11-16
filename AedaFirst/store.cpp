#include "store.h"
#include <iomanip>
#include <algorithm>
#include <map>
#include "files.h"
using namespace std;
const string Store::FILENAME = "stores.txt";

Store::Store(unsigned id) {
    this->id = id;
}
Store::Store(std::string name, Address address) {
    this->id = store_next_id++;
    this->name = name;
    this->address = address;
}
Store::Store(unsigned int id, std::string name, Address address) {
    this->id = id;
    this->name = name;
    this->address = address;
}

Store::Store(const map<string, string> &mapping, const map<unsigned, Product*> &productsMapping, const map<unsigned, Employee*> &employeesMapping){
    //Create store with basic variables(id, name and Address)
    stringstream sa(mapping.at("id"));
    sa >> this->id;
    this->name = mapping.at("name");
    this->address.street = mapping.at("address_street");
    this->address.locality = mapping.at("address_locality");

    //Read vectors of products and employees
    sa = stringstream(mapping.at("products"));
    while(!sa.eof()){
        unsigned id;
        sa >> id;
        addProduct(productsMapping.at(id));
    }

    sa = stringstream(mapping.at("employees"));
    while(!sa.eof()){
        unsigned nif;
        sa >> nif;
        addEmployee(employeesMapping.at(nif));
    }
}

unsigned Store::getId() const {
    return id;
}

string Store::getName() const {
  return name;
}

Address Store::getAddress() const {
  return address;
}

Product* Store::getProduct(unsigned id) const {
    for (auto product:products) {
        if (product->getId() == id)
            return product;
    }
    return nullptr;
}

vector<Employee*> Store::getEmployees() const {
    return employees;
}

void Store::setName(const string &name) {
  this->name = name;
}

void Store::setAddress(const Address &address) {
  this->address = address;
}

void Store::addProduct(Product* product) {
    if (!findProduct(product->getId()))
        products.push_back(product);
}

void Store::addAllProducts(const vector<Product*> &products) {
    for (auto product:products)
        if (!findProduct(product->getId()))
            this->products.push_back(product);
}

void Store::addEmployee(Employee *employee) {
    employees.push_back(employee);
}

void Store::removeProduct(Product *product) {
    auto it = find(products.begin(), products.end(), product);
    if (it != products.end())
        products.erase(it);
}

void Store::removeEmployee(Employee *employee) {
    auto it = find(employees.begin(), employees.end(), employee);
    if (it != employees.end())
        employees.erase(it);
}

bool Store::findProduct(const unsigned int &id) const {
    for (auto product:products)
        if (product->getId() == id)
            return true;
    return false;
}

Employee* Store::lessOrdered() const {
    Employee* employee = employees.front();
    unsigned min = employees.front()->getNumOrders();
    for (auto e:employees) {
        if (e->getNumOrders() < min) {
            min = e->getNumOrders();
            employee = e;
        }
    }
    return employee;
}

bool Store::operator==(const Store &store) const {
    return id == store.getId();
}

bool Store::operator<(const Store &store) const {
    return id < store.getId();
}

void Store::showProducts() const {
    cout << endl << left << setw(5) << "ID" << setw(10) << "Category" << setw(20)
         << "Name" << setw(17) << "Details" << setw(6) << "Price" << endl;
    for (auto product:products){
        product->showProduct();
    }
}

void Store::showEmployees() const {
    cout << setw(12) << "NIF" << setw(20) << "Name" << setw(10)
            << "Salary" << setw(12) << "N. Orders" << endl;
    for (auto emp:employees) {
        emp->showEmployee(true);
    }
}

void Store::showStore() const {
    cout << "ID: " << getId() << " Store: " << name << endl;
}

/*void Store::statistics(const vector<Sale*> &sales) const {
    unsigned nSales = 0;
    for (auto sale:sales) {
        if (*this == *(sale->getStore())) {
            nSales++;
        }
    }
    cout << "Number of sales: " << nSales << endl;

}*/

ostream& operator<< (std::ostream &os, Store &store){

    files::writeVariable(os, "id", store.id);
    files::writeVariable(os, "name", store.name);
    files::writeVariable(os, "address_locality", store.address.locality);
    files::writeVariable(os, "address_street", store.address.street);

    stringstream productsString("");
    for(Product *product : store.products){
        productsString << " " << product->getId();
    }
    files::writeVariable(os, "products", productsString.str());

    stringstream employeesString("");
    for(Employee *employee : store.employees){
        employeesString << " " << employee->getNif() ;
    }
    files::writeVariable(os, "employees", employeesString.str());

    os << "\n";
    return os;
}




