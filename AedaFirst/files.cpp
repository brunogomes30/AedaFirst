#include <iostream>
#include "files.h"
#include <sstream>
using namespace std;

namespace files{
    map<string, string>  readData(const string &line){
        map<string, string> mapping;
        stringstream ss(line);
        //Read all values from line
        while (!ss.eof()) {
            //First reads name of variable, then it's value (e.g id=" 9 ")
            string variable;
            ss >> variable;
            if(variable.empty()){
                continue;
            }
            if (*(variable.end() - 1) != '\"') {
                //Must be ' " '
                throw 1;
            }
            variable = variable.substr(0, variable.size() - 2);
            string value = "", extra = "";
            do {
                if(!value.empty()){
                    value += " ";
                }
                value += extra;
                ss >> extra;

            } while (extra != "\"");
            mapping[variable] =  value;
        }
        return mapping;
    }
}