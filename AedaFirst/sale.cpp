#include "sale.h"
#include <iomanip>
#include "files.h"
using namespace std;

const string Sale::FILENAME = "sales.txt";

Sale::Sale() {
    id = next_sale_id++;
    totalAmount = 0;
}

Sale::Sale(const map<string, string> &mapping,
           const map<unsigned, Store *>  &storesMapping,
           const map<unsigned, Employee *> &employeesMapping,
           const map<unsigned, Client *> &clientsMapping){
    stringstream(mapping.at("id")) >> this->id;
    unsigned employeeNif, clientNif, storeId;
    stringstream(mapping.at("employeeNif")) >> employeeNif;
    stringstream(mapping.at("clientNif")) >> clientNif;
    stringstream(mapping.at("storeId")) >> storeId;
    this->store = storesMapping.at(storeId);
    this->employee = employeesMapping.at(employeeNif);
    this->client = clientsMapping.at(clientNif);
    stringstream(mapping.at("appraisal")) >> this->appraisal;
    stringstream(mapping.at("totalAmount")) >> this->totalAmount;
    stringstream(mapping.at("discount")) >> this->discount;

}

void Sale::setStore(Store *store) {this->store = store;}

void Sale::setClient(Client *client) {this->client = client;}

void Sale::setEmployee(Employee* employee) {this->employee = employee;}

void Sale::addProduct(Product *product, unsigned int qty) {
    map<Product*, pair<unsigned, float>>::iterator it;
    it = products.find(product);
    if (it == products.end()){
        products.insert(pair<Product*,pair<unsigned, float>>(product, pair<unsigned, float>(qty, product->getPrice())));
    }
    else {
        products[product].first += qty;
    }
    totalAmount += qty*product->getPrice();
}

void Sale::setAppraisal(unsigned int appraisal) {
    this->appraisal = appraisal;
    client->addAppraisal(appraisal);
}

void Sale::setDiscount(float discount) {this->discount = discount;}

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
    files::writeVariable(os, "totalAmount", sale.totalAmount);
    files::writeVariable(os, "discount", sale.discount);
    os << "\n";
    return os;
}