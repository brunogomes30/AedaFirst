
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "store.h"
#include "product.h"
#include <stack>
#include <vector>
#include <map>

class Client {
private:
    /**
     * Name of the client.
     */
    std::string name;
    /**
     * NIF of the client.
     */
    unsigned nif;
    /**
     * True to Premium regime, false to Normal regime.
     */
    bool regime; // true if premium regime, false if normal regime
    /**
     * Current points of the client.
     */
    unsigned points;
    /**
     * True if the client has right to a discount in the next order.
     */
    bool discount;
    /**
     * True if average of appraisals is greater than 2.5, false otherwise.
     */
    bool opinion;
    /**
     * Save all the appraisals of client.
     */
    std::stack<int> appraisals;
    /**
     * Keep tracking the sum of appraisals to give the opinion in time O(1).
     */
    int sumOfAppraisals;

    /*
     * Status to see if client is removed active or not
     */
    bool status;
public:

    const static std::string FILENAME;
    Client();
    Client(std::string name, unsigned nif, bool regime);
    Client(const std::map<std::string, std::string> &mapping);
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
     * @param identifier Name or NIF
     * @return True if the client's name or the client's nif is the same of identifier, false otherwise
     */
    bool same(std::string identifier) const;
    /**
     *
     * @param client Pointer to client to be comapared.
     * @return True if both clients has the same name and the same NIF.
     */
    bool operator==(const Client* &client) const;
    /**
     * Print client in format:
     * <NIF>  <NAME>  <REGIME>  <OPINION>
     */
    void showClient(bool details) const;

    friend std::ostream& operator<< (std::ostream &os, const Client &client);

    bool getStatus() const;
    void setStatus(bool status);
};
#endif //CLIENT_H
