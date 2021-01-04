#include "utilities.h"
#include <iomanip>
using namespace std;

void showStores(const vector<Store*> &stores) {
    cout << endl << left << setw(5) << "ID" << setw(30) << "Name" << setw(30) << "Address" << endl;
    for (auto store:stores){
        cout << setw(5) << store->getId() << setw(30) << store->getName() << store->getAddress().street
             << ", " << store->getAddress().locality << endl;
    }
}

void showClients(const vector<Client*> &clients) {
    cout << endl << left << setw(12) << "NIF" << setw(20) << "Name" << setw(10) << "Regime" << setw(12) << "Opinion" << endl;
    for (auto client:clients)
        client->showClient(true);
}

void showEmployees(const std::vector<Store*> &stores, const unsigned &order) {
    for (auto store:stores) {
        cout << left << endl;
        store->showStore();
        store->showEmployees(order);
    }
}

void showProducts(const std::vector<Product*> &products) {
    cout << endl << left << setw(5) << "ID" << setw(10) << "Category" << setw(20)
            << "Name" << setw(17) << "Details" << setw(6) << "Price" << endl;
    for (auto product:products) {
        product->showProduct();
    }
}

void showStoreStatistics(const vector<Sale*> &sales, const Store *store) {
    if(!sales.empty()) {
        map<unsigned, unsigned> salesByProduct;
        salesByProduct[0] = 0; //Removed products from the store
        unsigned maxNameSize = 0;
        for (Product *product : store->getProducts()) {
            if (product->getName().size() > maxNameSize) {
                maxNameSize = product->getName().size();
            }
            salesByProduct[product->getId()] = 0;
        }

        for (Sale *sale: sales) {
            if (sale->getStore() == store) {
                for (auto pair: sale->getProducts()) {
                    Product *product = pair.first;
                    unsigned quantity = pair.second.first;
                    if (!product->getStatus() || store->findProduct(product->getId())) {
                        salesByProduct[product->getId()] += quantity;
                    } else {
                        salesByProduct[0] += quantity;
                    }
                }
            }
        }

        auto max_iterator = max_element(salesByProduct.begin(), salesByProduct.end(), []
                (const pair<unsigned, unsigned> &a, const std::pair<unsigned, unsigned> &b)
                -> bool { return a.second < b.second; });
        unsigned max = max_iterator->second;

        unsigned maxlength = 30;
        cout << endl << left << "Bar chart by products sold:" << endl << endl;
        for (Product *product : store->getProducts()) {
            cout << setw(maxNameSize) << product->getName() << " | ";

            unsigned quantity = salesByProduct[product->getId()];
            auto size = (unsigned)((float)quantity / (float)max * maxlength);
            for (unsigned i = 0; i < size; i++) {
                cout << "#";
            }
            cout << " " << quantity;
            cout << endl;
        }
    } else {
        cout << "The store doesn't have any sales." << endl;
    }
}


void showMenuOperations() {
    cout << endl << endl << "[MENU]" << endl;
    cout << "There are several options available and some require extra arguments" << endl;
    cout << "\t add      -> to Add an entity, take a second argument from the list:\n\t\t\t [store, employee, product, client]" << endl;
    cout << "\t view     -> to View a set of entities, take a second argument from the list:\n\t\t\t [stores, employees, products, clients, sales, volume]" << endl;
    cout << "\t select   -> to Select an entity, take a second argument from the list: \n\t\t\t [store, employee, product, client]" << endl;
    cout << "\t order    -> to Make an Order" << endl;
    cout << "\t delivery -> to make a delivery" << endl;
    cout << "\t help     -> to show options available" << endl;
    cout << "\t exit     -> to Exit and save data" << endl;
    cout << endl;
}

void showStoreOperations() {
    cout << endl << "[STORE]" << endl;
    cout << " 0 -> Back" << endl;
    cout << " 1 -> Print statistics" << endl;
    cout << " 2 -> Print all sales" << endl;
    cout << " 3 -> Add products" << endl;
    cout << " 4 -> Remove product" << endl;
    cout << " 5 -> Change name" << endl;
    cout << " 6 -> Change address" << endl;
    cout << " 7 -> Increase wages of employees" << endl;
    cout << " 8 -> Remove store" << endl;
}

void showClientOperations() {
    cout << endl << "[CLIENT]" << endl;
    cout << "0 -> Back" << endl;
    cout << "1 -> Change client's regime" << endl;
    cout << "2 -> Print client's history" << endl;
    cout << "3 -> Remove client" << endl;
}

void showEmployeeOperations() {
    cout << endl << "[EMPLOYEE]" << endl;
    cout << "0 -> Back" << endl;
    cout << "1 -> Change employee's salary" << endl;
    cout << "2 -> Remove employee" << endl;
}

