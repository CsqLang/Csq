
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
a = i32{49}
a:i32 = 49
b = a
```
### Loops
#### While Loop
```
i = 1
while i <= 100:
 print(i)
 i = i+1
```
#### For Loop
```
for i in range(1,100):
 print(i)
```
### If, Elif and Else statements
```
i = 1
if i == 1:
 i = 5
 if i == 5:
  print(5)
 elif i == 3:
  print(3)
 else:
  print(0)
```
### Functions
```
def myfun():
 print('inside myfun')
```
