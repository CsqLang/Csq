'''
This source contains the information of the various elements used in the code like
* variables
* functions

-----Working-----
When a variable will be declared it's name and other compiletime properties will be pushed into
the dictionary so for futher parsing and checks it can be used.
'''
class Variable:
    '''
    Name:
    Type:(Not required for now)
    Number of times used(So that we can avoid unnecessary allocations)
    '''
    name = ''
    times_used = 0

    def __init__(self, name):
        self.name = name
        self.times_used = 1


hasCimport = False

'''
Dictionary going to be used

Note: the checking process will be ceased if hasCimport is true.
'''
Compiletime_Objects = dict({})

def pushVariable(name:str)->None:
    var:Variable = name
    Compiletime_Objects[name] = var

def in_Compiletime_Objects(name:str)->bool:
    if name != 'ignore':
        return name in Compiletime_Objects
    else:
        return True