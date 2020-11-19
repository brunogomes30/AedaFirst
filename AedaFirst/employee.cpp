#include "employee.h"
#include <iomanip>
#include "files.h"

using namespace std;

const string Employee::FILENAME = "employees.txt";

Employee::Employee(const map<string, string> &mapping){
    stringstream(mapping.at("nif")) >> this->nif;
    stringstream(mapping.at("numOrders")) >> this->numOrders;
    stringstream(mapping.at("salary")) >> this->salary;
    stringstream(mapping.at("status")) >> this->status;
    this->name = mapping.at("name");
}

Employee::Employee(string name, unsigned nif, float salary){
    this->name = name;
    this->nif = nif;
    this->salary = salary;
    numOrders = 0;
    this->status = true;
}

string Employee::getName() const {return name;}

unsigned Employee::getNif() const {return nif;}

float Employee::getSalary() const {return salary;}

unsigned Employee::getNumOrders() const {return numOrders;}

void Employee::setName(string name) {this->name = name;}

void Employee::setNif(unsigned nif){this->nif = nif;}

void Employee::setSalary(float salary){this->salary = salary;}

void Employee::addOrders(unsigned numOrders){this->numOrders += numOrders;}

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
    cout << right << setw(9) << setfill('0') << nif << "   " << left << setfill(' ') << setw(20) << name;
    if (details)
        cout << setw(10) << setprecision(2) << fixed << salary << setw(12) << numOrders << endl;
    else
        cout << endl;
}

std::ostream& operator<< (std::ostream &os, Employee &employee){
    files::writeVariable(os, "nif", employee.nif);
    files::writeVariable(os, "name", employee.name);
    files::writeVariable(os, "salary", employee.salary);
    files::writeVariable(os, "numOrders", employee.numOrders);
    files::writeVariable(os, "status", employee.status);
    os << "\n";
    return os;
}

bool Employee::getStatus() const {
    return this->status;
}
void Employee::setStatus(bool status) {
    this->status = status;
}