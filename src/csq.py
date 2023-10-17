#!/usr/bin/env python3.10
"""

This file does compile code and produces machine code.

"""

import os
import sys

from Compiler.Compiletime.wrapper import bind
# from Tokenizer.tokenizer import *
from Compiler.Parser.parser import Compile
from Compiler.code_format import readCode, toTokens, writeCode

"""

Format for how this file should recieve args
python3.10 csq.py <path of file>

"""

if len(sys.argv) < 2:
    print("No file provided")
    exit(1)

# Path of file
path = sys.argv[1]

# csq include path path
csq_include_path = os.getenv("CSQ_INCLUDE")

# Read the file and process it
raw_code = readCode(path=path)

# Convert it into stream of tokens
lines = toTokens(raw_code)

# Moving forth to compilation
compiled_code = Compile(lines)

final_code = bind(csq_include_path, compiled_code)
name = path.replace(".csq", "")
writeCode(final_code, name + ".cpp")

os.system("g++ " + name + ".cpp -o " + name)
