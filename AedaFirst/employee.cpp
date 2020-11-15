#include "employee.h"
#include <iomanip>

using namespace std;


Employee::Employee(string name, unsigned nif, float salary){
    setName(name);
    setNif(nif);
    setSalary(salary);
    numOrders = 0;
}

string Employee::getName() const {return name;}

unsigned int Employee::getNif() const {return nif;}

float Employee::getSalary() const {return salary;}

unsigned int Employee::getNumOrders() const {return numOrders;}

void Employee::setName(string name) {this->name = name;}

void Employee::setNif(unsigned int nif){this->nif = nif;}

void Employee::setSalary(float salary){this->salary = salary;}

void Employee::addOrders(unsigned int numOrders){this->numOrders += numOrders;}

bool Employee::same(string identifier) const {
    if (isdigit(identifier[0])) {
        unsigned cmpNif = stoul(identifier);
        return nif == cmpNif;
    }
    else
        return name == identifier;
}

bool Employee::operator==(Employee* employee) {
    return name == employee->getName() && nif == employee->getNif();
}

void Employee::showEmployee(bool details) const {
    cout << left << setw(12) << nif << setw(20) << name;
    if (details)
        cout << setw(10) << salary << setw(12) << numOrders << endl;
    else
        cout << endl;
}
