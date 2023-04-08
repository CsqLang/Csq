
<h1> Csq 4.2</h1>
Hey there,
This the updated version of 4.2 which is having more concise syntax than the 4.1 and better compiler handling provided by AST.


### Sample code 




### Variables
In Csq4.2 a variable's data is allocated on stack by default but to store it's data into heap we could use builtin types to do so.
Syntax:
```
<name> = <value>
```
Example:
```
a = i32(49)
b = a
```
### Functions
The syntax for function is inspired by Python here the scope is resolved by indentations.
```
def fx(a, b):
 return a + b
x = fx(23,34)
```
If you just want to create a function without any code so to prevent error use ignore keyword.
```
def fx():
 ignore
fx()
```
### Rules of coding in Csq4.2
If you are not using more then one functions so you could write them like this directly:
```
def hi():
 print("Hi")
a = 30
if a == 30:
 print('30')
```
But when there are more functions so you have to write your main code into another function and call it at the end like this : 
```
def linear(x):
 return x
def ReLU(x):
 if x > 0:
  return x
 else:
  return 0
def start():
 x = 39
 fx = linear(x)
 fx = reLu(x)
start()
```
Here start is the entry point function you can use any other function also.
