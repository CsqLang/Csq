'''

This file does compile code and produces machine code.

'''

from Tokenizer.tokenizer import *
from Parser.parser import *
from Compiletime.wrapper import bind
from AST.ast import *
import sys
import os

'''
Some useful functions
'''
def read_file_in_directory(directory, filename):
    file_path = os.path.join(directory, filename)    
    if os.path.exists(file_path):
        with open(file_path, 'r') as file:
            file_contents = file.read()
        return file_contents
    else:
        return f"File '{filename}' not found in the directory '{directory}'."


'''

Format for how this file should recieve args
python3.10 csq.py <path of file>

'''
#Path of file
path = sys.argv[1]

#Current path
curr_dir = os.getcwd()

file = open(path, 'r')
#Read the file and process it
raw_code = file.read()

# Convert it into stream of tokens
lines = []
for line in raw_code.split('\n'):
    if line != '':
        lines.append(tokenize(line))

# Moving forth to compilation
compiled_code = Compile(lines)

final_code = bind(curr_dir, compiled_code)

name = ''
if '/' in path:
    name = path.split('/')[len(path.split('/'))-1]

fo = open(path.replace(name,'') + '/' + name.replace('.csq','.cpp'), 'w')
fo.write(final_code)
