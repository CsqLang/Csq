# Csq4
![Csq4 (1)](https://user-images.githubusercontent.com/90708238/212843929-05cc3e4c-0b83-45be-8493-a423308c6fbc.png)
<br>
Hello there👋,
This is the new and safe version of Csq which is in developed to solve memory related problems in Csq3 such as memory leak.
## Features
<li>Object oriented programming</li>
<li>Functional programming</li>
<li>High level programming
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

### Keywords
| Keyword Name |
| ------------- |
| if            |
| elif          |
| else          |
| def           |
| for           |
| while         |
| ends          |
| endc          |
| macro         |
| import        |
| in            |
| init          |
| public        |
| private       |
| inherits      |
| protected     |
| class         |
| use           |
| all           |
| as            |
| module        |
| try           |
| catch         |
| from()        |

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
### Classes
Syntax
```
class <name>
    ...
endc
```
Example
```
class mytype
    public:
        # Constructor
        init mytype()
        mytype ends
endc

x:mytype = mytype()
```
### Inheritance
Syntax
```
class <child> inherits <base>
endc
```
Example
```
class Animal
    public:
        def eat()
            print("Eating🍔")
        eat ends
        def walk()
            print("Walking🐾")
        walk ends
endc
class Dog inherits public Animal
    public:
        def bark()
            print("Woof Woof🐕")
        bark ends
endc
mydog : Dog = Dog()
mydog->bark()
mydog->walk()
mydog->eat()
```
### Importing a module
Syntax
```
import <module>
```
Example
```
import testmodule
```
Creating alias of module
```
import test
module T as test
```
Using all members from a module
```
import test
use test::<member_name>
```
### Creating a module
To create a module we should write a flag 'main = false'
#### Example
```mod.csq```
```
main = false
def myfun()
    print(str("Hello World"))
myfun ends
```
Now compile the above file using csq executable.
<br>
```sample.csq```
```
import mod
use mod::myfun
myfun()
```

## How Csq Works?
<img src = "https://media.licdn.com/dms/image/C4D22AQGcGg2ir0YA3w/feedshare-shrink_800/0/1677575848649?e=1680739200&v=beta&t=94dQB4fFg_ICdEI2EP-L-AVnr49QxE0gx813xD-r34E"></img>


## Syntax inspirations
<li>Python</li>
<li>Ruby</li>
<li>Nim</li>

