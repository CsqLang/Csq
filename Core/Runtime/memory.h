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

// Value types
enum Type
{
    INT = 1,
    STRING = 2,
    FLOAT = 3,
    COMPOUND = 4,
    CUSTYPE = 5,
};

// Class to handle custom datatypes

// Struct for a memory cell.
struct Cell
{
    Type type;
    union {
        int ival;
        double fval;
    };
    std::string sval;
    std::vector<Cell> array;
    std::string __class__;

    Cell(){}
    Cell(const Cell& c){
        type = c.type;
        ival = c.ival;
        fval = c.fval;
        sval = c.sval;
        array = c.array;
        __class__ = c.__class__;
    }

    Cell(Type type_, int ival_){
        ival = ival_;
        type = INT ;
    }

    Cell(double fval_){
        fval = fval_;
        type = FLOAT;
    }

    Cell(string sval_){
        sval = sval_;
        type = STRING;
    }

    Cell operator+(const Cell &c) const
    {
        /**
         * Overloaded addition operator for Cell.
         * Performs addition based on the types of operands.
         * Supports string concatenation, numeric addition, and mixed-type addition.
         * @param c The Cell to be added.
         * @return Resulting Cell after addition.
         */
        Cell result;

        if (type == STRING)
        {
            // String concatenation
            result.type = STRING;
            result.sval = sval + (c.type == STRING ? c.sval : (c.type == FLOAT ? to_string(c.fval) : to_string(c.ival)));
        }
        else if (type == FLOAT || c.type == FLOAT)
        {
            // Numeric addition for floats
            result.type = FLOAT;
            result.fval = (type == FLOAT ? fval : ival) + (c.type == FLOAT ? c.fval : c.ival);
        }
        else
        {
            // Numeric addition for integers
            result.type = INT;
            result.ival = ival + c.ival;
        }

        return result;
    }

    Cell operator*(const Cell &c) const
    {
        /**
         * Overloaded multiplication operator for Cell.
         * Performs multiplication based on the types of operands.
         * Supports numeric multiplication.
         * @param c The Cell to be multiplied.
         * @return Resulting Cell after multiplication or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator * between two strings.");
            return Cell(); // Error cell
        }
        else
        {
            return (c.type == FLOAT) ? Cell{fval * c.fval} : Cell{INT, ival * c.ival};
        }
    }

    Cell operator-(const Cell &c) const
    {
        /**
         * Overloaded subtraction operator for Cell.
         * Performs subtraction based on the types of operands.
         * Supports numeric subtraction.
         * @param c The Cell to be subtracted.
         * @return Resulting Cell after subtraction or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator - between two strings.");
            return Cell(); // Error cell
        }
        else
        {
            return (type == FLOAT || c.type == FLOAT) ? Cell{fval - c.fval} : Cell{INT, ival - c.ival};
        }
    }

    Cell operator/(const Cell &c) const
    {
        /**
         * Overloaded division operator for Cell.
         * Performs division based on the types of operands.
         * Supports numeric division.
         * @param c The Cell to be divided.
         * @return Resulting Cell after division or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator / between two strings.");
            return Cell(); // Error cell
        }
        else if (c.type == FLOAT && (type == FLOAT || type == INT))
        {
            return Cell{fval / c.fval};
        }
        else
        {
            return Cell{float(float(ival) / float(c.ival))};
        }
    }

    Cell operator>(const Cell &c) const
    {
        /**
         * Overloaded greater-than operator for Cell.
         * Performs comparison based on the types of operands.
         * Supports numeric comparisons.
         * @param c The Cell to compare with.
         * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator > between two strings.");
            return Cell(); // Error cell
        }
        else
        {
            return (type == FLOAT || c.type == FLOAT) ? Cell{INT, fval > c.fval} : Cell{INT, ival > c.ival};
        }
    }

    Cell operator<(const Cell &c) const
    {
        /**
         * Overloaded less-than operator for Cell.
         * Performs comparison based on the types of operands.
         * Supports numeric comparisons.
         * @param c The Cell to compare with.
         * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator < between two strings.");
            return Cell(); // Error cell
        }
        else
        {
            return (type == FLOAT || c.type == FLOAT) ? Cell{INT, fval < c.fval} : Cell{INT, ival < c.ival};
        }
    }

    Cell operator>=(const Cell &c) const
    {
        /**
         * Overloaded greater-than-or-equal-to operator for Cell.
         * Performs comparison based on the types of operands.
         * Supports numeric and string comparisons.
         * @param c The Cell to compare with.
         * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator >= between two strings.");
            return Cell(); // Error cell
        }
        else
        {
            return (type == FLOAT || c.type == FLOAT) ? Cell{INT, fval >= c.fval} : Cell{INT, ival >= c.ival};
        }
    }

    Cell operator<=(const Cell &c) const
    {
        /**
         * Overloaded less-than-or-equal-to operator for Cell.
         * Performs comparison based on the types of operands.
         * Supports numeric and string comparisons.
         * @param c The Cell to compare with.
         * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            printf("Error: invalid use of operator <= between two strings.");
            return Cell(); // Error cell
        }
        else
        {
            return (type == FLOAT || c.type == FLOAT) ? Cell{INT, fval <= c.fval} : Cell{INT, ival <= c.ival};
        }
    }

    Cell operator==(const Cell &c) const
    {
        /**
         * Overloaded equality operator for Cell.
         * Performs comparison based on the types of operands.
         * Supports numeric and string equality comparisons.
         * @param c The Cell to compare with.
         * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            return Cell{INT, static_cast<int>(sval == c.sval)};
        }
        else
        {
            return (type == FLOAT || c.type == FLOAT) ? Cell{INT, fval == c.fval} : Cell{INT, ival == c.ival};
        }
    }

    Cell operator!=(const Cell &c) const
    {
        /**
         * Overloaded inequality operator for Cell.
         * Performs comparison based on the types of operands.
         * Supports numeric and string inequality comparisons.
         * @param c The Cell to compare with.
         * @return Resulting Cell with a boolean value indicating the comparison result or an error Cell for invalid operations.
         */
        if (c.type == STRING)
        {
            return Cell{INT, static_cast<int>(sval != c.sval)};
        }
        else if (c.type == FLOAT)
        {
            return Cell{INT, static_cast<int>(fval != c.fval)};
        }
        else
        {
            return Cell{INT, static_cast<int>(ival != c.ival)};
        }
    }

    Cell operator[](const Cell &index) const
    {
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
// Function to get the number of cells in the memory.
int memory_size() { return memory.size(); }


// This function will dump all data in the memory.
void dump()
{
    for (int i = 0; i < memory.size(); i++)
    {
        printf("[%d] => type : %d   value : ", i, memory[i].type);
        if (memory[i].type == STRING)
        {
            printf("%s\n", memory[i].sval.c_str());
        }
        else if (memory[i].type == FLOAT)
        {
            printf("%lf\n", memory[i].fval);
        }
        else if (memory[i].type == COMPOUND)
        {
            for (Cell arg : memory[i].array)
            {
                if (arg.type == STRING)
                {
                    printf("%s\n", arg.sval.c_str());
                }
                else if (arg.type == FLOAT)
                {
                    printf("%lf\n", arg.fval);
                }
                else
                {
                    printf("%d\n", arg.ival);
                }
            }
        }
        else
        {
            printf("%d\n", memory[i].ival);
        }
    }
}

// This function will clear all the memory allocated.
void freeMemory()
{
    memory.clear();
}

// Top cell address of memory
int TopCellAddress()
{
    return memory.size() - 1;
}

#endif // MEMORY_CSQ4
