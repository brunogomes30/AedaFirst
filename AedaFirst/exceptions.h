#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <exception>

class Exception : public exception {
private:
    std::string explanation;
public:
    Exception(std::string ex) {explanation = ex;}
    virtual const char* what() const throw(){return explanation.c_str();}
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

class BadInput:public Exception {
public:
    BadInput(std::string ex):Exception(ex) {}
};

class NoPendingDeliveries:public Exception {
public:
    NoPendingDeliveries(std::string ex):Exception(ex) {}
};

class ReadingDataException : public Exception {
public:
    ReadingDataException(std::string ex) : Exception("Error reading " + ex + "Data "){}

};

#endif //EXCEPTIONS_H
