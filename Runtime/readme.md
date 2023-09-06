## Memory Management in Csq
Memory in Csq is stored as a collection of small memory storing units called the Cells.
### Cells
The Cells are responsible for dynamic typing in Csq since they allocate memory for storing values of different types like Float, String and Arrays.
<br>
They are defined as a struct whose members are :
<br>
Source : memory.h
```
Type type;
int u_count;
int ival;
double fval;
string sval;
vector<Cell> array;
```

## How memory is used for a program
Example code:
```
a := 949
a = 'Hi'
print a
```
In This example there is a variable a who is allocating 2 different values in entire program so
```
For a := 949

address            value
0          :       [949]

In Symbol table
a's address = 0

For a = 'Hi'
address            value
0          :       [949]
1          :       ['Hi']

As its assignment of variable so the old value in the memory will be removed and the new address for a is again 0

address            value
0          :       ['Hi']

For print a
id('a')

Where this id function in C/C++ is going to return a value by searching for variable's value address and returning the value found.
If not found so you will get a Seg fault since we are trying to find a value at address which doesn't exist.
```
