"""
Parser for Csq

This module contains the parser for the Csq programming language. It defines functions for parsing various language constructs and generating the corresponding abstract syntax tree (AST).
"""

from Compiler.AST.ast import *
from Compiler.Compiletime.error import (Error, IndentationError, NameError, SyntaxError,
                               TypeError)
from Compiler.Compiletime.syntax_check import *
from Compiler.Tokenizer.tokenizer import Token, TokenType, to_str, tokenize

'''
This variable will hold the current path of the file to be parsed.
'''
_curr_path = ''
'''
This list will be holding all the errors tracked during parsing
'''
error_list = []

class Scope:
    def __init__(self, level: int, of_: NodeTypes, ended: bool) -> None:
        """
        Initialize a scope for tracking the indentation level and type of a block.

        Args:
            level (int): The indentation level of the block.
            of_ (NodeTypes): The type of node this scope belongs to.
            ended (bool): Flag indicating if the block has ended.

        Returns:
            None
        """
        self.indent_level = level
        self.of = of_
        self.ended = ended


def get_indent_level(tokens) -> int:
    """
    Get the indentation level of a line based on the number of indent tokens.

    Args:
        tokens (list): A list of tokens representing a line.

    Returns:
        int: The indentation level.
    """
    indent_ = 0
    for token in tokens:
        if token.type == TokenType.INDENT:
            indent_ += 1
        else:
            break
    return indent_


def remove_indent(tokens) -> list:
    """
    Remove leading indentation tokens from a list of tokens.

    Args:
        tokens (list): A list of tokens.

    Returns:
        list: A new list of tokens with leading indentation tokens removed.
    """
    tok = []
    for token in tokens:
        if token.type == TokenType.INDENT:
            pass
        else:
            tok.append(token)
    return tok


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

def statement_type(tokens) -> NodeTypes:
    if is_var_decl(tokens):
        return NodeTypes.VAR_DECL
    elif is_var_assign(tokens):
        return NodeTypes.VAR_ASSIGN
    elif is_if_stmt(tokens):
        return NodeTypes.IF_STMT
    elif is_elif_stmt(tokens):
        return NodeTypes.ELIF_STMT
    elif is_else_stmt(tokens):
        return NodeTypes.ELSE_STMT
    elif is_for_stmt(tokens):
        return NodeTypes.FOR_STMT
    elif is_while_stmt(tokens):
        return NodeTypes.WHILE_STMT
    elif is_access_update(tokens):
        return NodeTypes.COLLECTION_UPDATE
    elif is_function(tokens):
        return NodeTypes.FUN_DECL
    elif is_return_stmt(tokens):
        return NodeTypes.RETURN
    elif is_break_stmt(tokens):
        return NodeTypes.BREAK
    elif is_import_stmt(tokens):
        return NodeTypes.IMPORT
    elif is_cimport_stmt(tokens):
        return NodeTypes.CIMPORT
    elif is_class(tokens):
        return NodeTypes.CLASS
    elif is_print_stmt(tokens):
        return NodeTypes.PRINT
    else:
        return NodeTypes.EXPR

"""
Parsing units
"""


def parse_ExprNode(tokens) -> ExprNode:
    """
    Parse an expression node from a list of tokens.

    Args:
        tokens (list): A list of tokens representing an expression.

    Returns:
        ExprNode: The parsed expression node.
    """
    node = ExprNode()
    i = 0

    while i < len(tokens):
        current_token = tokens[i]

        if current_token.type == TokenType.IDENTIFIER:
            if i + 1 < len(tokens) and tokens[i + 1].token == "(":
                node.tokens.append(Token(current_token.token + "(", TokenType.BLANK))
                i += 1
            elif i + 1 < len(tokens) and tokens[i + 1].token == ".":
                if i + 3 < len(tokens) and tokens[i+3].token == "(":
                    node.tokens.append(Token(f'methodId("{current_token.token}","{tokens[i+2].token}")', TokenType.BLANK))
                    i += 2
                else:
                    node.tokens.append(Token(f'memberId("{current_token.token}","{tokens[i+2].token}")', TokenType.BLANK))
                    i += 2
            else:
                node.tokens.append(
                    Token(f'id("{current_token.token}")', TokenType.BLANK)
                )

        elif current_token.type == TokenType.STR:
            node.tokens.append(Token(f"Cell({current_token.token})", TokenType.BLANK))

        elif current_token.type == TokenType.VALUE:
            if i + 2 < len(tokens) and tokens[i + 1].token == ".":
                node.tokens.append(
                    Token(
                        f"Cell(float({current_token.token}.{tokens[i + 2].token}))",
                        TokenType.BLANK,
                    )
                )
                i += 2
            else:
                node.tokens.append(
                    Token(f"Cell({current_token.token})", TokenType.BLANK)
                )

        else:
            node.tokens.append(current_token)

        i += 1

    return node


