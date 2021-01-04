
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
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
    bool regime;
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
     * Number of discounts used.
     */
    unsigned nDiscounts;
    /**
     * Keep tracking the number of appraisals to give the opinion in time O(1).
     */
    unsigned nAppraisals;
    /**
     * Keep tracking the sum of appraisals to give the opinion in time O(1).
     */
    int sumOfAppraisals;
    /**
     * Status to see if client is removed active or not.
     */
    bool status;
public:
    /**
     * Name of the file in data directory (clients.txt).
     */
    const static std::string FILENAME;
    /**
     * The constructor to use when loading from file.
     * @param mapping Pairs whose first element identifies the attribute and second has its data.
     */
    Client(const std::map<std::string, std::string> &mapping);
    /**
     * Initialize a client setting his name, NIF and regime.
     * @param name Name of the client.
     * @param nif NIF of the client.
     * @param regime Regime of the client.
     */
    Client(std::string name, unsigned nif, bool regime);
    /**
     *
     * @return Name of the client
     */
    std::string getName() const;
    /**
     *
     * @return NIF of the client.
     */
    unsigned getNif() const;
    /**
     *
     * @return Regime of the client.
     */
    bool getRegime() const;
    /**
     *
     * @return Current points of the client.
     */
    unsigned getPoints() const;
    /**
     *
     * @return True if discount in next order.
     */
    bool getDiscount() const;
    /**
     * @return Numbers of discounts used.
     */
     unsigned getNoDiscounts() const;
    /**
     *
     * @return Opinion of the client.
     */
    bool getOpinion() const;
    /**
     *
     * @return Activation status of the client (true if he was not removed)
     */
    bool getStatus() const;

    void setName(std::string name);
    void setNif(unsigned nif);
    /**
     *
     * @param regime New regime of the client.
     */
    void setRegime(bool regime);
    /**
     *
     * @param status New activation status of the client.
     */
    void setStatus(bool status);

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
     * Compare a client with either a name or a NIF.
     * @param identifier Name or NIF
     * @return True if the client's name or the client's nif is the same of identifier, false otherwise
     */
    bool same(std::string identifier) const;
    /**
     * Compare two clients.
     * @param client Pointer to client to be compared.
     * @return True if both clients has the same name and the same NIF.
     */
    bool operator==(const Client* &client) const;
    /**
     * Print client in format:\n
     * <NIF>  <NAME>  <REGIME>  <OPINION>\n
     * @param details If false does not print client´s opinion.
     */
    void showClient(bool details) const;
    /**
     * Write client in the file.
     * @param os Stream where to save.
     * @param client Client to be saved.
     * @return Stream where was saved.
     */
    friend std::ostream& operator<< (std::ostream &os, const Client &client);

};

/**
 * Class that represents a client
 */class ClientPtr{
private:
    /**
     * Pointer to client.
     */
    Client* client;
public:
    /**
     * Constructor of ClientPtr.
     * @param clt Pointer to client.
     */
    ClientPtr(Client* clt);
    /**
     *
     * @return Pointer to client.
     */
    Client* getClient() const;
    /**
     * Compare clients by their opinion and in equality case by discounts taken.
     * @param clt Client to compare with.
     * @return True if clt has a better opinion of the bakery, false otherwise.
     */
    bool operator<(const ClientPtr clt) const;
};
#endif //CLIENT_H
