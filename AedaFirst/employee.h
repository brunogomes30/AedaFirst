#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>

class Employee {
private:
    std::string name;
    unsigned int nif;
    float salary;
    unsigned int numOrders;
public:
    Employee(std::string name = "", unsigned int nif = 0, float salary = 0);

    std::string getName() const;

    unsigned getNif() const;

    float getSalary() const;

    unsigned int getNumOrders() const;

    void setName(std::string name);

    void setNif(unsigned nif);

    void setSalary(float salary);

    void addOrders(unsigned int numOrders);

    bool same(std::string identifier) const;

    bool operator==(Employee* employee);

        /**
         * Print employee in format:
         * Name: <EMPLOYEE_NAME> NIF: <EMPLOYEE_NIF>
         * Store ID: <STORE_ID> Store: <STORE_NAME>
         * Salary: <EMPLOYEE_SALARY> Number of orders: <NUM_ORDERS>
         */
    void showEmployee(bool details) const;
};
#endif //EMPLOYEE_H
