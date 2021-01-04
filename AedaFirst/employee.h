#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <map>
#include <queue>
#include "client.h"


class Employee {
private:
    /**
     * Name of the employee.
     */
    std::string name;
    /**
     * NIF of the employee.
     */
    unsigned nif;
    /**
     * Salary of the employee.
     */
    float salary;
    /**
     * Number of orders cared by the employee.
     */
    unsigned numOrders;
    /**
     * Activation status of the employee. True if he was not removed.
     */
    bool status;
    /**
     * Keep a maximum of 5 clients to delivery the order in right order.
     */
    std::priority_queue<ClientPtr> deliveries;
public:
    /**
     * Name of the file in data directory (employees.txt).
     */
	static const std::string FILENAME;
    /**
     * The constructor to use when loading from file.
     * @param mapping Pairs whose first element identifies the attribute and second has its data.
     */
    Employee(const std::map<std::string, std::string> &mapping,
             const std::map<unsigned, Client*> &clientsMapping);
    /**
     * Initialize a employee setting his name, NIF and salary.
     * @param name Name of the employee.
     * @param nif NIF of the employee.
     * @param salary Salary of the employee.
     */
    Employee(std::string name = "", unsigned nif = 0, float salary = 0);
    /**
     *
     * @return Name of the employee.
     */
    std::string getName() const;
    /**
     *
     * @return NIF of the employee.
     */
    unsigned getNif() const;
    /**
     *
     * @return Salary of the employee.
     */
    float getSalary() const;
    /**
     *
     * @return Current number of orders cared by the employee.
     */
    unsigned getNumOrders() const;
    /**
     *
     * @return Activation status of the employee (true if he was not removed)
     */
    bool getStatus() const;
    /**
     *
     * @return Deliveries.
     */
    std::priority_queue<ClientPtr>& getDeliveries();

    void setName(std::string name);

    void setNif(unsigned nif);
    /**
     *
     * @param salary New salary of the employee.
     */
    void setSalary(float salary);
    /**
     *
     * @param status New activation status of the client.
     */
    void setStatus(bool status);
    /**
     *
     * @param numOrders Number of orders to add to orders already done.
     */
    void addOrders(unsigned numOrders);
    /**
     * Compare a employee with either a name or a NIF.
     * @param identifier Name or NIF.
     * @return True if the employee's name or the employee's nif is the same of identifier, false otherwise.
     */
    bool same(std::string identifier) const;
    /**
     * Compare two employees.
     * @param employee Pointer to employee to be compared.
     * @return True if both employees have the same name and the same NIF.
     */
    bool operator==(Employee* employee);
    /**
     * Print employee in format:\n
     * <NIF>  <NAME>  <SALARY>  <NUM_ORDERS>\n
     * @param details If false does not print neither salary nor number of orders of the employee.
     */
    void showEmployee(bool details) const;
    /**
     * Write employee in the file.
     * @param os Stream where to save.
     * @param employee Employee to be saved.
     * @return Stream where was saved.
     */
    friend std::ostream& operator<< (std::ostream &os, Employee &employee);

};

/*
* Class that represents an employee
*/
class EmployeePtr {
private:
    /*
     * Pointer to employee
     */
    Employee* emp;
public:
    /*
     * Constructor of ClientPtr
     * @param e - Pointer to client
     */
    EmployeePtr(Employee* e):emp(e) {}

    /*
     *
     * @return Pointer to employee
     */
    Employee* getEmployee() const{return emp;}
};

/**
 * Return hash based on the nif of employee
 */
struct hashEmployee {
    int operator() (const EmployeePtr &employee) const{
        return std::hash<unsigned>()(employee.getEmployee()->getNif());
    }
};

/**
 * Returns true if the 2 employees have the same name and nif
 */
struct equalityEmployee{
    bool operator() (const EmployeePtr &employee1, const EmployeePtr &employee2) const {
        return employee1.getEmployee()->getNif() == employee2.getEmployee()->getNif();
    }
};
#endif //EMPLOYEE_H