def parse_VarDecl(tokens) -> VarDeclNode:
    node = VarDeclNode()
    node.identifier = tokens[0].token
    node.value.tokens = tokens[2:]
    node.value = parse_ExprNode(node.value.tokens)
    return node

def parse_MemberVarDecl(tokens) -> MemberVarDeclNode:
    node = MemberVarDeclNode()
    node.identifier = tokens[0].token
    node.value.tokens = tokens[2:]
    node.value = parse_ExprNode(node.value.tokens)
    return node


def parse_VarAssign(tokens) -> VarAssignNode:
    node = VarAssignNode()
    node.identifier = tokens[0].token
    node.value.tokens = tokens[2:]
    node.value = parse_ExprNode(node.value.tokens)
    return node

def parse_MemberVarAssign(tokens) -> MemberVarAssignNode:
    node = MemberVarAssignNode()
    id_bef_dot = ''
    pos = 0
    for token in tokens:
        if token.token != "=":
            if token.token == ".":
                node.identifier.append(id_bef_dot)
            else:
                id_bef_dot += token.token
        else:
            node.identifier.append(id_bef_dot)
        pos += 1
    node.value = tokens[pos:]
    return node    

def parse_PrintStmt(tokens) -> PrintNode:
    node = PrintNode()
    node.value.tokens = tokens[1:]
    node.value = parse_ExprNode(node.value.tokens)
    return node


def parse_IfStmt(tokens) -> IfStmtNode:
    tokens.pop(len(tokens) - 1)

    node = IfStmtNode()
    node.condition.tokens = tokens[1 : len(tokens)]
    node.condition = parse_ExprNode(node.condition.tokens)
    return node


def parse_ElifStmt(tokens) -> ElifStmtNode:
    tokens.pop(len(tokens) - 1)

    node = ElifStmtNode()
    node.condition.tokens = tokens[1:]
    node.condition = parse_ExprNode(node.condition.tokens)
    return node


def parse_ElseStmt():
    node = ElseStmtNode()
    return node


def parse_WhileStmt(tokens) -> WhileStmtNode:
    tokens.pop(len(tokens) - 1)

    node = WhileStmtNode()
    node.condition = parse_ExprNode(tokens[1:])
    return node

def parse_Class(tokens) -> ClassNode:
    tokens.pop(len(tokens) - 1)

    '''
    class <identifier>
    '''
    node = ClassNode()
    node.name = tokens[1].token
    return node


def parse_FunDecl(tokens) -> FunDeclNode:
    # Remove unnecessary tokens
    tokens.pop()  # Remove the last token (")")
    tokens.pop()  # Remove the second-to-last token ("name")

    node = FunDeclNode()
    node.identifier = tokens[1].token

    # Extract parameters
    tokens = tokens[2:]  # Skip the function name and "("
    param = ""

    if len(tokens) == 0:
        pass
    else:
        
        tokens.append(Token(',',TokenType.SYMBOL))
        param_ = False
        param = ''
        
        for token in tokens[1:]:
            if param_ == False and token.token != ',':
                param_ = True
                param += token.token
            elif param_ and token.token == ',':
                param_ = False
                node.parameters.append(param)
                param = ''
    return node

def parse_ReturnStmt(tokens):
    node = ReturnNode()
    node.value = parse_ExprNode(tokens)
    return node

def parse_ForStmt(tokens):
    tokens.pop(len(tokens) - 1)

    node = ForStmtNode()
    node.iter_name = tokens[1].token
    node.condition = parse_ExprNode(tokens[3:])

    return node

def parse_Methods(tokens):
    tokens.pop(len(tokens) - 1)

    '''
    Syntax:
        def <name>:
    '''
    node = MethodNode()
    node.identifier = tokens[1].token
    
    return node


