#include <Csq/Core/Runtime/memory.h>
#include <Csq/Core/Runtime/core.h>

auto plot=[&](Cell x, Cell y){
    string x_arr = "[";
    string y_arr = "[";
    
    for(Cell e : *(x.vectorVal)){
        switch(e.type){
            case Type::INT:{
                x_arr += to_string(e.intVal) + ",";
            }
            case Type::FLOAT:{
                x_arr += to_string(e.floatVal) + ",";
            }
        }
    }
    x_arr.pop_back();
    x_arr += "]";

    for(Cell e : *(y.vectorVal)){
        switch(e.type){
            case Type::INT:{
                y_arr += to_string(e.intVal) + ",";
            }
            case Type::FLOAT:{
                y_arr += to_string(e.floatVal) + ",";
            }
        }
    }
    y_arr.pop_back();
    y_arr += "]";
    // cout << x_arr << endl;
    string code = "import matplotlib.pyplot as plt;plt.plot(" + x_arr + "," + y_arr + ");plt.show();";
    string command = "python3 -c \"" + code + "\"";
    int r = system(command.c_str());
};

auto scatter=[&](Cell x, Cell y){
    string x_arr = "[";
    string y_arr = "[";
    
    for(Cell e : *(x.vectorVal)){
        switch(e.type){
            case Type::INT:{
                x_arr += to_string(e.intVal) + ",";
            }
            case Type::FLOAT:{
                x_arr += to_string(e.floatVal) + ",";
            }
        }
    }
    x_arr.pop_back();
    x_arr += "]";

    for(Cell e : *(y.vectorVal)){
        switch(e.type){
            case Type::INT:{
                y_arr += to_string(e.intVal) + ",";
            }
            case Type::FLOAT:{
                y_arr += to_string(e.floatVal) + ",";
            }
        }
    }
    y_arr.pop_back();
    y_arr += "]";
    // cout << x_arr << endl;
    string code = "import matplotlib.pyplot as plt;plt.scatter(" + x_arr + "," + y_arr + ");plt.show();";
    string command = "python3 -c \"" + code + "\"";
    int r = system(command.c_str());
};