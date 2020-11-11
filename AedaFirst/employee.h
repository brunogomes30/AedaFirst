//
// Created by pedro on 11/11/2020.
//

#ifndef MAIN_CPP_WORKER_H
#define MAIN_CPP_WORKER_H
#include "store.h"

class Employee {
private:
    std::string name;
    unsigned int nif;
    Store store;
    unsigned int salary;
    unsigned int numOrders
public:
    Employee();
    Employee(std::string name, unsigned int nif, Store store, unsigned int salary, unsigned int numOrders);
    std::string getName() const;
    unsigned getNif() const;
    bool getStore() const;
    unsigned getSalary() const;
    bool getNumOrders() const;
    void setName(std::string name);
    void setNif(unsigned nif);
    void setStore(Store store);
    void setSalary(unsigned int salary);
    void setNumOrders(unsigned int numOrders);
    /**
     * Print employee in format:
     * Name: <EMPLOYEE_NAME> NIF: <EMPLOYEE_NIF>
     * Store ID: <STORE_ID> Store: <STORE_NAME>
     * SALARY: <EMPLOYEE_SALARY> Number of orders: <NUM_ORDERS>
     */
    void showEmployee() const;

#endif //MAIN_CPP_WORKER_H