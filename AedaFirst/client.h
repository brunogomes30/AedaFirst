
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "store.h"
#include "product.h"
#include <stack>
#include <vector>

class Client {
private:
    std::string name;
    unsigned nif;
    bool regime; // true if premium regime, false if normal regime
    unsigned points;
    bool discount;
    bool opinion;
    std::stack<int> appraisals;
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
    void useDiscount();
    void addAppraisal(unsigned appraisal);
    void addPoints(const float &bill);
    void showClient() const;


};
#endif //CLIENT_H