'''
Function to parse import statements
'''
def parse_ImportStmt(tokens) -> ImportNode:
    node = ImportNode()
    for tok in tokens[1:]:
        node.path += tok.token
    return node

def parse_CImportStmt(tokens) -> CImportNode:
    node = CImportNode()
    for tok in tokens[1:]:
        node.path += tok.token
    return node

def Compile(code: list) -> str:
    """
    Compile Csq code into C/C++ code.

    Args:
        code (list): A list of code lines as lists of tokens.

    Returns:
        str: The compiled C/C++ code as a string.
    """
    # adding an additional line to make sure indents work properly.
    code.append([Token("0", TokenType.VALUE)])
    # Resulting code
    code_string = ""
    _class = False
    active_class = ''
    # Scope properties
    line_no = 1
    scope_stack = [Scope(0, NodeTypes.UNKNOWN_NODE, 0)]

    for line in code:
        # Get the current scope by finding indents
        indent_level = get_indent_level(line)

        while indent_level != scope_stack[-1].indent_level:
            if scope_stack[-1].of == NodeTypes.FUN_DECL or  scope_stack[-1].of == NodeTypes.CLASS:
                if scope_stack[-1].of == NodeTypes.CLASS:
                    _class = False
                    active_class = ''
                    scope_stack.pop()    
                else:
                    code_string += "};\n"
                    scope_stack.pop()
            else:
                code_string += "}\n"
                # Pop the previous scope since it's now closed.
                scope_stack.pop()

        # Removing all indentation from the stream
        line = remove_indent(line)

        match statement_type(line):
            case NodeTypes.VAR_DECL:
                if not _class or (_class == True and scope_stack[-1].of == NodeTypes.FUN_DECL):
                    if check_VarDecl(line):
                        node = parse_VarDecl(line)
                        code_string += node.visit() + "\n"
                    else :
                        error_list.append(SyntaxError(line_no, "invalid variable decl " + to_str(line)))
                        node = parse_VarDecl(line)
                        code_string += node.visit() + "\n"
                else:

                    if check_VarDecl(line):
                        node = parse_MemberVarDecl(line)
                        node._class_ = active_class
                        code_string += node.visit() + "\n"
                    else:
                        error_list.append(SyntaxError(line_no, "invalid variable decl " + to_str(line)))
                    
            case NodeTypes.VAR_ASSIGN:
                if check_VarAssign(line):
                    if is_MemberVarAssign(line):
                        node = parse_MemberVarAssign(line)
                        code_string += node.visit() + "\n"
                    else:
                        node = parse_VarAssign(line)
                        code_string += node.visit() + "\n"
                else:
                    error_list.append(
                        SyntaxError(
                            line_no, "invalid variable assignment " + to_str(line)
                        )
                    )
                    node = parse_VarAssign(line)
                    code_string += node.visit() + "\n"

            case NodeTypes.IF_STMT:
                if check_IfStmt(line)[0] != False:
                    node = parse_IfStmt(line)
                    code_string += node.visit() + "\n"
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.IF_STMT, 0))
                else:
                    error_list.append(
                        SyntaxError(
                            line_no, check_IfStmt(line)[1]
                        )
                    )
                    node = parse_IfStmt(line)
                    code_string += node.visit() + "\n"
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.IF_STMT, 0))
                    

            case NodeTypes.ELIF_STMT:
                if check_ElifStmt(line)[0] != False:
                    node = parse_ElifStmt(line)
                    code_string += node.visit() + "\n"
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.ELIF_STMT, 0))
                else:
                    error_list.append(
                        SyntaxError(
                            line_no, check_ElifStmt(line)[1]
                        )
                    )
                    node = parse_ElifStmt(line)
                    code_string += node.visit() + "\n"
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.ELIF_STMT, 0))

            case NodeTypes.ELSE_STMT:
                if check_ElseStmt(line)[0] != False:
                    node = parse_ElseStmt()
                    code_string += node.visit() + "\n"
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.ELSE_STMT, 0))
                else:
                    error_list.append(
                        SyntaxError(
                            line_no, check_ElseStmt(line)[1]
                        )
                    )
                    node = parse_ElseStmt()
                    code_string += node.visit() + "\n"
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.ELSE_STMT, 0))
                    

            case NodeTypes.WHILE_STMT:
                node = parse_WhileStmt(line)
                code_string += node.visit() + "\n"
                scope_stack.append(Scope(indent_level + 1, NodeTypes.WHILE_STMT, 0))

            case NodeTypes.FOR_STMT:
                node = parse_ForStmt(line)
                code_string += node.visit() + "\n"
                scope_stack.append(Scope(indent_level + 1, NodeTypes.FOR_STMT, 0))

            case NodeTypes.CLASS:
                if check_ClassStmt(line)[0]:
                    node = parse_Class(line)
                    code_string += node.visit() + "\n"
                    _class = True
                    active_class = node.name
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.CLASS, 0))
                else:
                    error_list.append(
                        SyntaxError(
                            line_no,
                            check_ClassStmt(line)[1]
                        )
                    )
                    code_string += "\n"
                    _class = True
                    active_class = ""
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.CLASS, 0))

            case NodeTypes.BREAK:
                #Didn't use any parsing function since there is no need of it in case of break statement
                node = BreakNode()
                code_string += node.visit() + "\n"
            case NodeTypes.FUN_DECL:
                if _class:
                    node = parse_Methods(line)
                    node.classname = active_class
                    code_string += node.visit()
                    scope_stack.append(Scope(indent_level + 1, NodeTypes.FUN_DECL, 0))

                else:
                    if check_FuncDecl(line)[0]:
                        node = parse_FunDecl(line)
                        code_string += node.visit() + "\n"
                        scope_stack.append(Scope(indent_level + 1, NodeTypes.FUN_DECL, 0))
                    else:
                        error_list.append(
                            SyntaxError(
                                line_no,
                                check_FuncDecl(line)[1]
                            )
                        )
                        node = parse_FunDecl(line)
                        code_string += node.visit() + "\n"
                        scope_stack.append(Scope(indent_level + 1, NodeTypes.FUN_DECL, 0))
                        

            case NodeTypes.IMPORT:
                if check_ImportStmt(line)[0]:
                    node = parse_ImportStmt(line)
                    code_string += visit_ImportNode(node) + "\n"
                else:
                    error_list.append(
                        SyntaxError(
                            line_no,
                            check_ImportStmt(line)[1]
                        )
                    )
                    
            case NodeTypes.CIMPORT:
                if check_CImportStmt(line)[0]:
                    node = parse_CImportStmt(line)
                    code_string += "\n//" + node.path + "\n" + visit_CImportNode(node) + "\n"
                else:
                    error_list.append(
                        SyntaxError(
                            line_no,
                            check_CImportStmt(line)[1]
                        )
                    )
            case NodeTypes.PRINT:
                if check_PrintStmt(line):
                    node = parse_PrintStmt(line)
                    code_string += node.visit() + "\n"
                else:
                    error_list.append(
                        SyntaxError(
                            line_no,
                            "invalid syntax for print statement\n(keywords and assignment operators arent allowed)",
                        )
                    )
            case NodeTypes.RETURN:
                node = parse_ReturnStmt(line[1:])
                code_string += node.visit() + '\n'
            case _:
                # The procedure to parse an expression is different if it's a return statement.
                if is_return_stmt(line):
                    pass
                else:
                    if check_Expr(line)[0]:
                        # Syntax is valid
                        node = parse_ExprNode(line)
                        if node.visit() == 'id("ignore")' or node.visit() == 'Cell(0)' :
                            pass
                        else:
                            code_string += node.visit() + ";\n"
                    else:
                        # Syntax is voilated
                        error_list.append(
                            SyntaxError(
                                line_no,
                                check_Expr(line)[1]
                            )
                        )
        line_no += 1
    '''
    Even if a single error is there in a code whole converted C++ code will be deformed.
    '''
    if len(error_list) > 0:
        code_string = ''
        for error in error_list:
            print(error)
        exit()


    return code_string


'''
Function to import code on the basis of given ImportNode
'''
def visit_ImportNode(node):
    module = open(_curr_path + node.path + ".csq", "r")
    # Read the file and process it
    code_ = module.read()
    # Convert it into stream of tokens
    lines = []
    for line in code_.split("\n"):
        if line != "":
            lines.append(tokenize(line))

    # Moving forth to compilation
    compiled_code = Compile(lines)
    return compiled_code
'''
Function to import C/C++ code on the basis of given CImportNode
'''
def visit_CImportNode(node):
    module = open( node.path + ".cpp", "r")
    # Read the file and process it
    code_ = module.read()
    return code_
