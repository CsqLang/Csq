"""Read Write Tokens  Python implementation of Csq"""
from Tokenizer.tokenizer import *


def readCode(path: str) -> str:
    """
    Read Csq code from a file.

    Args:
        path (str): The path to the Csq code file.

    Returns:
        str: The content of the code file as a string.
    """
    with open(path) as codefile:
        code = codefile.read()
    
    return code



def toTokens(code: str) -> list:
    """
    Tokenize Csq code into a list of token streams.

    Args:
        code (str): The Csq code as a string.

    Returns:
        list: A list of token streams, where each stream is a list of tokens.
    """
    tokens = []

    for line in code.split("\n"):
        try:
            tokenStream = tokenize(line)
            tokens.append(tokenStream)
        except Exception as e:
            pass

    tokens.append(tokenize("ignore"))
    return tokens



def writeCode(code: str, path: str) -> None:
    """
    Write Csq code to a file.

    Args:
        code (str): The Csq code as a string.
        path (str): The path to the output file where the code will be written.

    Returns:
        None
    """
    with open(path, "w") as codefile:
        codefile.write(code)
