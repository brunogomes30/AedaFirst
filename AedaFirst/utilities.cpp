#include "utilities.h"

using namespace std;

void showClients(const vector<Client*> &clients) {
    for (auto client:clients)
        cout << client->getNif() << " " << client->getName() << endl;
}

void showStores(const vector<Store*> &stores) {
    for (auto store:stores){
        cout << store->getId() << " -> " << store->getName() << endl;
    }
}

void showMenuOperations() {
    cout << "[MENU]" << endl;
    cout << "0 -> Exit" << endl;
    cout << "1 -> Make an order" << endl;
    cout << "2 -> Print all sales" << endl;
    cout << "3 -> Add a client" << endl;
    cout << "4 -> Search a client (submenu)" << endl;
    cout << "8 -> Add a store" << endl;
    cout << "9 -> Search a store" << endl;
}

void showClientOperations() {
    cout << "[CLIENT]" << endl;
    cout << "0 -> Exit" << endl;
    cout << "1 -> Change client's regime" << endl;
    cout << "2 -> Print client's history" << endl;
    cout << "3 -> Remove client" << endl;
}

void showStoreOperations() {
    cout << "[Store]" << endl;
    cout << "0 -> Exit" << endl;
    cout << "1 -> Print statistics" << endl;
    cout << "2 -> Print all sales" << endl;
    cout << "4 -> Remove store" << endl;
}

Client* searchClient(const vector<Client*> &clients, const string &identifier) {
    for (auto client:clients) {
        if (client->same(identifier))
            return client;
    }
    return nullptr;
}

Store* searchStore(const vector<Store*> &stores, const unsigned &id) {
    for (auto store:stores){
        if (id == store->getId()){
            return store;
        }
    }
    return nullptr;
}