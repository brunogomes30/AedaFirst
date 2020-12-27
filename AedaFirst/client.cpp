#include "client.h"
#include <iomanip>
#include "files.h"
#include "utilities.h"
using namespace std;

const string Client::FILENAME = "clients.txt";

Client::Client(const std::map<std::string, std::string> &mapping){
    this->name = mapping.at("name");
    stringstream(mapping.at("nif")) >> this->nif ;
    stringstream(mapping.at("points")) >> this->points;
    stringstream(mapping.at("opinion")) >> this->opinion;
    stringstream(mapping.at("regime")) >> this->regime;
    stringstream(mapping.at("discount")) >> this->discount;
    stringstream (mapping.at("nDiscounts")) >> this->nDiscounts;
    stringstream (mapping.at("nAppraisals")) >> this->nAppraisals;
    stringstream(mapping.at("sumOfAppraisals")) >> this->sumOfAppraisals;
    stringstream(mapping.at("status")) >> this->status;
}

Client::Client(std::string name, unsigned nif, bool regime) {
    this->name = name;
    this->nif = nif;
    this->regime = regime;
    points = 0;
    discount = false;
    nDiscounts = 0;
    sumOfAppraisals = 0;
    opinion = false;
    this->status = true;
}

string Client::getName() const {return name;}

unsigned Client::getNif() const {return nif;}

bool Client::getRegime() const {return regime;}

unsigned Client::getPoints() const {return points;}

bool Client::getDiscount() const {return discount;}

unsigned Client::getNoDiscounts() const {return nDiscounts;}

bool Client::getOpinion() const {return opinion;}

bool Client::getStatus() const {return this->status;}

void Client::setName(string name) {this->name = name;}

void Client::setNif(unsigned nif) {this->nif = nif;}

void Client::setRegime(bool regime) {this->regime = regime;}

void Client::setStatus(bool status) {
    this->status = status;
}

void Client::useDiscount() {
    discount = false;
    nDiscounts++;
}

void Client::addAppraisal(unsigned appraisal) {
    nAppraisals++;
    sumOfAppraisals += appraisal;
    if ((double)sumOfAppraisals/nAppraisals >= 2.5)
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
        return toLower(name) == toLower(identifier);
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

ostream& operator<< (ostream &os, const Client &client){
    files::writeVariable(os, "nif", client.nif);
    files::writeVariable(os, "name", client.name);
    files::writeVariable(os, "opinion", client.opinion);
    files::writeVariable(os, "points", client.points);
    files::writeVariable(os, "regime", client.regime);
    files::writeVariable(os, "discount", client.discount);
    files::writeVariable(os, "nDiscounts", client.nDiscounts);
    files::writeVariable(os, "nAppraisals", client.nAppraisals);
    files::writeVariable(os, "sumOfAppraisals", client.sumOfAppraisals);
    files::writeVariable(os, "status", client.status);
    os << "\n";
    return os;
}


ClientPtr::ClientPtr(Client *clt) {client = clt;}

Client* ClientPtr::getClient() const {return client;}

bool ClientPtr::operator<(const ClientPtr clt) const {
    if ((client->getOpinion() && clt.client->getOpinion()) || (!client->getOpinion() && !clt.client->getOpinion()))
        return client->getNoDiscounts() > clt.client->getNoDiscounts();
    return client->getOpinion() && !clt.client->getOpinion();
}

