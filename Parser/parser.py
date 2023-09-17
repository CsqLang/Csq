"""
        
    Parser for Csq4.2

"""

from AST.ast import *
from Compiletime.error import (Error, IndentationError, NameError, SyntaxError,
                               TypeError)
from Compiletime.syntax_check import *
from Tokenizer.tokenizer import Token, TokenType, to_str


class Scope:
    def __init__(self, level: int, of_: NodeTypes, ended: bool) -> None:
        self.indent_level = level
        self.of = of_
        self.ended = ended


def get_indent_level(tokens) -> int:
    indent_ = 0
    for token in tokens:
        if token.type == TokenType.INDENT:
            indent_ += 1
        else:
            break
    return indent_


def remove_indent(tokens) -> list:
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
    elif is_import_stmt(tokens):
        return NodeTypes.IMPORT
    elif is_print_stmt(tokens):
        return NodeTypes.PRINT
    else:
        return NodeTypes.EXPR


"""
Parsing units
"""


def parse_ExprNode(tokens) -> ExprNode:
    node = ExprNode()
    i = 0
    while i < len(tokens):
        if tokens[i].type == TokenType.IDENTIFIER:
            if i + 1 < len(tokens):
                if tokens[i + 1].token == "(":
                    """
                    It's a function then
                    """

                    node.tokens.append(Token(tokens[i].token + "(", TokenType.BLANK))
                    i += 1
                else:
                    node.tokens.append(
                        Token('id("' + tokens[i].token + '")', TokenType.BLANK)
                    )
            else:
                node.tokens.append(
                    Token('id("' + tokens[i].token + '")', TokenType.BLANK)
                )

        elif tokens[i].type == TokenType.STR or tokens[i].type == TokenType.VALUE:
            if tokens[i].type == TokenType.STR:
                node.tokens.append(
                    Token("s_val(" + tokens[i].token + ")", TokenType.BLANK)
                )
            else:
                node.tokens.append(
                    Token("f_val(" + tokens[i].token + ")", TokenType.BLANK)
                )
        else:
            node.tokens.append(tokens[i])
        i += 1

    return node


def parse_VarDecl(tokens) -> VarDeclNode:
    node = VarDeclNode()
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


def parse_FunDecl(tokens) -> FunDeclNode:
    tokens.pop(len(tokens) - 1)
    tokens.pop(len(tokens) - 1)

    node = FunDeclNode()
    node.identifier = tokens[1].token
    # By removing name and (
    tokens = tokens[2:]
    if len(tokens) == 0:
        pass
    else:
        tokens.append(Token(",", TokenType.SYMBOL))
        param_ = False
        param = ""

        for token in tokens[1:]:
            if param_ == False and token.token != ",":
                param_ = True
                param += token.token
            elif param_ and token.token == ",":
                param_ = False
                node.parameters.append(param)
                param = ""
    return node

def parse_ForStmt(tokens):
    tokens.pop(len(tokens) - 1)

    node = ForStmtNode()
    node.iter_name = tokens[1].token
    node.condition = parse_ExprNode(tokens[3:])

    return node

def Compile(code: list) -> str:
    # adding an additional line to make sure indents work properly.
    code.append([Token("0", TokenType.VALUE)])
    # Resulting code
    code_string = ""

    # Scope properties
    line_no = 1
    scope_stack = [Scope(0, NodeTypes.UNKNOWN_NODE, 0)]

    # States
    class_ = False
    last_indent = 0
    # Last statement type
    last_statement = NodeTypes.UNKNOWN_NODE

    for line in code:
        # Get the current scope by finding indents
        indent_level = get_indent_level(line)

        # # Work with the indentation levels
        # # print(scope_stack[-1].indent_level, ' "', to_str(line), '"')
        # if len(scope_stack) != 1:
        #     # print(len(scope_stack))
        #     while indent_level != scope_stack[-1].indent_level:
        #         code_string += "}\n"
        #         scope_stack.pop()
        # scope_stack.append(Scope(indent_level+1,NodeTypes.UNKNOWN_NODE,2))
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

        match statement_type(line):
            case NodeTypes.VAR_DECL:
                if check_VarDecl(line):
                    node = parse_VarDecl(line)
                    code_string += node.visit() + "\n"
                else:
                    print(SyntaxError(line_no, "invalid variable decl " + to_str(line)))

            case NodeTypes.VAR_ASSIGN:
                if check_VarAssign(line):
                    node = parse_VarAssign(line)
                    code_string += node.visit() + "\n"
                else:
                    print(
                        SyntaxError(
                            line_no, "invalid variable assignment " + to_str(line)
                        )
                    )

            case NodeTypes.IF_STMT:
                node = parse_IfStmt(line)
                code_string += node.visit() + "\n"
                scope_stack.append(Scope(indent_level + 1, NodeTypes.IF_STMT, 0))

            case NodeTypes.ELIF_STMT:
                node = parse_ElifStmt(line)
                code_string += node.visit() + "\n"
                scope_stack.append(Scope(indent_level + 1, NodeTypes.ELIF_STMT, 0))

            case NodeTypes.ELSE_STMT:
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

            case NodeTypes.FUN_DECL:
                node = parse_FunDecl(line)
                code_string += node.visit() + "\n"
                scope_stack.append(Scope(indent_level + 1, NodeTypes.FUN_DECL, 0))

            case NodeTypes.PRINT:
                if check_PrintStmt(line):
                    node = parse_PrintStmt(line)
                    code_string += node.visit() + "\n"
                else:
                    print(
                        SyntaxError(
                            line_no,
                            "invalid syntax for print statement\n(keywords and assignment operators arent allowed)",
                        )
                    )

            case _:
                node = parse_ExprNode(line)
                code_string += node.visit() + ";\n"

        line_no += 1
    return code_string
