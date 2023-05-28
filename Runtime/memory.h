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

 C++ is 
int a = stoi(readCell(0));
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
};


// Struct for a memory cell.
struct Cell
{
    int ival;
    double fval;
    string sval;
    Type type;
    bool used;
};


// This is the ultimate memory where everything will be stored.
vector<Cell> memory;
//Function to get the number of cells in the memory.
int memory_size(){return memory.size();}

// This will add a memory cell to the main memory and return its address.
void addCell(int val)
{
    Cell cell;
    cell.ival = val;
    cell.used = 1;
    cell.type = INT;
    memory.push_back(cell);
}

void addCell(double val)
{
    Cell cell;
    cell.fval = val;
    cell.used = 1;
    cell.type = FLOAT;
    memory.push_back(cell);
}

void addCell(string val)
{
    Cell cell;
    cell.sval = val;
    cell.used = 1;
    cell.type = Type::STRING;
    memory.push_back(cell);
}

//This function will dump all data in the memory.
void dump(){
    for(int i=0; i<memory.size(); i++){
        printf("[%d] => type : %d used : %d value : ",i,memory[i].type,memory[i].used);
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

// Modify the memory cell
void modifyCell(Cell* cell, string value){
    cell->sval = value;
    cell->type = Type::STRING;
}

void modifyCell(Cell* cell, int value){
        cell->ival = value;
        cell->type = INT;
}

void modifyCell(Cell* cell, float value){
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

#endif // MEMORY_CSQ4  