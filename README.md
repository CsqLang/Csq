# Csq4
![Csq4 (1)](https://user-images.githubusercontent.com/90708238/212843929-05cc3e4c-0b83-45be-8493-a423308c6fbc.png)
<br>
Hello there👋,
This is the new and safe version of Csq which is in developed to solve memory related problems in Csq3 such as memory leak.
But built-in facilities are still in development.
## Features
<li>Object Oriented Programming </li>
<li>Functional Programming features</li>
<li>Reference Counting for memory safety</li>
<li>Easy syntax</li>
<li>Fast speed during executions</li>

## Requirements
<li>G++</li>

## The Principles of Csq code
<li>Every Csq code shall ends with an extention .csq</li>
<li>Every variable is an object of SmartPointer class which inherits the datatype of that variable</li>
<li>All operators overloaded are the methods starting from op_ example: def op_div()</li>

## Examples/Syntax
```
# This is a comment
# Variable declarations
a:i32 = 1000
a2:f64 = 3.141592
a3:str = "Hello World"
a4:list<i32> = {3,4,6,28,9}
# Loops
for i:i32 in a4
    ...
ends
while <condition>
    ...
ends
# Decision making statements
if <condition>
    ...
ends
elif <condition>
    ...
ends
else
    ...
ends
# Functions
def myfun(i:i32)
    ...
myfun ends
#Calling a function
myfun(i32(34))

#Classes
class myclass
    ...
endc
#Inheritence 
class child inherits base
    ...
endc
```

## Syntax inspirations
<li>Python</li>
<li>Ruby</li>
<li>Nim</li>

