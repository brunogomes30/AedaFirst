#include "store.h"
#include "utilities.h"
#include <iomanip>
#include <algorithm>
#include <map>
#include "files.h"


using namespace std;

const string Store::FILENAME = "stores.txt";

unsigned Store::store_next_id = 1;

Store::Store(const map<string, string> &mapping,
             const map<unsigned, Product*> &productsMapping,
             const map<unsigned, Employee*> &employeesMapping){
    //Create store with basic variables(id, name and Address)
    stringstream sa(mapping.at("id"));
    if(store_next_id <= this->id) {
        store_next_id = this->id + 1;
    }
    sa >> this->id;
    this->name = mapping.at("name");
    this->address.street = mapping.at("address_street");
    this->address.locality = mapping.at("address_locality");

    //Read vectors of products and employees
    sa = stringstream(mapping.at("products"));
    while(!sa.eof() && !mapping.at("products").empty()){
        unsigned id;
        sa >> id;
        addProduct(productsMapping.at(id));
    }

    sa = stringstream(mapping.at("employees"));
    while(!sa.eof() && !mapping.at("employees").empty()){
        unsigned nif;
        sa >> nif;

        addEmployee(employeesMapping.at(nif));
    }
}

Store::Store(std::string name, Address address) {
    this->id = store_next_id++;
    this->name = name;
    this->address = address;
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
    vector<Employee*> employees;
    for(const auto& ptr: this->employees){
        employees.push_back(ptr.getEmployee());
    }
    return employees;
}

std::vector<Product *> Store::getProducts() const {
    return this->products;
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
    //employees.push_back(employee);
    employees.insert(EmployeePtr(employee));
}

void Store::removeProduct(Product *product) {
    auto it = find(products.begin(), products.end(), product);
    if (it != products.end())
        products.erase(it);
}

bool Store::removeEmployee(Employee *employee) {
    //auto it = find(employees.begin(), employees.end(), employee);
    //if (it != employees.end())
    //    employees.erase(it);
    return employees.erase(EmployeePtr(employee));
}

bool Store::findProduct(const unsigned int &id) const {
    return searchProduct(products, id) != nullptr;

}

Employee* Store::lessOrdered() const {
    Employee* employee = nullptr;
    unsigned min = 999999999;
    for (auto &e:employees) {
        if ((e.getEmployee()->getNumOrders() < min) && (e.getEmployee()->getDeliveries().size() < 5)) {
            min = e.getEmployee()->getNumOrders();
            employee = e.getEmployee();
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

void Store::showEmployees(const unsigned &order) {
    vector<Employee *> employees = getEmployees();
    if (order%3 == 1)
        sortEmployeesByName(employees);
    else if (order%3 == 2)
        sortEmployeesByNif(employees);
    else
        sortEmployeesBySalary(employees);
    if (order > 3)
        reverse(employees.begin(), employees.end());

    cout << setw(12) << "NIF" << setw(20) << "Name" << setw(10)
            << "Salary" << setw(12) << "N. Orders" << setw(12) << "To Delivery" << endl;
    for (auto emp:employees) {
        emp->showEmployee(true);
    }
}

void Store::showStore() const {
    cout << "ID: " << getId() << " Store: " << name << endl;
}

void Store::increaseWages(unsigned minNumber){
    for(const auto& ptr: employees){
        Employee * employee = ptr.getEmployee();
        if(employee->getNumOrders() >= minNumber){
            employee->setSalary(employee->getSalary() * 1.02);
        }
    }
}

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
    for(auto &ptr : store.employees){
        employeesString << " " << ptr.getEmployee()->getNif() ;
    }
    files::writeVariable(os, "employees", employeesString.str());

    os << "\n";
    return os;
}
