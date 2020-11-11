//
// Created by pedro on 11/11/2020.
//
#include "employee.h"
#include "store.h"
#include <string>
#include <iostream>
using namespace std;


Employee::Employee(name = "", nif = 0, store, salary = 0, numOrders = 0){
    setName(name);
    setNif(nif);
    setStore(store);
    setSalary(salary);
    setNumOrders(numOrders);
}

string Employee::getName() const {return name;}

unsigned int Employee::getNif() const {return nif;}

store Employee::getStore() const {return store;}

float Employee::getSalary() const {return salary;}

unsigned int Employee::getNumOrders() const {return numOrders;)

void Employee::setName(string name) {this->name = name;}

void Employee::setNif(unsigned int nif){this->nif = nif;}

void Employee::setStore(Store store){this->store = store;}

void Employee::setSalary(float salary){this->salary = salary;}

void Employee::setNumOrders(int numOrders){this->numOrder = numOrder;}

void showEmployee() const{
    cout << "Name: " << name << "NIF:" << nif;
    showStore(store);
    cout << "Salary: " << salary << "Number of orders:" << numOrders;
}
