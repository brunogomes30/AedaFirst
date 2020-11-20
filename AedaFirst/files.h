#ifndef FILES_H
#define FILES_H
#include <map>

namespace files{

    /**
     * Writes the variable in the ostream in the correct format to load.
     * @tparam T Types of values to be saved.
     * @param os Ostream
     * @param name Name of the variable.
     * @param value Value/Values of the variable.
     */
    template<typename T>
    void writeVariable(std::ostream &os, const std::string &name, const T &value){
        os << name <<"=\" " << value << " \" ";
    }

    /**
     * Reads the text file data from a line.
     * @param line Line corresponding to an entity.
     * @return Map with the key as the variable name and value as the variable value.
     */
    std::map<std::string, std::string>  readData(const std::string &line);
}

#endif //FILES_H
