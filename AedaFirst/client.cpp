#include "client.h"
#include <iomanip>
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
    opinion = false;
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

void Client::useDiscount() {discount = false;}

void Client::addAppraisal(unsigned appraisal) {
    appraisals.push(appraisal);
    sumOfAppraisals += appraisal;
    if ((double)sumOfAppraisals/appraisals.size() >= 2.5)
        opinion = true; // positive opinion
    else
        opinion = false; // negative opinion
}

void Client::addPoints(const float &bill) {
    points += (int) bill * 10;

    if (regime) {
        if (points >= 100) {
            points = points % 100;
            discount = true;
        }
    }
    else {
        if (points >= 200) {
            points = points % 200;
            discount = true;
        }
    }
}

bool Client::same(string identifier) const {
    if (isdigit(identifier[0])) {
        unsigned cmpNif = stoul(identifier);
        return nif == cmpNif;
    }
    else
        return name == identifier;
}

bool Client::operator==(const Client* &client) const {
    return (name==client->getName()) && (nif == client->getNif());
}

void Client::showClient(bool details) const {
    cout << right << setw(9) << setfill('0') << nif << left << "   " << setfill(' ') << setw(20) << name;
    if (regime)
        cout << setw(10) << "Premium";
    else
        cout << setw(10) << "Normal";
    if (details) {
        if (opinion)
            cout << setw(12) << "Positive" << endl;
        else
            cout << setw(12) << "Negative" << endl;
    }
    else {
        cout << endl;
    }

}