void showProductOperations() {
    cout << endl << "[PRODUCT]" << endl;
    cout << "0 -> Back" << endl;
    cout << "1 -> Change product's name" << endl;
    cout << "2 -> Change product's price" << endl;
    cout << "3 -> Add product to stores" << endl;
    cout << "4 -> Remove product" << endl;
}

string toLower(string str){
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return  std::tolower(c);});
    return str;
}

void askId(unsigned &id, string object) {
    bool error;
    do {
        error = false;
        cout << endl << object + "'s ID:" << endl;
        cin >> id;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            error = true;
            cout << " That " + object + " doesn't exist" << endl;
        }
        cin.ignore(100, '\n');
    } while (error);
}

void askPersonData(string &identifier, string person) {
    bool error;
    do {
        error = false;
        cout << endl << person+"'s name or NIF:" << endl;
        getline(cin, identifier);
        if (identifier.length() == 0)
            error = true;
    } while (error);
}

void askAddress(Address &address) {
    bool error;
    // Set store's street
    do {
        error = false;
        cout << "Store's street:" << endl;
        getline(cin, address.street);
        if (address.street.length() == 0)
            error = true;
    } while (error);
    // Set store's locality
    do {
        error = false;
        cout << "Store's locality:" << endl;
        getline(cin, address.locality);
        if (address.locality.length() == 0)
            error = true;
    } while (error);
}

void askMinNumber(unsigned &minNumber){
    bool error;
    int number;
    do {
        error = false;
        cout << "Minimum number of deliveries to increase wage:" << endl;
        cin >> number;
        if (cin.fail() || cin.peek() != '\n' || number < 0) {
            cin.clear();
            cout << "That's not a valid value!" << endl;
            error = true;
        }
    } while (error);
    minNumber = (unsigned) number;
}

void askName(string &name, string object) {
    bool error;
    do {
        error = false;
        cout << object + " name:" << endl;
        getline(cin, name);
        if (name.length() == 0)
            error = true;
    } while (error);
}

