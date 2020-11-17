#ifndef FILES_H
#define FILES_H
#include <map>

namespace files{

    /**
     * Writes the variable in the ostream in the correct format to load
     * @tparam T
     * @param os
     * @param name
     * @param value
     */
    template<typename T>
    void writeVariable(std::ostream &os, const std::string &name, const T &value){
        os << name <<"=\" " << value << " \" ";
    }

    /**
     * Reads the text file data from a line, and returns a map with the key as the variable name,
     *  and value as the variable value
     * @param line
     * @return
     */
    std::map<std::string, std::string>  readData(const std::string &line);
}

#endif //FILES_H
