#!/usr/bin/env python3
"""

This file does compile code and produces machine code.

"""

import os
import sys

from Compiletime.wrapper import bind
# from Tokenizer.tokenizer import *
from Parser.parser import Compile
from Runtime.code_format import readCode, toTokens, writeCode

"""

Format for how this file should recieve args
python3.10 csq.py <path of file>

"""
# Path of file
path = sys.argv[1]

# Current path
curr_dir = os.getcwd()

# Read the file and process it
raw_code = readCode(path=path)

# Convert it into stream of tokens
lines = toTokens(raw_code)

# Moving forth to compilation
compiled_code = Compile(lines)

final_code = bind(curr_dir, compiled_code)
name = path.replace(".csq", "")
writeCode(final_code, name + ".cpp")

os.system("g++ " + name + ".cpp -o " + name)