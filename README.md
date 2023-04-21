
<h1> Csq 4.2</h1>
Hey there,
This the updated version of 4.2 which is having more concise syntax than the 4.1 and better compiler handling provided by AST.

## New Features
<li>Use of stack memory by default</li>
<li>Use of indentations for scope repr</li>
<li>Better error handling</li>
<li>Optional control of hardware</li>
<li>Removing GC</li>


### Sample code 


### Variables
In Csq4.2 a variable's data is allocated on stack by default but to store it's data into heap we could use builtin types to do so.
We could also use type annotation for explicit typing.
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
#### If
```
if 1:
 print('Hi')
```
#### Elif
```
if 1:
 print('Hi')
elif 0:
 print("Bye")
```
#### Else
```
if 1:
 print('Hi')
else:
 print('Bye')
 ```
### Functions
```
def myfun():
 print('inside myfun')
```
### Classes
The classes in Csq are public and they currently doesn't allow functions inside them.
```
class mytype:
 data:i32 = 0
obj = mytype()
obj.data = 494
```
### Group statement
similar to classes but it doesn't need any object it can be used to store variables.
```
group mygroup:
 a:i32 = 495
 b:i32 = 49
print(mygroup.a)
```
