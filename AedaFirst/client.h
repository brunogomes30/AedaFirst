
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
    /**
     * Set discount to false.
     */
    void useDiscount();
    /**
     * Change the client's opinion if it is the case.
     * @param appraisal Client appreciation of an order.
     */
    void addAppraisal(unsigned appraisal);
    /**
     * Add 10 points for each unit of bill and set discount on 100 or 200 points according to regime.
     * @param bill Amount payed in last order.
     */
    void addPoints(const float &bill);
    /**
     *
     * @param identifier Can be a name or a nif
     * @return True if the client's name or the client's nif is the same of identifier, false otherwise
     */
    bool same(std::string identifier) const;
    bool operator==(const Client* &client) const;
    /**
     * Print client in format:
     * NIF: <CLIENT_NIF> Name: <CLIENT_NAME> Premium: <REGIME>
     */
    void showClient(bool details) const;
};
#endif //CLIENT_H
