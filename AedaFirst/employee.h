#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include<map>
class Employee {
private:
    std::string name;
    unsigned nif;
    float salary;
    unsigned numOrders;
public:
	static const std::string FILENAME;
Employee(std::string name = "", unsigned nif = 0, float salary = 0);
    /**
     * The constructor to use when loading from file
     * @param mapping
     */
    Employee(const std::map<std::string, std::string> &mapping);

    std::string getName() const;

    unsigned getNif() const;

    float getSalary() const;

    unsigned getNumOrders() const;

    void setName(std::string name);

    void setNif(unsigned nif);

    void setSalary(float salary);

    void addOrders(unsigned numOrders);

    bool same(std::string identifier) const;

    bool operator==(Employee* employee);

        /**
         * Print employee in format:
         * Name: <EMPLOYEE_NAME> NIF: <EMPLOYEE_NIF>
         * Store ID: <STORE_ID> Store: <STORE_NAME>
         * Salary: <EMPLOYEE_SALARY> Number of orders: <NUM_ORDERS>
         */
    void showEmployee(bool details) const;

    friend std::ostream& operator<< (std::ostream &os, Employee &employee);
};
#endif //EMPLOYEE_H
