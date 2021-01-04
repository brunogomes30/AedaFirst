#include "bakery.h"
#include "utilities.h"
#include "files.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "exceptions.h"
#include <fstream>
#include <map>

using namespace std;

Bakery::Bakery(bool load):productsPresences(ProductPtr(nullptr)) {
    if (load)
        loadData();
}

void Bakery::opsStore(Store* &store) {
    int operation; unsigned id, minNumber; string name; Address address;
    vector<Store*>::iterator it;
    do {
        showStoreOperations();
        cout << "\n[STORE] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                break;
            case 1: // Print statistics
                showStoreStatistics(sales, store);
                break;
            case 2: // Print all sales
                for (auto sale:sales) {
                    if (sale->getStore() == store)
                        sale->showSale(true);
                }
                break;
            case 3: // Add products
                showProducts(products);
                cout << setw(5) << "0" << "All Products" << endl;
                askId(id, "Product");
                if (id == 0)
                    store->addAllProducts(products);
                else {
                    Product *p = searchProduct(products, id);
                    if (p != nullptr)
                        store->addProduct(p);
                    else
                        cout << "That product does not exist." << endl;
                }
                break;
            case 4: // Remove product
                store->showProducts();
                askId(id, "Product");
                store->removeProduct(searchProduct(products, id));
                break;
            case 5: // Change name
                askName(name, "Store");
                store->setName(name);
                break;
            case 6: // Change address
                askAddress(address);
                store->setAddress(address);
                break;
            case 7: // Increase wages of employees by 2%
                askMinNumber(minNumber);
                store->increaseWages(minNumber);
                break;
            case 8: // Remove store
                it = find(stores.begin(), stores.end(), store);
                for (auto it2=sales.begin(); it2!=sales.end();it2++) {
                    if ((*it2)->getStore() == (*it)) {
                        delete *it2;
                        *it2 = nullptr;
                    }
                }
                sales.erase(remove(sales.begin(), sales.end(), nullptr), sales.end());
                storesMapping.erase((*it)->getId());
                delete (*it);
                *it = nullptr;
                stores.erase(remove(stores.begin(), stores.end(), nullptr), stores.end());
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Bakery::clientHistory(Client* &client) {
    unsigned nSales = 0, nDiscounts = 0;
    float totalSpent = 0, totalDiscount = 0;
    for (auto sale:sales){
        if (sale->sameClient(client)){
            nSales++;
            if (sale->getDiscount() != 1)
                nDiscounts++;
            totalDiscount += (1-sale->getDiscount()) * sale->getTotalAmount();
            totalSpent += sale->getDiscount() * sale->getTotalAmount();
        }
    }
    client->showClient(false);
    if (client->getOpinion())
        cout << "Opinion:\t\t" << "Positive" << endl;
    else
        cout << "Opinion:\t\t" << "Negative" << endl;
    cout << "Number of points:\t" << client->getPoints() << endl;
    cout << "Number of orders:\t" << nSales << endl;
    cout << "Total spent:\t\t" << setprecision(2) << fixed << totalSpent << endl;
    cout << "Discounts used:\t\t" << nDiscounts << endl;
    cout << "Total saved:\t\t" << setprecision(2) << fixed << totalDiscount << endl << endl;

}

void Bakery::opsClient(Client* &client) {
    unsigned operation;
    vector<Client*>::iterator it;
    do {
        showClientOperations();
        cout << "\n[CLIENT] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change regime
                client->setRegime(!client->getRegime());
                if (client->getRegime())
                    cout << client->getName() << " is now Premium regime" << endl;
                else
                    cout << client->getName() << " is now Normal regime" << endl;
                break;
            case 2: // View history
                clientHistory(client);
                break;
            case 3: // Remove client
                it = find(clients.begin(), clients.end(), client);
                (*it)->setStatus(false);
                clients.erase(it);
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Bakery::opsEmployee(Employee* employee) {
    unsigned operation;
    vector<Employee*>::iterator it;
    do {
        showEmployeeOperations();
        cout << endl << "[EMPLOYEE] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change employee's salary
                Store* s;
                bool error;
                float salary;
                askSalaryOrPrice(salary, "Employee's new salary");
                it = find(employees.begin(), employees.end(), employee);
                for (auto store:stores) {
                    if (store->removeEmployee(*it))
                        s = store;
                }
                employee->setSalary(salary);
                s->addEmployee(*it);
                break;
            case 2: // Remove employee
                it = find(employees.begin(), employees.end(), employee);
                for (auto store:stores) {
                    store->removeEmployee(*it);
                }
                (*it)->setStatus(false);
                employees.erase(it);
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Bakery::opsProduct(Product* &product) {
    int operation;
    string name;
    vector<Product*>::iterator it;
    vector<Store*> filterStores;

    do {
        showProductOperations();
        cout << endl << "[PRODUCT] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 1: // Change name
                askName(name, "Product's new");
                productsPresences.remove(ProductPtr(product));
                product->setName(name);
                productsPresences.insert(ProductPtr(product));
                break;
            case 2: // Change price
                float price;
                askSalaryOrPrice(price, "Product's new price");
                productsPresences.remove(ProductPtr(product));
                product->setPrice(price);
                productsPresences.insert(ProductPtr(product));
                break;
            case 3: // Add to stores
                filterStores.clear();
                askStores(stores, filterStores);
                for (auto store:filterStores) {
                    if (!store->findProduct(product->getId()))
                        store->addProduct(product);
                }
                break;
            case 4: // Remove product
                it = find(products.begin(), products.end(), product);
                for (auto store:stores) {
                    store->removeProduct(*it);
                }
                (*it)->setStatus(false);
                products.erase(it);
                operation = 0;
                break;
            default:
                break;
        }
    } while (operation != 0);
}

void Bakery::makeOrder() {
    Store* store;
    Client* client;
    string client_identifier;
    unsigned appraisal, store_id, product_id, qnt;
    float bill=0;
    bool error;

    if (clients.empty())
        throw NoClientInClientsException("No registered clients.");

    // Choose client
    showClients(clients);
    do {
        error = true;
        askPersonData(client_identifier, "Client");

        client = searchClient(clients, client_identifier);
        if (client != nullptr)
            error = false;
        else
            cout << "That client doesn't exist." << endl;
    } while (error);

    // Choose store
    showStores(stores);
    do {
        error = true;
        askId(store_id, "Store");
        store = searchStore(stores, store_id);
        if (store != nullptr)
            error = false;
        else
            cout << "That store doesn't exist." << endl;
    } while (error);

    if (store->getEmployees().empty())
        throw NoEmployeeInStoreException("No employees in that store to deal with the order.");
    if (store->lessOrdered() == nullptr)
        throw NoEmployeeInStoreException("No employees available in that store to deal with the order.");

    // Choose products
    Sale auxSale;
    cout << endl;
    store->showProducts();
    cout << "Press 0 to stop adding" << endl << endl;
    do {
        cout << "Product you want:" << endl;
        cin >> product_id;
        if (cin.fail() || cin.peek() != '\n' || (!store->findProduct(product_id) && product_id != 0)) {
            product_id = 1;
            cin.clear();
            cin.ignore(100, '\n');
            cout << "That product doesn't exist." << endl;
            continue;
        }
        else
            cin.ignore(100, '\n');
        if (product_id == 0)
            continue;

        error = false;
        cout << "How many:" << endl;
        cin >> qnt;
        if (cin.fail() || cin.peek() != '\n' || qnt == 0){
            error = true;
            cin.clear();
            cout << "That quantity is not possible" << endl;
        }
        cin.ignore(100, '\n');

        if (!error) {
            auxSale.addProduct(store->getProduct(product_id), qnt);
        }
    } while (product_id != 0);

    if (auxSale.getProducts().empty())
        throw NoProductsChoseException("Order canceled, no products were chose.");

    // Update presences of products
    for (const auto& p:auxSale.getProducts()) {
        productsPresences.remove(ProductPtr(p.first));
        p.first->addPresence();
        productsPresences.insert(ProductPtr(p.first));
    }

    // Initialize sale
    Sale* sale = new Sale(client, store);
    sale->setProducts(auxSale.getProducts(), auxSale.getTotalAmount());

    // Set employee
    sale->setEmployee(sale->getStore()->lessOrdered());
    sale->getEmployee()->addOrders(1);
    sale->getEmployee()->getDeliveries().push(ClientPtr(sale->getClient()));

    // Bill
    bill = sale->getTotalAmount();

    // Discount
    if (client->getDiscount()) {
        if (client->getRegime())
            sale->setDiscount(0.95);
        else
            sale->setDiscount(0.98);
        client->useDiscount();
    }
    else
        sale->setDiscount(1);

    sale->showSale(false);

    // Manage points
    client->addPoints(bill);
    cout << "You have " << client->getPoints() << " points." << endl;

    if (client->getDiscount()) {
        if (!client->getRegime())
            cout << "Discount of 2% in next order" << endl;
        else
            cout << "Discount of 5% in next order" << endl;
    }

    // Appraisal
    cout << "Your appraisal for the service (0-5): " << endl;
    do {
        cin >> appraisal;
        if (cin.fail() || cin.peek()!= '\n') {
            cin.clear();
            appraisal = -1;
        }
        cin.ignore(100, '\n');
    } while (appraisal < 0 || appraisal > 5);

    sale->setAppraisal(appraisal);


    sales.push_back(sale);
}

void Bakery::makeDelivery(Employee* employee) {
    unsigned id = 0;
    Client* client = employee->getDeliveries().top().getClient();

    if (employee->getDeliveries().empty())
        throw NoPendingDeliveries("No pending deliveries to this employee.");

    for (vector<Sale *>::const_reverse_iterator it = sales.rbegin(); it != sales.rend(); it++) {
        if (((*it)->getEmployee()->getNif() == employee->getNif()) &&
                ((*it)->getClient()->getNif() == client->getNif())) {
            id = (*it)->getId();
            break;
        }
    }

    cout << endl << "Order no. " << id << " was delivery to client "
        << client->getName() << " (NIF: " << client->getNif() << ")." << endl;

    employee->getDeliveries().pop();
}

void Bakery::salesVolumeByProduct() {
    map<Product*, pair<unsigned, float>> auxProducts;
    map<Product*, pair<unsigned, float>> prods; // Final map originated by merging all the maps of each sale
    for (auto sale:sales) {
        auxProducts = sale->getProducts();
        for (auto it=auxProducts.begin(); it != auxProducts.end(); it++) {
            if (prods.find(it->first) == prods.end())
                prods[it->first] = pair<unsigned, float>(it->second.first, it->second.first*it->second.second);
            else {
                prods[it->first].first += it->second.first;
                prods[it->first].second += it->second.first*it->second.second;
            }
        }
    }
    vector<pair<Product*, pair<unsigned, float>>> vProducts;
    for (auto &it:prods)
        vProducts.push_back(it);
    chooseSalesVolumeByProductSort(vProducts);
    cout << endl << setw(5) << "ID" << setw(20) << "Name" << right << setw(14) << "Total sold" << setw(14) << "Total income" << left << endl;
    for (auto p:vProducts) {
        cout << setw(5) << p.first->getId() << setw(20) << p.first->getName() << right << setw(14)
            << p.second.first << setw(14) << p.second.second << left << endl;
    }
}
void Bakery::salesVolumeByStore() {
    map<Product*, pair<unsigned, float>> auxProducts;
    map<Store*, float> stores_incomes;
    for (auto store:stores)
        stores_incomes[store] = 0;
    for (auto sale:sales) {
        auxProducts = sale->getProducts();
        for (auto it=auxProducts.begin(); it != auxProducts.end(); it++)
            stores_incomes[sale->getStore()] += it->second.first*it->second.second;
    }
    vector<pair<Store*, float>> vStores_incomes;
    for (auto &it:stores_incomes)
        vStores_incomes.push_back(it);
    sort(vStores_incomes.begin(), vStores_incomes.end(),
         [](pair<Store*, float> &p1, pair<Store*, float> &p2) {return p1.second > p2.second;});
    cout << endl << left << setw(5) << "ID" << setw(20) << "Name" << right << setw(14) << "Total income" << left << endl;
    for (auto s:vStores_incomes)
        cout << setw(5) << s.first->getId() << setw(20) << s.first->getName()
            << right << setw(14) << s.second << left << endl;
}
void Bakery::salesProductsPresences() {
    string categories[2] = {"Bread", "Cake"}, category;
    unsigned max, min;
    Category ctg = bread;
    bool goodInput = true, choseCtg;

    do {
        cout << "\nInsert 'all' to not apply any filter and show all produtcs." << endl;
        cout << "Insert 'min <minimum>' and/or 'max <maximum>' to set minimum and maximum presences of products to show." << endl;
        cout << "Insert 'bread' or 'cake' to show the products of respective category." << endl;
        cout << "e.g: cake min 10 max 50; e.g all; e.g max 10" << endl;

        string stringCommand = "", intCommand = "", line;
        max = 9999999; min = 0; choseCtg = false; goodInput = true;
        getline(cin, line);
        stringstream responseStream(line);
        try {
            do {
                responseStream >> stringCommand;
                if (stringCommand == "all") {
                    break;
                }
                else if (toLower(stringCommand) == "bread") {
                    ctg = bread;
                    choseCtg = true;
                }
                else if (toLower(stringCommand) == "cake") {
                    ctg = cake;
                    choseCtg = true;
                }
                else if (stringCommand == "min") {
                    responseStream >> intCommand;
                    min = stoul(intCommand);
                }
                else if (stringCommand == "max") {
                    responseStream >> intCommand;
                    max = stoul(intCommand);
                }
                else {
                    throw BadInput("Command does not exist");
                }
            } while (!responseStream.eof());
        }
        catch (invalid_argument &e) {
            cout << "That is not a minimum/maximum" << endl;
            goodInput = false;
        }
        catch (BadInput &e) {
            cout << e.what() << endl;
            goodInput = false;
        }
    } while (!goodInput);


    cout << left << setw(5) << "ID" << setw(10) << "Category" << setw(20) << "Name" << setw(12) << "Presences" << endl;
    iteratorBST<ProductPtr> it = productsPresences.begin();
    while (it != productsPresences.end()) {
        if ((*it).getPresences() >= min && (*it).getPresences() <= max &&
                    (!choseCtg || (*it).getProduct()->getCategory() == ctg)) {
            cout << setw(5) << (*it).getProduct()->getId() << setw(10) << categories[(*it).getProduct()->getCategory()]
                << setw(20) << (*it).getProduct()->getName() << setw(12) << (*it).getPresences() << endl;
        }
        it++;
    }
}

void Bakery::opsSalesVolume() {
    int operation;
    do {
        cout << endl << "[SALES VOLUME]" << endl;
        cout << " 0 -> Back" << endl;
        cout << " 1 -> Sales volume by product" << endl;
        cout << " 2 -> Sales volume by store" << endl;
        cout << " 3 -> Products presences" << endl;
        cout << "\n[SALES VOLUME] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                break;
            case 1:
                salesVolumeByProduct();
                break;
            case 2:
                salesVolumeByStore();
                break;
            case 3:
                salesProductsPresences();
                break;
            default:
                cout << "That operation doesn't exist" << endl;
                break;
        }
    } while (operation != 0);
}

void Bakery::opsSales() {
    int operation;
    string name;
    Client* auxC;
    vector<Store*> filterStores = stores;
    vector<Client*> filterClients = clients;
    do {
        cout << endl << "[SALES]" << endl;
        cout << " 0 -> Back" << endl;
        cout << " 1 -> Print all sales" << endl;
        cout << " 2 -> Print filter sales (Use filters first)" << endl;
        cout << " 3 -> Filter stores" << endl;
        cout << " 4 -> Filter clients" << endl;
        cout << "\n[SALES] Select operation:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            operation = -1;
        }
        cin.ignore(100, '\n');
        switch (operation) {
            case 0:
                break;
            case 1: // Print all sales
                for (auto sale:sales)
                    sale->showSale(true);
                break;
            case 2: // Print filter sales
                for (auto sale:sales)
                    if (searchStore(filterStores, sale->getStore()->getId()) != nullptr &&
                        searchClient(filterClients, sale->getClient()->getName()) != nullptr)
                        sale->showSale(true);
                break;
            case 3: // Filer sales by stores
                filterStores.clear();
                askStores(stores, filterStores);
                break;
            case 4: // Filter sales by clients
                filterClients.clear();
                showClients(clients);
                cout << "Press  0  to finish the filter" << endl;
                do {
                    askPersonData(name, "Client");
                    auxC = searchClient(clients, name);
                    if (auxC != nullptr && searchClient(filterClients, name) == nullptr)
                        filterClients.push_back(auxC);
                } while (name != "0");
                break;
            default:
                cout << "That operation doesn't exist" << endl;
                break;
        }
    } while (operation != 0);
}

void Bakery::mainMenu() {
    string name;
    unsigned nif_or_id;
    float price_or_salary;
    Store* store; Address address;
    Product *product; Category ctg; SizeType size; Layer ly1;Layer ly2;
    Client *client; bool regime;
    Employee *employee;
    string firstCommand, secondCommand, thirdCommand;
    showMenuOperations();
    do {
        firstCommand = "", secondCommand = "", thirdCommand = "";

        cout << "\n[MENU] Select operation:" << endl;
        string line;
        getline(cin, line);

        stringstream responseStream(line);
        responseStream >> firstCommand >> secondCommand >> thirdCommand; // Read user command

        if(firstCommand == "add"){
            //Add options
            if(secondCommand.empty()){
                cout << "Please insert a second argument from the list:" << endl;
                cout << " [store, employee, product, client]" << endl;
                cout << "e.g: add store " << endl;
            }
            else if(secondCommand == "store"){
                setStoreData(name, address);
                store = new Store(name, address);
                stores.push_back(store);
                storesMapping[store->getId()] = store;
            }
            else if(secondCommand == "employee"){
                setEmployeeData(name, nif_or_id, price_or_salary, stores, store);
                if (searchEmployee(employees, to_string(nif_or_id)) == nullptr) {
                    employee = new Employee(name, nif_or_id, price_or_salary);
                    employees.push_back(employee);
                    store->addEmployee(employees.back());
                    employeesMapping[employee->getNif()] = employee;
                }
                else
                    cout << "That employee already exists." << endl;
            }
            else if(secondCommand == "product"){
                setProductData(name, price_or_salary, ctg, size, ly1, ly2);
                if (ctg == bread) {
                    product = new Bread(name, price_or_salary, size);
                    products.push_back(product);
                }
                else{
                    product = new Cake(name, price_or_salary, ly1, ly2);
                    products.push_back(product);
                }
                productsPresences.insert(product);
                productsMapping[product->getId()] = product;
            }
            else if(secondCommand == "client") {
                setClientData(name, nif_or_id, regime);
                if (searchClient(clients, to_string(nif_or_id)) == nullptr) {
                    client = new Client(name, nif_or_id, regime);
                    clients.push_back(client);
                    clientsMapping[client->getNif()] = client;
                }
                else
                    cout << "That client is already registered." << endl;

            }
            else {
                cout << "Second argument is wrong." << endl;
                cout << "Please insert a second argument from the list:" << endl;
                cout << "[store, employee, product, client]" << endl;
                cout << "e.g: add store " << endl;
            }
        }
        else if(firstCommand == "view") {
            //View options
            if (secondCommand.empty()) {
                cout << "Please insert a second argument from the list:" << endl;
                cout << "[stores, employees, products, clients, sales, volume]" << endl;
                cout << "e.g: view stores " << endl;
            }
            else if (secondCommand == "stores") {
                showStores(stores);
                cout << endl;
            }
            else if (secondCommand == "employees") {
                nif_or_id = chooseEmployeesSort();
                showEmployees(stores, nif_or_id);
            }
            else if (secondCommand == "products") {
                chooseProductsSort(products);
                showProducts(products);
            }
            else if (secondCommand == "clients") {
                chooseClientsSort(clients);
                showClients(clients);
                nif_or_id = 0;
                for (auto c:clients) {
                    if (c->getRegime())
                        nif_or_id++;
                }
                cout << "Normal: " << clients.size() - nif_or_id << "     Premium: " << nif_or_id << endl;
            }
            else if (secondCommand == "sales") {
                opsSales();
            }
            else if (secondCommand == "volume") {
                opsSalesVolume();
            }
            else {
                cout << "Second argument is wrong." << endl;
                cout << "Please insert a second argument from the list:" << endl;
                cout << "[stores, employees, products, clients, sales, volume]" << endl;
                cout << "e.g: view stores" << endl;
            }
        }
        else if (firstCommand == "select") {
            //Select options
            bool inputRequired = thirdCommand.empty();
            if (secondCommand.empty()) {
                cout << "Please insert a second argument from the list:" << endl;
                cout << "[store, employee, product, client]" << endl;
                cout << "e.g: select store " << endl;
            }
            else if (secondCommand == "store") {
                if(!inputRequired){
                    stringstream(thirdCommand) >> nif_or_id;
                } else {
                    showStores(stores);
                    askId(nif_or_id, "Store");
                }
                store = searchStore(stores, nif_or_id);
                if (store != nullptr){
                    if(!inputRequired){
                        cout << endl;
                        store->showStore();
                    }
                    opsStore(store);
                }
                else
                    cout << "There is no store with the given ID." <<  endl;
            }
            else if (secondCommand == "employee") {

                if(!inputRequired){
                    name = "";
                    getline(responseStream, name);
                    name = thirdCommand + name;
                } else {
                    showEmployees(stores);
                    askPersonData(name, "Employee");
                }
                employee = searchEmployee(employees, name);
                if (employee != nullptr) {
                    if (!inputRequired) {
                        cout << endl;
                        employee->showEmployee(true);
                    }
                    opsEmployee(employee);
                }
                else
                    cout << "There is no employee with the given NIF or name." << endl;
            }
            else if (secondCommand == "product") {
                if(!inputRequired){
                    stringstream(thirdCommand) >> nif_or_id;
                } else {
                    showProducts(products);
                    askId(nif_or_id, "Product");
                }
                product = searchProduct(products, nif_or_id);
                if (product != nullptr){
                    if(!inputRequired) {
                        cout << endl;
                        product->showProduct();
                    }
                    opsProduct(product);
                }
                else
                    cout << "There is no product with the given ID." << endl;
            }
            else if (secondCommand == "client") {
                if(!inputRequired){
                    name = "";
                    getline(responseStream, name);
                    name = thirdCommand + name;
                } else {
                    showClients(clients);
                    askPersonData(name, "Client");
                }
                client = searchClient(clients, name);
                if (client != nullptr){
                    if(!inputRequired) {
                        cout << endl;
                        client->showClient(true);
                    }
                    opsClient(client);
                }
                else
                    cout << "There is no client with the given name" << endl;
            }
            else {
                cout << "Second argument is wrong." << endl;
                cout << "Please insert a second argument from the list:" << endl;
                cout << "[store, employee, product, client]" << endl;
                cout << "e.g: select store" << endl;
            }
        }
        else if(firstCommand == "order") {
            try {
                makeOrder();
            }
            catch (Exception &e) {
                cout << e.what() << endl;
            }
        }
        else if (firstCommand == "delivery") {
            bool inputRequired = secondCommand.empty();
            if(!inputRequired){
                name = "";
                getline(responseStream, name);
                name = secondCommand + name;
            }
            else {
                showEmployees(stores);
                askPersonData(name, "Employee");
            }
            employee = searchEmployee(employees, name);
            if (employee != nullptr) {
                if (!inputRequired) {
                    cout << endl;
                    employee->showEmployee(false);
                }
                try {
                    makeDelivery(employee);
                }
                catch (Exception &e) {
                    cout << e.what() << endl;
                }
            }
            else
                cout << "There is no employee with the given NIF or name." << endl;
        }
        else if(firstCommand == "help") {
            showMenuOperations();
        }
        else if(firstCommand == "exit") {
            cout << "Finish Program" << endl;
        }
        else {
            cout << "First argument is wrong." << endl;
            cout << "Insert \"help\" to see options available." << endl;
        }
    } while (firstCommand != "exit");
}

void Bakery::loadData() {
    string line;
    string path = "data/";
    try {
        ifstream is(path + Bread::FILENAME);
        //Load breads
        try {
            while (!is.eof() && is.is_open()) {
                getline(is, line);
                if (line.empty()) {
                    continue;
                }
                map<string, string> mapping = files::readData(line);
                Bread *bread = new Bread(mapping);
                Product *product = bread;
                productsMapping[bread->getId()] = product;

                if(product->getStatus()){
                    products.push_back(product);
                }
                productsPresences.insert(product);
            }
            is.close();
        }catch(exception &e){
            throw ReadingDataException("Breads");
        }
        //Load Cakes
        try {
            is = ifstream(path + Cake::FILENAME);
            while (!is.eof() && is.is_open()) {
                getline(is, line);
                map<string, string> mapping = files::readData(line);
                if (mapping.empty()) {
                    continue;
                }
                Cake *cake = new Cake(mapping);
                Product *product = cake;
                productsMapping[cake->getId()] = product;

                if(product->getStatus()) {
                    products.push_back(product);
                }
                productsPresences.insert(product);
            }
            is.close();
        } catch(exception &e){
            throw ReadingDataException("Cakes");
        }
        try {
            // Load clients
            is = ifstream(path + Client::FILENAME);
            //One line equals one Store
            while(!is.eof() && is.is_open()) {
                getline(is, line);
                if(line.empty()){
                    continue;
                }
                map<string, string> mapping = files::readData(line);
                Client *client = new Client(mapping);
                clientsMapping[client->getNif()] = client;

                if(client->getStatus()){
                    clients.push_back(client);
                }
            }
            is.close();
        } catch(exception &e){
            throw ReadingDataException("Clients");
        }
        try {
            //Load employees
            is = ifstream(path + Employee::FILENAME);
            while (!is.eof() && is.is_open()) {
                getline(is, line);
                if (line.empty()) {
                    continue;
                }
                map<string, string> mapping = files::readData(line);
                Employee *employee = new Employee(mapping, clientsMapping);
                employeesMapping[employee->getNif()] = employee;
                if(employee->getStatus()){
                    employees.push_back(employee);
                }
            }
            is.close();
        } catch (exception &e){
            throw ReadingDataException("Employees");
        }
        try {
            //Load stores
            is = ifstream(path + Store::FILENAME);
            //One line equals one Store
            while (!is.eof() && is.is_open()) {

                getline(is, line);
                if (line.empty()) {
                    continue;
                }
                map<string, string> mapping = files::readData(line);
                Store *store = new Store(mapping, productsMapping, employeesMapping);
                storesMapping[store->getId()] = store;
                stores.push_back(store);
            }
            is.close();
        } catch (exception e){
            throw ReadingDataException("Stores");
        }
        //Load Sales
        try {
            is = ifstream(path + Sale::FILENAME);
            //One line equals one Store
            while (!is.eof() && is.is_open()) {
                getline(is, line);
                if (line.empty()) {
                    continue;
                }
                map<string, string> mapping = files::readData(line);
                Sale *sale = new Sale(mapping, storesMapping, employeesMapping, clientsMapping, productsMapping);
                sales.push_back(sale);
            }
            is.close();
        } catch (exception &e){
            throw ReadingDataException("Sales");
        }

    } catch (ReadingDataException &e){
        cout << e.what() << endl;
    }
}

void Bakery::saveData(){
    string path = "data/";
    ofstream outCakes, outBreads, outEmployees, outStores, outClients, outSales;

    //Save products
    outCakes.open(path + Cake::FILENAME, ios::out);
    outBreads.open(path + Bread::FILENAME, ios::out);
    for(auto it : productsMapping){
        if(it.second->getCategory() == Category::bread){
            outBreads << *(Bread*) it.second;
        } else {
            outCakes << *(Cake*) it.second;
        }
    }
    outBreads.close();
    outCakes.close();

    //Save employees
    outEmployees.open(path + Employee::FILENAME, ios::out);
    for(auto it : employeesMapping){
        outEmployees << *(it.second);
    }
    outEmployees.close();

    //Save Stores
    outStores.open(path + Store::FILENAME, ios::out);
    for(auto it : storesMapping){
        outStores << *(it.second);
    }
    outStores.close();

    // Save Clients
    outClients.open(path + Client::FILENAME, ios::out);
    for(auto it: clientsMapping){
        outClients << *(it.second);
    }
    outClients.close();

    // Save Sales
    outSales.open(path + Sale::FILENAME, ios::out);
    for(Sale * sale : sales){
        outSales << *sale;
    }
    outSales.close();
}