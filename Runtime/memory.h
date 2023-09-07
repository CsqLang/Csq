#if !defined(MEMORY_CSQ4)
#define MEMORY_CSQ4


/*
Memory Layout of Csq code:

The memory used by the Csq code is in the form of array which contains the values and 
an address. 
So how it will be used by C++ compiler?
The Csq code is : 
a:=83


Memory view
 -----------------
 Value       address
|83 ----------> 0   |
|                   |
|                   |
|                   |    
|                   |
 --------------------

***********************

*/


#include <string>
#include <vector>
using namespace std;


//Value types
enum Type{
    INT,
    STRING,
    FLOAT,
    COMPOUND,
};


// Struct for a memory cell.
struct Cell
{
    Type type;
    int u_count;
    int ival;
    double fval;
    string sval;
    vector<Cell> array;

    Cell operator+(Cell c){
        if(c.type == STRING && type == STRING){
            Cell c1;
            c1.type = STRING;
            c1.sval = sval + c.sval;
            return c1;
        }
        else if(type == STRING && c.type == FLOAT){
            Cell c1;
            c1.type = STRING;
            c1.sval = sval + to_string(c.fval);
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval + c.fval;
            return c1;
        }
    }

    Cell operator*(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator * between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval * c.fval;
            return c1;
        }
    }
    Cell operator-(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator - between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval - c.fval;
            return c1;
        }
    }
    Cell operator/(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator / between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval / c.fval;
            return c1;
        }
    }
    Cell operator>(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator > between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval > c.fval;
            return c1;
        }
    }
    Cell operator<(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator < between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval < c.fval;
            return c1;
        }
    }
    Cell operator>=(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator >= between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval >= c.fval;
            return c1;
        }
    }
    Cell operator<=(Cell c){
        if(c.type == STRING){
            Cell c1;
            printf("Error: invalid use of operator <= between two strings.");
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval <= c.fval;
            return c1;
        }
    }
    Cell operator==(Cell c){
        if(c.type == STRING){
            Cell c1;
            c1.type = FLOAT;
            c1.fval = c.sval == sval;
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval == c.fval;
            return c1;
        }
    }
    Cell operator!=(Cell c){
        if(c.type == STRING){
            Cell c1;
            c1.type = FLOAT;
            c1.fval = c.sval != sval;
            return c1;
        }
        else{
            Cell c1;
            c1.type = FLOAT;
            c1.fval = fval != c.fval;
            return c1;
        }
    }
    Cell operator[](Cell index){
        return array[int(index.fval)];
    }
};


// This is the ultimate memory where everything will be stored.
vector<Cell> memory;
//Function to get the number of cells in the memory.
int memory_size(){return memory.size();}

void addCell(int val) {
    Cell cell;
    cell.ival = val;
    cell.type = INT;
    cell.u_count = 0;
    memory.emplace_back(cell);
}

void addCell(double val) {
    Cell cell;
    cell.fval = val;
    cell.type = FLOAT;
    cell.u_count = 0;
    memory.emplace_back(cell);
}

void addCell(const string& val) {
    memory.emplace_back(Cell{STRING, 0, 0, 0.0, val});
}

void addCell(const vector<Cell>& array) {
    // memory.insert(memory.end(), array.begin(), array.end());
    Cell c;
    c.type = COMPOUND;
    for(Cell e : array){
        c.array.push_back(e);
    }
    memory.push_back(c);
}
//This function will dump all data in the memory.
void dump(){
    for(int i=0; i<memory.size(); i++){
        printf("[%d] => type : %d used : %d  value : ",i,memory[i].type,memory[i].u_count);
        if(memory[i].type == STRING){
            printf("%s\n",memory[i].sval.c_str());
        }
        else if(memory[i].type == FLOAT){
            printf("%lf\n",memory[i].fval);
        }
        else{
            printf("%d\n",memory[i].ival);
        }
    }
}

// Read the value of at address
string readCell(int address){
    switch(memory[address].type){
        case INT:{
            return to_string(memory[address].ival);
        }
        case STRING:{
            return "\"" + memory[address].sval + "\"";
        }
        default:{
            return to_string(memory[address].fval);
        }
    }
}

Cell* getCellPtr(int address){
    return &memory[address];
}

void modifyCell(Cell* cell, const string& value) {
    cell->sval = value;
    cell->type = Type::STRING;
}

void modifyCell(Cell* cell, int value) {
    cell->ival = value;
    cell->type = INT;
}

void modifyCell(Cell* cell, float value) {
    cell->fval = value;
    cell->type = FLOAT;
}

//This function will clear all the memory allocated.
void freeMemory(){
    memory.clear();
}

//Top cell address of memory
int TopCellAddress(){
    return memory.size()-1;
}


//GC----------------------------------------------->
void Free(){
    for(int i = 0;i<memory.size();i++){
        if(memory[i].u_count == 0){
            //Free its a garbage cell
            memory.erase(memory.begin() + i);
        }
    }
}



#endif // MEMORY_CSQ4  
