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
#include <memory>
using namespace std;


//Value types
enum Type{
    INT,
    STRING,
    FLOAT,
    COMPOUND,
    CUSTYPE,
};

//Class to handle custom datatypes
class CusType{
    public:
        virtual ~CusType() = default;
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
    shared_ptr<CusType> cus_type;


    Cell operator+(const Cell& c) const {
        /**
             * Overloaded addition operator for Cell.
             * Performs addition based on the types of operands.
             * Supports string concatenation, numeric addition, and mixed-type addition.
             * @param c The Cell to be added.
             * @return Resulting Cell after addition.
        */ 
        Cell result;

        if (type == STRING) {
            // String concatenation
            result.type = STRING;
            result.sval = sval + (c.type == STRING ? c.sval : (c.type == FLOAT ? to_string(c.fval) : to_string(c.ival)));
        } else if (type == FLOAT || c.type == FLOAT) {
            // Numeric addition for floats
            result.type = FLOAT;
            result.fval = (type == FLOAT ? fval : ival) + (c.type == FLOAT ? c.fval : c.ival);
        } else {
            // Numeric addition for integers
            result.type = INT;
            result.ival = ival + c.ival;
        }

        return result;
    }


    Cell operator*(const Cell& c) const {
        /**
             * Overloaded multiplication operator for Cell.
             * Performs multiplication based on the types of operands.
             * Supports numeric multiplication.
             * @param c The Cell to be multiplied.
             * @return Resulting Cell after multiplication or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator * between two strings.");
            return Cell();  // Error cell
        } else {
            return (c.type == FLOAT) ? Cell{FLOAT, 0, 0,fval * c.fval} : Cell{INT, 0, ival * c.ival};
        }
    }

    Cell operator-(const Cell& c) const {
        /**
             * Overloaded subtraction operator for Cell.
             * Performs subtraction based on the types of operands.
             * Supports numeric subtraction.
             * @param c The Cell to be subtracted.
             * @return Resulting Cell after subtraction or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator - between two strings.");
            return Cell();  // Error cell
        } else {
            return (type == FLOAT || c.type == FLOAT) ? Cell{FLOAT, 0, 0,fval - c.fval} : Cell{INT, 0, ival - c.ival};
        }
    }


    Cell operator/(const Cell& c) const {
        /**
             * Overloaded division operator for Cell.
             * Performs division based on the types of operands.
             * Supports numeric division.
             * @param c The Cell to be divided.
             * @return Resulting Cell after division or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator / between two strings.");
            return Cell();  // Error cell
        } else if (c.type == FLOAT && (type == FLOAT || type == INT)) {
            return Cell{FLOAT, 0, 0,fval / c.fval};
        } else {
            return Cell{INT, 0, ival / c.ival};
        }
    }

 
    Cell operator>(const Cell& c) const {
        /**
             * Overloaded greater-than operator for Cell.
             * Performs comparison based on the types of operands.
             * Supports numeric comparisons.
             * @param c The Cell to compare with.
             * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator > between two strings.");
            return Cell();  // Error cell
        } else {
            return (type == FLOAT || c.type == FLOAT) ? Cell{FLOAT, 0, fval > c.fval} : Cell{INT, 0, ival > c.ival};
        }
    }


    Cell operator<(const Cell& c) const {
        /**
             * Overloaded less-than operator for Cell.
             * Performs comparison based on the types of operands.
             * Supports numeric comparisons.
             * @param c The Cell to compare with.
             * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator < between two strings.");
            return Cell();  // Error cell
        } else {
            return (type == FLOAT || c.type == FLOAT) ? Cell{FLOAT, 0, fval < c.fval} : Cell{INT, 0, ival < c.ival};
        }
    }

    
    Cell operator>=(const Cell& c) const {
        /**
             * Overloaded greater-than-or-equal-to operator for Cell.
             * Performs comparison based on the types of operands.
             * Supports numeric and string comparisons.
             * @param c The Cell to compare with.
             * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator >= between two strings." );
            return Cell();  // Error cell
        } else {
            return (type == FLOAT || c.type == FLOAT) ? Cell{FLOAT, 0, fval >= c.fval} : Cell{INT, 0, ival >= c.ival};
        }
    }

   
    Cell operator<=(const Cell& c) const {
        /**
             * Overloaded less-than-or-equal-to operator for Cell.
             * Performs comparison based on the types of operands.
             * Supports numeric and string comparisons.
             * @param c The Cell to compare with.
             * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            printf("Error: invalid use of operator <= between two strings.");
            return Cell();  // Error cell
        } else {
            return (type == FLOAT || c.type == FLOAT) ? Cell{FLOAT, 0, fval <= c.fval} : Cell{INT, 0, ival <= c.ival};
        }
    }

   
    Cell operator==(const Cell& c) const {
        /**
             * Overloaded equality operator for Cell.
             * Performs comparison based on the types of operands.
             * Supports numeric and string equality comparisons.
             * @param c The Cell to compare with.
             * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            return Cell{FLOAT, 0, 0,static_cast<float>(sval == c.sval)};
        } else {
            return (type == FLOAT || c.type == FLOAT) ? Cell{FLOAT, 0, fval == c.fval} : Cell{INT, 0, ival == c.ival};
        }
    }

    
    Cell operator!=(const Cell& c) const {
        /**
             * Overloaded inequality operator for Cell.
             * Performs comparison based on the types of operands.
             * Supports numeric and string inequality comparisons.
             * @param c The Cell to compare with.
             * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
        */
        if (c.type == STRING) {
            return Cell{FLOAT, 0, 0,static_cast<float>(sval != c.sval)};
        } else if (c.type == FLOAT) {
            return Cell{FLOAT, 0, 0,static_cast<float>(fval != c.fval)};
        } else {
            return Cell{FLOAT, 0, 0,static_cast<float>(ival != c.ival)};
        }
    }

    
    Cell operator[](const Cell& index) const {
        /**
         * Overloaded subscript operator for Cell.
         * Retrieves the element at the specified index in the array.
         * @param index The index Cell.
         * @return Resulting Cell containing the array element or an error Cell for invalid operations.
        */
        return array[static_cast<int>(index.fval)];
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

void addCell(const CusType& object){
    Cell cell;
    cell.cus_type = make_shared<CusType>(object);
    cell.type = CUSTYPE;
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
