'''
THis will be checking for syntax errors where grammar is voilated.
'''
from Tokenizer.tokenizer import TokenType
from Compiletime.error import TypeError, IndentationError, NameError, SyntaxError, Error

def check_VarDecl(tokens):
    '''
    Format:
    <identifier> := <Expr>
    '''
    valid = False
    if tokens[0].type == TokenType.IDENTIFIER:
        valid = True

        if tokens[1].token == ':=':
            for i in tokens[1:]:
                if i.type == TokenType.KEYWORD:
                    valid = False
                    break
        else:
            valid = False
    return valid

def check_VarAssign(tokens):
    '''
    Format:
    <identifier> = <Expr>
    '''
    valid = False
    if tokens[0].type == TokenType.IDENTIFIER:
        valid = True

        if tokens[1].token == '=':
            for i in tokens[1:]:
                if i.type == TokenType.KEYWORD:
                    valid = False
                    break
        else:
            valid = False
    return valid

def check_PrintStmt(tokens):
    '''
    Format:
    print <Expr>
    '''
    valid = True

    for i in tokens[1:]:
        if i.token == ":=" or i.token == "=":
            valid = False
        elif i.type == TokenType.KEYWORD:
            valid = False

    return valid
