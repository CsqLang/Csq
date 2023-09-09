from AST.ast import NodeTypes
from Tokenizer.tokenizer import TokenType
class Scope():
    
    def __init__(self,level:int,of_:NodeTypes,ended:bool) -> None:
        self.indent_level = level
        self.of = of_
        self.ended = ended 
        
def get_indent_level(tokens) -> int:
    indent_ = 0
    for token in tokens:
        if token.type == TokenType.INDENT:
            indent_ +=1
        else:
            break
    return indent_

def remove_indent(tokens):
    tok = []
    for token in tokens:
        if token.type == TokenType.INDENT:
            pass
        else:
            tok.append(token)
    return tok
def is_var_decl(tokens):
    if len(tokens) >= 2 and tokens[0].type == TokenType.IDENTIFIER and tokens[1].token == ":=":
        return True
    return False

def is_print_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == TokenType.print:
        return True
    return False

def is_type_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == TokenType.type:
        return True
    return False

def is_var_assign(tokens):
    if len(tokens) >= 2 and tokens[0].type == TokenType.IDENTIFIER and tokens[1].token == "=":
        return True
    return False

def is_if_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "if":
        return True
    return False

def is_elif_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "elif":
        return True
    return False

def is_else_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "else":
        return True
    return False

def is_return_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "return":
        return True
    return False

def is_while_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "while":
        return True
    return False

def is_access_stmt(tokens):
    is_access = False
    if len(tokens) >= 1 and tokens[0].type == TokenType.IDENTIFIER:
        for token in tokens:
            if token.token == "[" or token.token == "]":
                is_access = True
                break
    return is_access

def is_access_update(tokens):
    if len(tokens) >= 5 and tokens[0].type == TokenType.IDENTIFIER and tokens[1].token == "[" and tokens[4].token == "=":
        return True
    else:
        return False

def is_function(tokens):
    if len(tokens) >= 1 and tokens[0].token == "def":
        return True
    else:
        return False

def is_import_stmt(tokens):
    if len(tokens) >= 1 and tokens[0].token == "import":
        return True
    else:
        return False


def statement_type(tokens):
    if is_var_decl(tokens):
        return NodeTypes.VAR_DECL
    elif is_var_assign(tokens):
        return NodeTypes.VAR_ASSIGN
    elif is_if_stmt(tokens):
        return NodeTypes.IF_STMT
    elif is_print_stmt(tokens):
        return NodeTypes.PRINT
    elif is_elif_stmt(tokens):
        return NodeTypes.ELIF_STMT
    elif is_else_stmt(tokens):
        return NodeTypes.ELSE_STMT
    elif is_while_stmt(tokens):
        return NodeTypes.WHILE_STMT
    elif is_access_update(tokens):
        return NodeTypes.COLLECTION_UPDATE
    elif is_function(tokens):
        return NodeTypes.FUN_DECL
    elif is_return_stmt(tokens):
        return NodeTypes.RETURN
    elif is_import_stmt(tokens):
        return NodeTypes.IMPORT
    else:
        return NodeTypes.EXPR



def Compile(code:list) -> str:

    # Resulting code
    code_string = ""

    # Scope properties
    line_no = 1
    scope = Scope(0, NodeTypes.UNKNOWN_NODE, 0)
    scope_stack = [scope]

    # States
    class_ = False
    last_indent = 0
    # Last statement type
    last_statement = NodeTypes.UNKNOWN_NODE

    for line in code:
        # Get the current scope by finding indents
        indent_level = get_indent_level(line)

        # Work with the indentation levels
        while indent_level != scope_stack[-1].indent_level:
            if scope_stack[-1].of == NodeTypes.FUN_DECL:
                code_string += "};\n"
                scope_stack.pop()

            else:
                code_string += "}\n"
                # Pop the previous scope since it's now closed.
                scope_stack.pop()

        # Removing all indentation from the stream
        line = remove_indent(line)

    