void askNif(unsigned &nif, string object) {
    bool error;
    do {
        error = false;
        cout << object << "'s NIF:" << endl;
        cin >> nif;
        if (cin.fail() || cin.peek() != '\n' || nif > 999999999 || nif < 1) {
            cin.clear();
            cout << "That's not a NIF number!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
}

void askRegime(bool &regime) {
    bool error;
    cout << left << endl << setw(5) << "OP" << setw(10) << "Regime" << endl;
    cout << setw(5) << "1" << setw(10) << "Normal" << endl;
    cout << setw(5) << "2" << setw(10) << "Premium" << endl;
    int reg;
    do {
        error = false;
        cout << endl << "Client's regime:" << endl;
        cin >> reg;
        if (cin.fail() || cin.peek() != '\n' || (reg!=1 && reg!=2)) {
            cin.clear();
            cout << "That's not a regime!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
    regime = reg==2;
}

void askSalaryOrPrice(float &price_salary, string object) {
    bool error;
    do {
        error = false;
        cout << object << ":" << endl;
        cin >> price_salary;
        if (cin.fail() || cin.peek() != '\n' || price_salary < 0) {
            cin.clear();
            cout << "That's not a valid value!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
}

void askCategory(Category &ctg) {
    int category;
    bool error;
    cout << left << endl << setw(5) << "OP" << setw(10) << "Category" << endl;
    cout << setw(5) << "1" << setw(10) << "Bread" << endl;
    cout << setw(5) << "2" << setw(10) << "Cake" << endl;
    do {
        error = false;
        cout << endl << "Product's category:" << endl;
        cin >> category;
        if (cin.fail() || cin.peek() != '\n' || (category != 1 && category != 2)) {
            cin.clear();
            cout << "That's not a category!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
    if (category == 1) ctg = bread;
    else ctg = cake;
}

void askBreadSize(SizeType &size) {
    int s;
    bool error;
    cout << endl << setw(5) << "OP" << setw(10) << "Bread size" << endl;
    cout << setw(5) << "1" << setw(10) << "Small" << endl;
    cout << setw(5) << "2" << setw(10) << "Big" << endl;
    do {
        error = false;
        cout << endl << "Bread's size:" << endl;
        cin >> s;
        if (cin.fail() || cin.peek() != '\n' || (s != 1 && s != 2)) {
            cin.clear();
            cout << "That's not a bread size!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
    if (s == 1) size = small;
    else size = big;
}

void askCakeLayer(Layer &ly, string object) {
    int layer;
    bool error;
    cout << endl << setw(5) << "OP" << setw(10) << "Cake layer" << endl;
    cout << setw(5) << "1" << setw(10) << "Crispy" << endl;
    cout << setw(5) << "2" << setw(10) << "Puff" << endl;
    cout << setw(5) << "3" << setw(10) << "Sponge" << endl;
    do {
        error = false;
        cout << endl << "Cake's Layer " << object << ":" << endl;
        cin >> layer;
        if (cin.fail() || cin.peek() != '\n' || (layer != 1 && layer != 2 && layer != 3)) {
            cin.clear();
            cout << "That's not a cake layer!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
    if (layer == 1) ly = crispy;
    else if (layer == 2) ly = puff;
    else ly = sponge;
}

void askStores(const vector<Store*> &stores, vector<Store*> &filterStores) {
    unsigned id;
    Store* auxS;
    showStores(stores);
    cout << "Press  0  to finish the filter" << endl;
    do {
        askId(id, "Store");
        auxS = searchStore(stores, id);
        if (auxS != nullptr && searchStore(filterStores, id) == nullptr)
            filterStores.push_back(auxS);
    } while (id != 0);
}

void setStoreData(string &name, Address &address) {
    // Set store's name
    askName(name, "Store");
    // Set store's address
    askAddress(address);
}

void setClientData(string &name, unsigned &nif, bool &regime) {
    // Set client's name
    askName(name, "Client");
    // Set client's NIF
    askNif(nif, "Client");
    // Set client's regime
    askRegime(regime);
}

void setEmployeeData(string &name, unsigned &nif, float &salary, const vector<Store*> &stores, Store* &store) {
    bool error;
    // Set employee's name
    askName(name, "Employee's");
    // Set employee's NIF
    askNif(nif, "Employee");
    // Set employee's salary
    askSalaryOrPrice(salary, "Employee's salary");
    // Set employee's store
    unsigned id;
    do {
        error = false;
        showStores(stores);
        askId(id, "Store");
        store = searchStore(stores, id);
        if (store == nullptr) {
            cout << "That store doesn't exist" << endl;
            error = true;
        }
    } while (error);
}

void setProductData(string &name, float &price, Category &ctg, SizeType &size, Layer &ly1, Layer &ly2) {
    // Set category
    askCategory(ctg);
    // Set name
    askName(name, "Product");
    // Set price
    askSalaryOrPrice(price, "Product's price");
    if (ctg == bread)
        askBreadSize(size);
    else {
        askCakeLayer(ly1, "1");
        askCakeLayer(ly2, "2");
    }
}

Store* searchStore(const vector<Store*> &stores, unsigned id) {
    auto it = find_if(stores.begin(), stores.end(),
                      [&id](const Store* store){return store->getId() == id;});
    if (it!=stores.end())
        return *it;
    else
        return nullptr;
}

Client* searchClient(const vector<Client*> &clients, const string &identifier) {
    auto it = find_if(clients.begin(), clients.end(),
                      [&identifier](const Client* client){return client->same(identifier);});
    if (it!=clients.end())
        return *it;
    else
        return nullptr;

}

Employee* searchEmployee(const vector<Employee*> &employees, const string &identifier) {
    auto it = find_if(employees.begin(), employees.end(),
                      [&identifier](const Employee* employee){return employee->same(identifier);});
    if (it!=employees.end())
        return *it;
    else
        return nullptr;
}

Product* searchProduct(const vector<Product*> &products, unsigned id) {
    auto it = find_if(products.begin(), products.end(),
                      [&id](const Product* product){return product->getId() == id;});
    if (it!=products.end())
        return *it;
    else
        return nullptr;
}

bool order() {
    int descending;
    do {
        cout << endl << setw(5) << "OP" << setw(12) << "Order" << endl;
        cout << setw(5) << "1" << setw(12) << "Ascending" << endl;
        cout << setw(5) << "2" << setw(12) << "Descending" << endl;
        cout << endl << "Choose order of sort:" << endl;
        cin >> descending;
        if (cin.fail() || cin.peek() != '\n' || (descending != 1 && descending != 2)) {
            cin.clear();
            descending = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (descending == -1);
    return descending==2;
}

bool cmpByIncome(const pair<Product*, pair<unsigned, float>> &p1, const pair<Product*, pair<unsigned, float>> &p2) {
    return p1.second.second < p2.second.second;
}

bool cmpByQuantitySold(const pair<Product*, pair<unsigned, float>> &p1, const pair<Product*, pair<unsigned, float>> &p2) {
    return p1.second.first < p2.second.first;
}

void sortByIncome(std::vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    sort(vProducts.begin(), vProducts.end(), cmpByIncome);
}

void sortByQuantitySold(std::vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    sort(vProducts.begin(), vProducts.end(), cmpByQuantitySold);
}

template<class T>
bool cmpPersonsByName(T* &person1, T* &person2) {
    return person1->getName() < person2->getName();
}
template<class T>
bool cmpPersonsByNif(T* &person1, T* &person2) {
    return person1->getNif() < person2->getNif();
}

bool cmpEmployeesBySalary(Employee* &employee1, Employee* &employee2) {
    return employee1->getSalary()<employee2->getSalary();
}
bool cmpProductsById(Product* &product1, Product* &product2) {
    return product1->getId()<product2->getId();
}

bool cmpProductsByCategory(Product* &product1, Product* &product2) {
    if (product1->getCategory() == product2->getCategory())
        return product1->getName()<product2->getName();
    return product1->getCategory() < product2->getCategory();
}

bool cmpProductsByPrice(Product* &product1, Product* &product2) {
    return product1->getPrice() < product2->getPrice();
}

void sortEmployeesByName(vector<Employee*> &employees) {
    sort(employees.begin(), employees.end(), cmpPersonsByName<Employee>);
}

void sortEmployeesByNif(vector<Employee*> &employees) {
    sort(employees.begin(), employees.end(), cmpPersonsByNif<Employee>);
}

void sortEmployeesBySalary(vector<Employee*> &employees) {
    sort(employees.begin(), employees.end(), cmpEmployeesBySalary);
}

void sortProductsById(vector<Product*> &products) {
    sort(products.begin(), products.end(), cmpProductsById);
}

void sortProductsByCategory(vector<Product*> &products) {
    sort(products.begin(), products.end(), cmpProductsByCategory);
}

void sortProductsByPrice(vector<Product*> &products) {
    sort(products.begin(), products.end(), cmpProductsByPrice);
}

void sortClientsByName(vector<Client*> &clients) {
    sort(clients.begin(), clients.end(), cmpPersonsByName<Client>);
}

void sortClientsByNif(vector<Client*> &clients) {
    sort(clients.begin(), clients.end(), cmpPersonsByNif<Client>);
}

unsigned chooseEmployeesSort() {
    unsigned operation;
    do {
        cout << left << endl << setw(5) << "OP" << "Sort by" << endl;
        cout << setw(5) << "1" << "Name" << endl;
        cout << setw(5) << "2" << "NIF" << endl;
        cout << setw(5) << "3" << "Salary" << endl;
        cout << endl << "Choose sort:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 1 && operation != 2 && operation != 3)) {
            cin.clear();
            operation = 0;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == 0);
    if (order())
        operation += 3;
    return operation;
}

void chooseProductsSort(vector<Product*> &products) {
    int operation;
    do {
        cout << left << endl << setw(5) << "OP" << "Sort by" << endl;
        cout << setw(5) << "1" << "ID" << endl;
        cout << setw(5) << "2" << "Category and name" << endl;
        cout << setw(5) << "3" << "Price" << endl;
        cout << endl << "Choose sort:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 1 && operation != 2 && operation != 3)) {
            cin.clear();
            operation = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == -1);
    if (operation == 1)
        sortProductsById(products);
    else if (operation == 2)
        sortProductsByCategory(products);
    else
        sortProductsByPrice(products);

    if (order())
        reverse(products.begin(), products.end());
}

void chooseClientsSort(vector<Client*> &clients) {
    int operation;
    do {
        cout << left << endl << setw(5) << "OP" << "Sort by" << endl;
        cout << setw(5) << "1" << "Name" << endl;
        cout << setw(5) << "2" << "NIF" << endl;
        cout << endl << "Choose sort:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 1 && operation != 2)) {
            cin.clear();
            operation = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == -1);
    if (operation == 1)
        sortClientsByName(clients);
    else
        sortClientsByNif(clients);

    if (order())
        reverse(clients.begin(), clients.end());
}

void chooseSalesVolumeByProductSort(vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    int operation;
    bool descending;
    do {
        cout << endl << left << setw(5) << "OP" << "Sort by" << endl;
        cout << setw(5) << "1" << "Quantity sold" << endl;
        cout << setw(5) << "2" << "Income" << endl;
        cout << endl << "Choose sort:" << endl;
        cin >> operation;
        if (cin.fail() || cin.peek() != '\n' || (operation != 1 && operation != 2)) {
            cin.clear();
            operation = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (operation == -1);
    descending = order();
    if (operation == 1)
        sortByQuantitySold(vProducts);
    else
        sortByIncome(vProducts);

    if (descending)
        reverse(vProducts.begin(), vProducts.end());
}
