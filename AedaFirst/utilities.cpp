#include "utilities.h"

using namespace std;

void showClients(const vector<Client*> &clients) {
    for (auto client:clients)
        cout << client->getNif() << " " << client->getName() << endl;
}

void showStores(const vector<Store*> &stores) {
    for (auto store:stores){
        cout << store->getId() << "  " << store->getName() << "\t\t" << store->getAddress().street
            << ", " << store->getAddress().locality << endl;
    }
}

void showProducts(const std::vector<Product*> &products) {
    for (auto product:products) {
        cout << product->getId() << " " << product->getName() << " " << product->getPrice() << endl;
    }
}


void showMenuOperations() {
    cout << "[MENU]" << endl;
    cout << " 0 -> Exit" << endl;
    cout << " 1 -> Print stores" << endl;
    cout << " 2 -> Add a store" << endl;
    cout << " 3 -> Search a store (Submenu)" << endl;
    cout << " 4 -> Print clients" << endl;
    cout << " 5 -> Add a client" << endl;
    cout << " 6 -> Search a client (Submenu)" << endl;
    cout << "# 7 -> Print employees" << endl;
    cout << "# 8 -> Add an employee" << endl;
    cout << "# 9 -> Search an employee" << endl;
    cout << "#10 -> Print products" << endl;
    cout << "#11 -> Add a product" << endl;
    cout << "#12 -> Search a product" << endl;
    cout << "13 -> Make an order" << endl;
    cout << "14 -> Print sales volume (Submenu)" << endl;
    cout << "15 -> Print all sales" << endl;
}

void showClientOperations() {
    cout << "[CLIENT]" << endl;
    cout << "0 -> Back" << endl;
    cout << "1 -> Change client's regime" << endl;
    cout << "#2 -> Print client's history" << endl;
    cout << "3 -> Remove client" << endl;
}

void showStoreOperations() {
    cout << "[Store]" << endl;
    cout << " 0 -> Exit" << endl;
    cout << "# 1 -> Print statistics" << endl;
    cout << " 2 -> Print all sales" << endl;
    cout << " 3 -> Add a product" << endl;
    cout << " 4 -> Remove store" << endl;
}

void setClientData(string &identifier) {
    bool error;
    do {
        error = false;
        cout << "Client's name or NIF:" << endl;
        getline(cin, identifier);
        if (identifier.length() == 0)
            error = true;
    } while (error);
}

void setClientData(string &name, unsigned &nif, bool &regime) {
    bool error;
    // Set client's name
    do {
        error = false;
        cout << "New client's name:" << endl;
        getline(cin, name);
        if (name.length() == 0)
            error = true;
    } while (error);
    // Set client's NIF
    do {
        error = false;
        cout << "New client's NIF:" << endl;
        cin >> nif;
        if (cin.fail() || cin.peek() != '\n' || nif > 999999999 || nif < 1) {
            cin.clear();
            cout << "That's not a NIF number!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
    // Set client's regime
    cout << "0 -> Normal regime" << endl;
    cout << "1 -> Premium regime" << endl;
    do {
        error = false;
        cout << "New client's regime:" << endl;
        cin >> regime;
        if (cin.fail() || cin.peek() != '\n') {
            cin.clear();
            cout << "That's not a regime!" << endl;
            error = true;
        }
        cin.ignore(100, '\n');
    } while (error);
}

void setStoreData(unsigned &id) {
    bool error;
    do {
        error = false;
        cout << "Store's ID:" << endl;
        cin >> id;
        if (cin.fail() || cin.peek() != '\n') {
            error = true;
            cout << " That store doesn't exist" << endl;
        }
    } while (error);
}

void setStoreData(string &name, Address &address) {
    bool error;
    // Set store's name
    do {
        error = false;
        cout << "New store's name:" << endl;
        getline(cin, name);
        if (name.length() == 0)
            error = true;
    } while (error);
    // Set store's street
    do {
        error = false;
        cout << "New store's street:" << endl;
        getline(cin, address.street);
        if (address.street.length() == 0)
            error = true;
    } while (error);
    // Set store's locality
    do {
        error = false;
        cout << "New store's locality:" << endl;
        getline(cin, address.locality);
        if (address.locality.length() == 0)
            error = true;
    } while (error);
}

Client* searchClient(const vector<Client*> &clients, const string &identifier) {
    for (auto client:clients) {
        if (client->same(identifier))
            return client;
    }
    return nullptr;
}

Store* searchStore(const vector<Store*> &stores, unsigned id) {
    Store searchingStore(id);
    auto it = find_if(stores.begin(), stores.end(),
                      [&searchingStore](const Store* store){return *store == searchingStore;});
    if (it!=stores.end())
        return *it;
    else
        return nullptr;
}

void searchEmployee() {}

Product* searchProduct(const vector<Product*> &products, unsigned id) {
    Product searchingProduct(id);
    auto it = find_if(products.begin(), products.end(),
                      [&searchingProduct](const Product* product){return *product == searchingProduct;});
    if (it!=products.end())
        return *it;
    else
        return nullptr;
}

bool order() {
    int descending;
    do {
        cout << "0 -> Ascending" << endl;
        cout << "1 -> Descending" << endl;
        cin >> descending;
        if (cin.fail() || cin.peek() != '\n' || (descending != 0 && descending != 1)) {
            cin.clear();
            descending = -1;
            cout << "That is not a possible sort" << endl;
        }
        cin.ignore(100, '\n');
    } while (descending == -1);
    return (bool)descending;
}

bool cmpByIncome(const pair<Product*, pair<unsigned, float>> &p1, const pair<Product*, pair<unsigned, float>> &p2) {
    return p1.second.second > p2.second.second;
}

bool cmpByQuantitySold(const pair<Product*, pair<unsigned, float>> &p1, const pair<Product*, pair<unsigned, float>> &p2) {
    return p1.second.first > p1.second.first;
}

void sortByIncome(std::vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    sort(vProducts.begin(), vProducts.end(), cmpByIncome);
}

void sortByQuantitySold(std::vector<pair<Product*, pair<unsigned, float>>> &vProducts) {
    sort(vProducts.begin(), vProducts.end(), cmpByQuantitySold);
}

bool cmpClientsByName(Client* &client1, Client* &client2) {
    return client1->getName() < client2->getName();
}

bool cmpClientsByNif(Client* &client1, Client* &client2) {
    return client1->getNif() < client2->getNif();
}

void sortClientsByName(std::vector<Client*> &clients) {
    sort(clients.begin(), clients.end(), cmpClientsByName);
}

void sortClientsByNif(std::vector<Client*> &clients) {
    sort(clients.begin(), clients.end(), cmpClientsByNif);
}

