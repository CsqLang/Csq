"""
Module: Syntax Checking Functions

These functions are responsible for checking the syntax of various statements and expressions
in the Csq language. They check for violations of grammar rules and return whether the syntax is
valid or not.
"""


from Tokenizer.tokenizer import TokenType

def check_VarDecl(tokens):
    """
    Check the syntax of a variable declaration statement.

    Args:
        tokens (list): A list of tokens representing the statement.

    Returns:
        bool: True if the syntax is valid, False otherwise.
    """
    valid = False
    if tokens[0].type == TokenType.IDENTIFIER:
        valid = True

        if tokens[1].token == ":=":
            for i in tokens[1:]:
                if i.type == TokenType.KEYWORD:
                    valid = False
                    break
        else:
            valid = False
    return valid

def check_VarAssign(tokens):
    """
    Check the syntax of a variable assignment statement.

    Args:
        tokens (list): A list of tokens representing the statement.

    Returns:
        bool: True if the syntax is valid, False otherwise.
    """
    valid = False
    if tokens[0].type == TokenType.IDENTIFIER:
        valid = True

        if tokens[1].token == "=":
            for i in tokens[1:]:
                if i.type == TokenType.KEYWORD:
                    valid = False
                    break
        else:
            valid = False
    return valid

def check_PrintStmt(tokens):
    """
    Check the syntax of a print statement.

    Args:
        tokens (list): A list of tokens representing the statement.

    Returns:
        bool: True if the syntax is valid, False otherwise.
    """
    valid = True

    for i in tokens[1:]:
        if i.token == ":=" or i.token == "=":
            valid = False
        elif i.type == TokenType.KEYWORD:
            valid = False

    return valid
