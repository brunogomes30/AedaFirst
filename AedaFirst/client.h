
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <list>

class Client {
private:
    std::string name;
    unsigned nif;
    bool regime; // true if premium regime, false if normal regime
    unsigned points;
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
    bool getOpinion() const;
    void setName(std::string name);
    void setNif(unsigned nif);
    void setRegime(bool regime);
    void addAppraisal(int appraisal);


};
#endif //CLIENT_H
