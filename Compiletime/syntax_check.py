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
    if tokens[0].type != TokenType.IDENTIFIER:
        return False

    if len(tokens) < 3 or tokens[1].token != ":=":
        return False

    for token in tokens[2:]:
        if token.type == TokenType.KEYWORD:
            return False

    return True


def check_VarAssign(tokens):
    """
    Check the syntax of a variable assignment statement.

    Args:
        tokens (list): A list of tokens representing the statement.

    Returns:
        bool: True if the syntax is valid, False otherwise.
    """
    if len(tokens) < 3:
        return False

    if tokens[0].type != TokenType.IDENTIFIER or tokens[1].token != "=":
        return False

    for token in tokens[2:]:
        if token.type == TokenType.KEYWORD:
            return False

    return True

def check_PrintStmt(tokens):
    """
    Check the syntax of a print statement.

    Args:
        tokens (list): A list of tokens representing the statement.

    Returns:
        bool: True if the syntax is valid, False otherwise.
    """
    for token in tokens[1:]:
        if token.token in (":=", "=") or token.type == TokenType.KEYWORD:
            return False

    return True

