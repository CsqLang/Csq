"""
Module: Syntax Checking Functions

These functions are responsible for checking the syntax of various statements and expressions
in the Csq language. They check for violations of grammar rules and return whether the syntax is
valid or not which will futher be used by parser where it will decide whether to give runtime error or not.
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

def check_Expr(tokens):
    """
    Check whether the given expr is a valid expr or not.

    Args:
        tokens (list): A stream of tokens representing the statement.

    Returns:
        bool: True if the syntax is valid, False otherwise.

    Rule to check:
    * An expression should not contain any keyword(for now).
    * An expression should not contain any unclosed bracket.
    """
    valid = True
    reason = ''

    def has_unclosed_brackets(_tokens):
        stack = []

        # Define mappings for opening and closing brackets
        bracket_map = {
            '(': ')',
            '[': ']',
            '{': '}',
        }

        for token in _tokens:
            if token.token in bracket_map.keys():  # Use token.token as the key
                # If it's an opening bracket, push it onto the stack
                stack.append(token)
            elif token.token in bracket_map.values():
                # If it's a closing bracket, check if it matches the top of the stack
                if not stack or bracket_map[stack.pop().token] != token.token:  # Use token.token as the key
                    return True  # Mismatch means unclosed bracket

        # If the stack is not empty, there are unclosed opening brackets
        return len(stack) > 0

    if has_unclosed_brackets(tokens):
        valid = False
        reason = 'Contains unclosed bracket'
        return [valid,reason]

    if valid:
        for token in tokens:
            if token.type == TokenType.KEYWORD:
                reason = 'An expression must not contain a keyword which is in this case "' + token.token + '"'
                return [valid,reason]
        
    return [True,""]    
