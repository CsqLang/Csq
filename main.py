import sys

from Parser.parser import Compile
from Runtime.code_format import readCode, toTokens, writeCode

arguments = sys.argv
filename = str()
filepath = str()
if len(arguments) == 3:
    filename = arguments[1]
    filepath = arguments[2]
else:
    print("Argv[Filename.csq filefolder]")
    exit()

code = readCode(filepath + "/" + filename)


Token_code = toTokens(code=code)

for token_line in Token_code:  # This code for testing Token
    for token in token_line:
        print(token)

# compile_code = Compile(Token_code)
