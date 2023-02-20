# Csq4
![Csq4 (1)](https://user-images.githubusercontent.com/90708238/212843929-05cc3e4c-0b83-45be-8493-a423308c6fbc.png)
<br>
Hello there👋,
This is the new and safe version of Csq which is in developed to solve memory related problems in Csq3 such as memory leak.
But built-in facilities are still in development.
## Features
<li>Object Oriented Programming</li>
<li>Functional Programming</li>
<li>Reference Counting for memory safety</li>
<li>Easy syntax</li>
<li>Fast speed during executions</li>
<li>Customizable syntax using macro keyword</li>
## Requirements
<li>G++</li>

## The Principles of Csq code
<li>Every Csq code shall ends with an extention .csq</li>
<li>All operators overloaded are the methods starting from op_ example: def op_div()</li>

## Examples/Syntax

### Comments
```
# This is a comment
```

### Variables
In Csq4 Variables are the pointers pointing to a block of memory.
Syntax:
```
a:<type> = <value>
```
Example
```
a:i32 = 3954
b:i32 = a
```
### if,elif and else
Syntax
```
if <condition>
    ...
ends
elif <condition>
    ...
ends
else
    ...
ends
```
Example
```
a:i32 = 30
b:i32 = 23
if a == b
    print("They are equal")
ends
elif a > b
    print("a>b")
ends
else
    print("Else")
ends
```
### Loops
In Csq4 there are 2 types of loop (for and while).
Syntax
```
for i:<type> in <iterator>
    ...
ends

while <condition>
    ...
ends
```
Example
```
a:list<i32> = {1,59,5,76}
for i:i32 in a
    print(i)
ends
```
```
i:i32 = 1
while i<=i32(5)
    print(i)
    i = i+i32(1)
ends
```
### Functions
Syntax
```
def <name>(<args>)
    ...
<name> ends
```
Example:
```
def myfun(i:i32)
    print(i)
myfun ends
myfun(i32(44))
```


## Syntax inspirations
<li>Python</li>
<li>Ruby</li>
<li>Nim</li>

