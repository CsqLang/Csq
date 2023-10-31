"""
Parser for Csq

This module contains the parser for the Csq programming language. It defines functions for parsing various language constructs and generating the corresponding abstract syntax tree (AST).
"""

from Compiler.AST.ast import *
from Compiler.Compiletime.error import (Error, IndentationError, NameError, SyntaxError,
                               TypeError)
from Compiler.Compiletime.syntax_check import *
from Compiler.Tokenizer.tokenizer import Token, TokenType, to_str, tokenize
from Compiler.Parser.parserChecker import *
from Compiler.Parser.parserTokenToNode import *
from Compiler.Parser.parserVisits import *
from Compiler.utils import error_list
import os


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
                elif scope_stack[-1].of == NodeTypes.FOR_STMT:
                    code_string += "}\n"
                    scope_stack.pop()
                else:
                    code_string += "};\n"
                    scope_stack.pop()
            else:
                if scope_stack[-1].of == NodeTypes.FOR_STMT:
                    code_string += "}\n"
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


