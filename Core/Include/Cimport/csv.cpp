#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <Csq/Core/Runtime/memory.h>
#include <Csq/Core/Runtime/core.h>

auto splitString=[&](const std::string& input, char delimiter){
    std::vector<std::string> result;
    std::istringstream stream(input);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
};
auto readCSV=[&](Cell fln) {

    string filename = (*fln.stringVal);
    Cell data;
    ifstream file(filename);
    string line;

    vector<Cell> _data;
    while (std::getline(file, line)) {
        line += ",";
        vector<Cell> _line;
        for(string val : splitString(line, ',')){
            if(val[0] == '\"'){

                _line.push_back(Cell(val.substr(1,val.size()-2)));
            }
            else{
                _line.push_back(Cell(std::stod(val)));
            }
        }
        Cell lne;
        lne.vectorVal = new vector<Cell>(_line);
        lne.type = Type::COMPOUND;
        _data.push_back(lne);
    }
    data.vectorVal = new vector<Cell>(_data);
    data.type = Type::COMPOUND;
    return data;
};
