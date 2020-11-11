//
// Created by pedro on 11/11/2020.
//

#ifndef MAIN_CPP_WORKER_H
#define MAIN_CPP_WORKER_H
#include "store.h"
#include <iostream>

class Employee {
private:
    std::string name;
    unsigned int nif;
    Store store;
    float salary;
    unsigned int numOrders
public:
    Employee(std::string name, unsigned int nif, Store store, float salary, unsigned int numOrders);
    std::string getName() const;
    unsigned getNif() const;
    bool getStore() const;
    float getSalary() const;
    unsigned int getNumOrders() const;
    void setName(std::string name);
    void setNif(unsigned nif);
    void setStore(Store store);
    void setSalary(float salary);
    void setNumOrders(unsigned int numOrders);
    /**
     * Print employee in format:
     * Name: <EMPLOYEE_NAME> NIF: <EMPLOYEE_NIF>
     * Store ID: <STORE_ID> Store: <STORE_NAME>
     * Salary: <EMPLOYEE_SALARY> Number of orders: <NUM_ORDERS>
     */
    void showEmployee() const;

#endif //MAIN_CPP_WORKER_H
