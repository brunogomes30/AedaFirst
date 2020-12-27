#include "sale.h"
#include <iomanip>
#include "files.h"
using namespace std;

const string Sale::FILENAME = "sales.txt";

unsigned Sale::next_sale_id = 1;

Sale::Sale(const map<string, string> &mapping,
           const map<unsigned, Store *>  &storesMapping,
           const map<unsigned, Employee *> &employeesMapping,
           const map<unsigned, Client *> &clientsMapping,
           const map<unsigned, Product *> &productsMapping){
    stringstream(mapping.at("id")) >> this->id;
    if(next_sale_id <= this->id){
        next_sale_id = this->id + 1;
    }
    unsigned employeeNif, clientNif, storeId;
    stringstream(mapping.at("employeeNif")) >> employeeNif;
    stringstream(mapping.at("clientNif")) >> clientNif;
    stringstream(mapping.at("storeId")) >> storeId;
    this->store = storesMapping.at(storeId);
    this->employee = employeesMapping.at(employeeNif);
    this->client = clientsMapping.at(clientNif);

    stringstream(mapping.at("appraisal")) >> this->appraisal;
    stringstream(mapping.at("discount")) >> this->discount;
    totalAmount = 0;
    stringstream ss = stringstream(mapping.at("products"));

    while(!ss.eof()) {
        unsigned id, quantity;
        float price;
        ss >> id >> quantity >> price;
        addProduct(productsMapping.at(id), quantity, price);
    }

}

Sale::Sale() {
    totalAmount = 0;
}

Sale::Sale(Client* client, Store* store) {
    id = next_sale_id++;
    this->client = client;
    this->store = store;
    totalAmount = 0;
}

void Sale::setStore(Store *store) {this->store = store;}

void Sale::setClient(Client *client) {this->client = client;}

void Sale::setEmployee(Employee* employee) {this->employee = employee;}

void Sale::addProduct(Product *product, unsigned qty){
    addProduct(product, qty, product->getPrice());
    }

void Sale::addProduct(Product *product, unsigned qty, float price) {
    map<Product*, pair<unsigned, float>>::iterator it;
    it = products.find(product);
    if (it == products.end()){
        products.insert(pair<Product*,pair<unsigned, float>>(product, pair<unsigned, float>(qty, price)));
    }
    else {
        products[product].first += qty;
    }
    totalAmount += qty*price;
}


void Sale::setProducts(std::map<Product*, std::pair<unsigned, float>> &prodsVolume, float totalAmount) {
    products = prodsVolume;
    this->totalAmount = totalAmount;
}

void Sale::setAppraisal(unsigned appraisal) {
    this->appraisal = appraisal;
    client->addAppraisal(appraisal);
}

void Sale::setDiscount(float discount) {this->discount = discount;}

unsigned Sale::getId() const {return id;}

Store* Sale::getStore() const {return store;}

Client* Sale::getClient() const {return client;}

Employee* Sale::getEmployee() const {return employee;}

map<Product*,pair<unsigned, float>>& Sale::getProducts() {return products;}

unsigned Sale::getAppraisal() const {return appraisal;}

float Sale::getDiscount() const {return discount;}

float Sale::getTotalAmount() const {return totalAmount;}

bool Sale::sameClient(Client *&client) const {
    return this->client == client;
}

void Sale::showSale(bool showAppraisal) const {
    string ctg[2] = {"Bread", "Cake"};
    cout << endl << "-----------------------------------------------" << endl;
    cout << "SALE " << id << endl;
    store->showStore();
    cout << "Employee: "; employee->showEmployee(false);
    cout << "Client: "; client->showClient(false);
    cout << endl << setw(5) << "ID" << setw(10) << "Category" << setw(20) << "Name" << setw(6)
            << "Qty" << "   " << setw(6) << "Price" << endl;
    for (auto it = products.begin(); it != products.end(); it++){
        cout << setw(5) << it->first->getId() << setw(10) << ctg[it->first->getCategory()] << setw(20) << it->first->getName()
            << setw(6) << it->second.first << " x " << setw(6) << setprecision(2) << fixed << it->second.second << endl;
    }
    cout << endl << "Total amount: " << setprecision(2) << fixed << totalAmount << endl;
    if (discount!=1) {
        cout << "Discount: " << (1-discount)*100 << "%   Amount to pay : "
            << setprecision(2) << fixed << totalAmount*discount << endl;
    }
    if (showAppraisal)
        cout << "Appraisal: " << appraisal << endl;
    cout << "-----------------------------------------------" << endl;
}

ostream& operator<< (ostream &os, const Sale &sale){
    files::writeVariable(os, "id", sale.id);
    files::writeVariable(os, "employeeNif", sale.employee->getNif());
    files::writeVariable(os, "clientNif", sale.client->getNif());
    files::writeVariable(os, "storeId", sale.store->getId());
    files::writeVariable(os, "appraisal", sale.appraisal);
    files::writeVariable(os, "discount", sale.discount);

    stringstream productsStream (" ");
    for(auto it = sale.products.begin(); it!= sale.products.end(); it++){
        productsStream << it->first->getId() << " " << it->second.first << " " << it->second.second << " ";
    }
    files::writeVariable(os, "products", productsStream.str());
    os << "\n";
    return os;
}