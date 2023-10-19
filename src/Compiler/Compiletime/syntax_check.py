"""
Module: Syntax Checking Functions

These functions are responsible for checking the syntax of various statements and expressions
in the Csq language. They check for violations of grammar rules and return whether the syntax is
valid or not which will futher be used by parser where it will decide whether to give runtime error or not.
"""


from Compiler.Tokenizer.tokenizer import TokenType


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
            if token.token in bracket_map:
                stack.append(token.token)
            elif token.token in bracket_map.values() and (not stack or bracket_map[stack.pop()] != token.token):
                return True

        # If the stack is not empty, there are unclosed opening brackets
        return bool(stack)

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
 
def check_ImportStmt(tokens):
    '''
    this function will be checking the impl of the
    syntax of import statement.
    '''
    valid = True
    reason = ''
    for token in tokens:
        if token.type == TokenType.KEYWORD and token.token != "import":
            valid = 0
            reason = f"Use of keyword '{token.token}' as path to the module."
            break
    return [valid, reason]

def check_CImportStmt(tokens):
    '''
    this function will be checking the impl of the
    syntax of cimport statement.
    '''
    valid = True
    reason = ''
    for token in tokens:
        if token.type == TokenType.KEYWORD and token.token != "cimport":
            valid = 0
            reason = f"Use of keyword '{token.token}' as path to the module."
            break
    return [valid, reason]


def check_FuncDecl(tokens):
    '''
    This function will be checking the impl of the
    syntax of function decl
    '''
    valid = True
    reason = ''
    for token in tokens:
        if token.type == TokenType.KEYWORD and token.token != "def":
            valid = False
            reason = f"Use of keyword '{token.token}' in function decl."
            break
    return [valid, reason]

def check_IfStmt(tokens):
    '''
    This function will be checking the impl of the syntax of if stmt
    '''
    valid = True
    reason = ''
    if tokens[len(tokens)-1].token != ":":
        valid = False
        reason = 'Missing colon at the end in the used if stmt.'
    return [valid, reason]

def check_ElifStmt(tokens):
    '''
    This function will be checking the impl of the syntax of elif stmt
    '''
    valid = True
    reason = ''
    if tokens[len(tokens)-1].token != ":":
        valid = False
        reason = 'Missing colon at the end in the used elif stmt.'
    return [valid, reason]

def check_ElseStmt(tokens):
    '''
    This function will be checking the impl of the syntax of else stmt
    '''
    valid = True
    reason = ''
    if tokens[len(tokens)-1].token != ":":
        valid = False
        reason = 'Missing colon at the end in the used else stmt.'
    return [valid, reason]

def check_ClassStmt(tokens):
    '''
    This function will be checking the impl of the syntax of class
    '''
    valid = True
    reason = ''
    if tokens[len(tokens)-1].token != ":":
        valid = False
        reason = 'Missing colon at the end in the used class stmt.'
        
    if tokens[1].type != TokenType.IDENTIFIER:
        valid = False
        reason = 'Expected an identifier after class keyword.'
    return [valid, reason]
