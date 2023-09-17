"""Read Write Tokens  Python implementation of Csq"""
from Tokenizer.tokenizer import *


def readCode(path: str) -> str:
    """Read Csq Code File"""
    code = str()
    with open(path) as codefile:
        for line in codefile.readlines():
            if line == "":
                continue
            else:
                code += line

    return code


# Not need of split() in python
# def split(string:str) -> list:
#     tokens = list()

#     for line in string.split("\n"):
#         tokens.append(line)

#     return tokens


def toTokens(code: str) -> list:
    tokens = list()
    statements = code.split("\n")

    for line in statements:
        try:
            tokenStream = tokenize(line)
            tokens.append(tokenStream)
        except Exception as e:
            pass

    tokens.append(tokenize("ignore"))
    return tokens


def writeCode(code: str, path: str) -> None:
    with open(path, "w") as codefile:
        codefile.write(code)
