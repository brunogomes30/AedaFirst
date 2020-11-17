#include "menu.h"
#include "utilities.h"

using namespace std;
static map<int, Product> productsMapping;

int main() {
    /*
    vector<Store *> stores;
    vector<Employee*> employees;
    vector<Employee*> oldEmployees;
    vector<Client *> clients;
    vector<Client *> oldClients;
    vector<Product *> products;
    vector<Product *> oldProducts;
    vector<Sale *> sales;

    Client c1("Joca", 111111, true);
    Client c2("Ambrosio", 222222, false);

    Bread p1("pao de agua", 0.20, bread, small);
    Bread p2("bico de pato", 0.40, bread, big);
    Cake p3("marmore", 0.80, cake, crispy, sponge);
    Employee e1("Joaquim", 123456789, 1000.5);
    Employee e2("Ana", 987654321, 800);
    Employee e3("Mozart", 1, 2000);
    Employee e4("Bethoveen", 232, 1578);
    Employee e5("Bach", 4, 112);
    Employee e6("Schubert", 9, 834);


    products.push_back(&p1);
    products.push_back(&p2);
    products.push_back(&p3);
    employees.push_back(&e1);
    employees.push_back(&e2);
    employees.push_back(&e3);
    employees.push_back(&e4);
    employees.push_back(&e5);
    employees.push_back(&e6);
    clients.push_back(&c1);
    clients.push_back(&c2);

    stores.push_back(new Store("Baker Porto", Address({"Rua do Douro", "Porto"})));
    stores.push_back(new Store("Baker Lisboa", Address({"Rua do Tejo", "Lisboa"})));
    stores.push_back(new Store("Baker Faro", Address({"Rua do Mediterraneo", "Faro"})));
    stores.push_back(new Store("Baker Aveiro", Address({"Rua do Vouga", "Aveiro"})));

    for (auto s:stores) {
        s->addProduct(&p1);
        s->addProduct(&p2);
        s->addProduct(&p3);
    }

    for (int i = 0; i < employees.size(); i++) {
        stores[i%4]->addEmployee(employees[i]);
    }

    */
    Menu menu(true);
    //Menu menu(stores, clients, oldClients, employees, oldEmployees, products, oldProducts, sales);
    menu.mainMenu();

    menu.saveData();


}