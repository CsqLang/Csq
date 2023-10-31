
from Compiler.AST.ast import *
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