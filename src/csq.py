#!/usr/bin/env python3
"""

This file does compile code and produces machine code.

"""

import os
import sys

from Compiler.code_format import readCode, toTokens, writeCode
from Compiler.Compiletime.wrapper import bind
# from Tokenizer.tokenizer import *
from Compiler.Parser.parser import Compile

"""

Format for how this file should recieve args
python3.10 csq.py <path of file>

"""

# Check more than one argument is passed

if len(sys.argv) < 2:
    print("Format: csq <path of file>")
    exit(1)

# Path of file
path = sys.argv[1]

# Compiler
compiler = "g++ "

# csq include path path
csq_include_path = "/opt/csq/src"

# Read the file and process it
raw_code = readCode(path=path)

# Convert it into stream of tokens
lines = toTokens(raw_code)

# Moving forth to compilation
compiled_code = Compile(lines)

final_code = bind(csq_include_path, compiled_code)
name = path.replace(".csq", "")
writeCode(final_code, name + ".cpp")

os.system(compiler + name + ".cpp -o " + name)
