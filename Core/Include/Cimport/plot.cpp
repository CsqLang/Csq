#include <Csq/Core/Runtime/memory.h>
#include <Csq/Core/Runtime/core.h>

auto plot=[&](Cell x, Cell y){
    string x_arr = "[";
    string y_arr = "[";
    
    for(Cell e : *(x.vectorVal)){
        switch(e.type){
            case Type::INT:{
                x_arr += to_string(e.intVal) + ",";
                break;
            }
            case Type::FLOAT:{
                x_arr += to_string(e.floatVal) + ",";
                break;
            }
        }
    }
    x_arr.pop_back();
    x_arr += "]";

    for(Cell e : *(y.vectorVal)){
        switch(e.type){
            case Type::INT:{
                y_arr += to_string(e.intVal) + ",";
                break;
            }
            case Type::FLOAT:{
                y_arr += to_string(e.floatVal) + ",";
                break;
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
                break;
            }
            case Type::FLOAT:{
                x_arr += to_string(e.floatVal) + ",";
                break;
            }
        }
    }
    x_arr.pop_back();
    x_arr += "]";

    for(Cell e : *(y.vectorVal)){
        switch(e.type){
            case Type::INT:{
                y_arr += to_string(e.intVal) + ",";
                break;
            }
            case Type::FLOAT:{
                y_arr += to_string(e.floatVal) + ",";
                break;
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

auto bar=[&](Cell x, Cell y){
    string x_arr = "[";
    string y_arr = "[";
    
    for(Cell e : *(x.vectorVal)){
            x_arr += (*e.stringVal) + ",";
    }
    x_arr.pop_back();
    x_arr += "]";

    for(Cell e : *(y.vectorVal)){
        switch(e.type){
            case Type::INT:{
                y_arr += to_string(e.intVal) + ",";
                break;
            }
            case Type::FLOAT:{
                y_arr += to_string(e.floatVal) + ",";
                break;
            }
        }
    }
    y_arr.pop_back();
    y_arr += "]";
    
    string code = "import matplotlib.pyplot as plt;plt.bar(" + x_arr + "," + y_arr + ");plt.show();";
    string command = "python3 -c \"" + code + "\"";
    int r = system(command.c_str());
};
auto pie=[&](Cell x, Cell y){
    string x_arr = "[";
    string y_arr = "[";
    
    for(Cell e : *(x.vectorVal)){
            x_arr += (*e.stringVal) + ",";
    }
    x_arr.pop_back();
    x_arr += "]";

    for(Cell e : *(y.vectorVal)){
        switch(e.type){
            case Type::INT:{
                y_arr += to_string(e.intVal) + ",";
                break;
            }
            case Type::FLOAT:{
                y_arr += to_string(e.floatVal) + ",";
                break;
            }
        }
    }
    y_arr.pop_back();
    y_arr += "]";
    
    string code = "import matplotlib.pyplot as plt;plt.pie(" + y_arr + ",labels = " + x_arr + ");plt.show();";
    string command = "python3 -c \"" + code + "\"";
    int r = system(command.c_str());
};