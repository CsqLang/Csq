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
int a = stoi(heap[0]);
*/


#include <string>
#include <vector>
using namespace std;


//Value types
enum Type{
    INT,
    STR,
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
    cell.type = STR;
    memory.push_back(cell);
}

//This function will dump all data in the memory.
void dump(){
    for(int i=0; i<memory.size(); i++){
        printf("[%d] => type : %d used : %d value : ",i,memory[i].type,memory[i].used);
        if(memory[i].type == STR){
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
        case STR:{
            return memory[address].sval;
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
    if(cell->type != STR){
        printf("Error: couldn't allocate a str value into a cell of different type.");
    }
    else{
        cell->sval = value;
    }
}

void modifyCell(Cell* cell, int value){
    if(cell->type != INT){
        printf("Error: couldn't allocate an int value into a cell of different type.");
    }
    else{
        cell->ival = value;
    }
}

void modifyCell(Cell* cell, float value){
    if(cell->type != FLOAT){
        printf("Error: couldn't allocate an float value into a cell of different type.");
    }
    else{
        cell->fval = value;
    }
}

#endif // MEMORY_CSQ4  
