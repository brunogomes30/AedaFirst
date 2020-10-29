
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "store.h"
#include "product.h"
#include <list>
#include <vector>

class Client {
private:
    std::string name;
    unsigned nif;
    bool regime; // true if premium regime, false if normal regime
    unsigned points;
    bool discount;
    bool opinion;
    std::list<int> appraisals;
    int sumOfAppraisals;
public:
    Client();
    Client(std::string name, unsigned nif, bool regime);
    std::string getName() const;
    unsigned getNif() const;
    bool getRegime() const;
    unsigned getPoints() const;
    bool getDiscount() const;
    bool getOpinion() const;
    void setName(std::string name);
    void setNif(unsigned nif);
    void setRegime(bool regime);
    void addAppraisal(int appraisal);
    void addPoints(const float &bill);
    void makeOrder(std::vector<Store*> stores);

};
#endif //CLIENT_H
