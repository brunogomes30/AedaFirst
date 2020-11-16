#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class Exception {
private:
    std::string explanation;
public:
    Exception(std::string ex) {explanation = ex;}
    void what() const {cout << endl << explanation << endl;}
};

class NoEmployeeInStoreException:public Exception {
public:
    NoEmployeeInStoreException(std::string ex):Exception(ex) {}
};

class NoClientInClientsException:public Exception {
public:
    NoClientInClientsException(std::string ex):Exception(ex) {}
};

class NoProductsChoseException:public Exception {
public:
    NoProductsChoseException(std::string ex):Exception(ex) {}
};

#endif //EXCEPTIONS_H
