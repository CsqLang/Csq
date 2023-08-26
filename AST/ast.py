'''
Python implementation of Csq AST
'''

#Node Types 
class NodeTypes:
    EXPR = 0
    VAR_DECL = 1
    VAR_ASSIGN = 2
    FUN_DECL = 3
    IF_STMT = 4
    ELSE_STMT = 5
    ELIF_STMT = 6
    FOR_STMT = 7
    WHILE_STMT = 8
    BLOCK = 9
    FUN_CALL = 10 
    PRINT = 11
    TYPE = 12
    ACCESS = 13
    COLLECTION_UPDATE = 14
    RETURN = 15
    IMPORT = 16
    UNKNOWN_NODE = 17
    
#Parent AST node type

class ASTNode:
    def __init__(self):
        self.type = None
        self.indent_level = int()

class ExprNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.tokens = []
        self.type = NodeTypes.EXPR

class VarDeclNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = ""
        self.var_type = ""
        self.value = None
        self.type = NodeTypes.VAR_DECL

class VarAssignNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = ""
        self.value = None
        self.type = NodeTypes.VAR_ASSIGN

class BlockNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.statements = []
        self.type = NodeTypes.BLOCK

class FunDeclNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = ""
        self.parameters = []
        self.type = NodeTypes.FUN_DECL

class IfStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.condition = None
        self.type = NodeTypes.IF_STMT

class ElseStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.type = NodeTypes.ELSE_STMT

class ElifStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.condition = None
        self.type = NodeTypes.ELIF_STMT

class ForStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.body = None
        self.iter_name = ""
        self.condition = None
        self.type = NodeTypes.FOR_STMT

class WhileStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.condition = None
        self.type = NodeTypes.WHILE_STMT

class CallNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.name = ""
        self.params = []
        self.type = NodeTypes.FUN_CALL

class PrintNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.value = None
        self.type = NodeTypes.PRINT

class TypeNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.type = NodeTypes.TYPE

class UnknownNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.type = NodeTypes.UNKNOWN_NODE

class AccessNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.index = 0
        self.source = ""
        self.type = NodeTypes.ACCESS

class CollectionUpdateNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.index = None
        self.source = ""
        self.value = None
        self.type = NodeTypes.COLLECTION_UPDATE

class ReturnNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.value = None
        self.type = NodeTypes.RETURN

class ImportNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.name = ""
        self.type = NodeTypes.IMPORT
