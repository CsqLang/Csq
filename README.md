
<h1> Csq 4.2</h1>
Hey there,
This the updated version of 4.2 which is having more concise syntax than the 4.1 and better compiler handling provided by AST.
<br>
For brief : <a href = "https://csqlang.github.io/">Csq official website</a>
<br>

## New Features
<li>Use of stack memory by default</li>
<li>Use of indentations for scope repr</li>
<li>Better error handling</li>
<li>Optional control of hardware</li>
<li>Removing GC</li>


### Sample code 


### Variables
In Csq4.2 a variable's data is allocated on stack by default but to store it's data into heap we could use builtin types to do so.
We could also use type annotation for explicit typing. But it will make you feel like dynamic typing since type annotation is only strictly recommended to use inside classes.
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
There is a functionality in Csq that the functions defined doesn't require any function overloading since it's param can be use for any type but return type should be same in all cases.
```
def myfun(a = {}):
 print(a)
```
