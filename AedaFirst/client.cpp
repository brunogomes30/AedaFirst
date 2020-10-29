#include "client.h"
#include <algorithm>
using namespace std;

Client::Client() {
    name ="";
    nif = 0;
    regime = false;
    points = 0;
    discount = false;
    sumOfAppraisals = 0;
}

Client::Client(std::string name, unsigned int nif, bool regime) {
    this->name = name;
    this->nif = nif;
    this->regime = regime;
    points = 0;
    discount = false;
    sumOfAppraisals = 0;
}

string Client::getName() const {return name;}

unsigned Client::getNif() const {return nif;}

bool Client::getRegime() const {return regime;}

unsigned Client::getPoints() const {return points;}

bool Client::getDiscount() const {return discount;}

bool Client::getOpinion() const {return opinion;}

void Client::setName(string name) {this->name = name;}

void Client::setNif(unsigned nif) {this->nif = nif;}

void Client::setRegime(bool regime) {this->regime = regime;}

void Client::addAppraisal(int appraisal) {
    appraisals.push_back(appraisal);
    sumOfAppraisals += appraisal;
    if ((double)sumOfAppraisals/appraisals.size() >= 2.5)
        opinion = true; // positive opinion
    else
        opinion = false; // negative opinion
}

void Client::addPoints(const float &bill) {
    points += (int) bill * 10;

    if (regime)
        if (points >= 100) {
            points = 0;
            discount = true;
        }
    else
        if (points >= 200) {
            points = 0;
            discount = true;
        }

}

void Client::makeOrder(vector<Store*> stores) {
    Store* s;
    vector<Product*> products;
    vector<int> quantities;
    unsigned appraisal, store_id, product_id, qnt;
    float bill=0;

    // Choose store
    for (auto store:stores){
        cout << store->getId() << " -> " << store->getName() << endl;
    }
    cin >> store_id;
    for (auto store:stores){
        if (store_id == store->getId())
            s = store;
    }

    // Choose products
    s->showProducts();
    do {
        cout << "Product you want: ";
        cin >> product_id;
        products.push_back(s->getProduct(product_id));
        cout << "How many: ";
        cin >> qnt;
        quantities.push_back(qnt);
    } while (product_id != 0);

    // Bill
    for (size_t i = 0; i < quantities.size(); i++){
        bill += quantities[i]*products[i]->getPrice();
    }
    if (discount) {
        if (regime)
            bill *= 0.95;
        else
            bill *= 0.98;
        discount = false;
    }
    cout << "Amount to pay: " << bill << endl;

    // Manage points
    addPoints(bill);

    // Appraisal
    cout << "Your appraisal for the service (0-5): ";
    cin >> appraisal;

    addAppraisal(appraisal);
}