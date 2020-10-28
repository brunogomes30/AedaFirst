#include "client.h"
using namespace std;

Client::Client() {
    name ="";
    nif = 0;
    regime = false;
    points = 0;
    sumOfAppraisals = 0;
}

Client::Client(std::string name, unsigned int nif, bool regime) {
    this->name = name;
    this->nif = nif;
    this->regime = regime;
    points = 0;
    sumOfAppraisals = 0;
}

string Client::getName() const {return name;}

unsigned Client::getNif() const {return nif;}

bool Client::getRegime() const {return regime;}

unsigned Client::getPoints() const {return points;}

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