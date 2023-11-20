from Compiler.Tokenizer.tokenizer import TokenType,to_str
from Compiler.Compiletime.stack import Compiletime_Objects, pushVariable, in_Compiletime_Objects, Variable
from Compiler.Compiletime import stack

def is_var_decl(tokens) -> bool:
    if (
        len(tokens) >= 2
        and tokens[0].type == TokenType.IDENTIFIER
        and tokens[1].token == ":="
    ):
        return True
    return False


def is_print_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].type == TokenType.KEYWORD:
        return True
    return False


def is_type_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == TokenType.type:
        return True
    return False


def is_var_assign(tokens) -> bool:
    if (
        len(tokens) >= 2
        and tokens[0].type == TokenType.IDENTIFIER
        and tokens[1].token == "="
    ):
        return True
    elif(
            len(tokens) >= 2 and tokens[0].type == TokenType.IDENTIFIER
            and tokens[1].type == TokenType.IDENTIFIER
            and "=" in to_str(tokens)
        ):
        return True

    return False


def is_if_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "if":
        return True
    return False


def is_elif_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "elif":
        return True
    return False


def is_else_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "else":
        return True
    return False


def is_for_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "for":
        return True
    return False


def is_return_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "return":
        return True
    return False

def is_break_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "break":
        return True
    return False

def is_while_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "while":
        return True
    return False


def is_access_stmt(tokens) -> bool:
    is_access = False
    if len(tokens) >= 1 and tokens[0].type == TokenType.IDENTIFIER:
        for token in tokens:
            if token.token == "[" or token.token == "]":
                is_access = True
                break
    return is_access


def is_access_update(tokens) -> bool:
    if (
        len(tokens) >= 5
        and tokens[0].type == TokenType.IDENTIFIER
        and tokens[1].token == "["
        and tokens[4].token == "="
    ):
        return True
    else:
        return False


def is_function(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "def":
        return True
    else:
        return False


def is_import_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "import":
        return True
    else:
        return False

def is_cimport_stmt(tokens) -> bool:
    if len(tokens) >= 1 and tokens[0].token == "cimport":
        return True
    else:
        return False

def is_class(tokens) -> bool:
    if tokens[0].token == "class":
        return True
    else:
        return False

def is_MemberVarAssign(tokens) -> bool:
    if  (   tokens[0].type == TokenType.IDENTIFIER
            and tokens[1].type == TokenType.IDENTIFIER
            and "=" in to_str(tokens)
        ):
        return True
    return False