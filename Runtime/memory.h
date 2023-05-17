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

// Struct for a memory cell.
struct Cell
{
    string value;
    bool used;
};

// This is the ultimate memory where everything will be stored.
vector<Cell> memory;
vector<bool> usedStatus;

// This will add a memory cell to the main memory and return its address.
int addCell(Cell cell)
{
    memory.emplace_back(cell);
    usedStatus.push_back(true);
    return memory.size() - 1;
}

// Check if a cell is available at the given address.
bool isCellAvailable(int address)
{
    return address >= 0 && address < usedStatus.size() && !usedStatus[address];
}


/*
A must needed boiler plate for speeding the
*/

#endif // MEMORY_CSQ4  
