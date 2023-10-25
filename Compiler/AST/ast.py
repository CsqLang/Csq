"""
Python implementation of Csq AST
"""
from Compiler.Tokenizer.tokenizer import to_str


# Node Types
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
    ACCESS = 12
    COLLECTION_UPDATE = 13
    RETURN = 14
    IMPORT = 15
    UNKNOWN_NODE = 16
    CIMPORT = 17
    CLASS = 18
    BREAK = 19


# Parent AST node type


class ASTNode:
    def __init__(self):
        self.type = None
        self.indent_level = int()


class ExprNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.tokens = []
        self.type = NodeTypes.EXPR

    def visit(self) -> str:
        val = ""
        for tok in self.tokens:
            val += tok.token
        if val[0] == '{' and val[len(val)-1] == '}':
            val = "vector<Cell>" + val 
        return val


class VarDeclNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = ""
        self.var_type = ""
        self.value = ExprNode()
        self.type = NodeTypes.VAR_DECL

    def visit(self) -> str:
        return (
            'allocateVar("' + self.identifier + '",Cell(' + self.value.visit() + "));"
        )


class VarAssignNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = ""
        self.value = ExprNode()
        self.type = NodeTypes.VAR_ASSIGN

    def visit(self) -> str:
        return 'assignVar("' + self.identifier + '",Cell(' + self.value.visit() + "));"


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

    def visit(self) -> str:
        code = "auto " + self.identifier + "=[&]("
        # Args conversion

        for arg in self.parameters:
            if arg != " ":
                code += "Cell " + arg + ","

        if code[len(code) - 1] == ",":
            code = code[: len(code) - 1]
        else:
            pass

        code += "){\n"

        '''
        As parameters are also in terms of variables so they should also
        undergo the generation of variable allocation code so that it can
        be used effectively by other species.
        '''
        
        for arg in self.parameters:
            if arg != ' ':
                code += 'allocateVar("' + arg + '",Cell('+arg+'));\n'

        return code


class IfStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.condition = ExprNode()
        self.type = NodeTypes.IF_STMT

    def visit(self) -> str:
        return "if(" + self.condition.visit() + "){"


class ElseStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.type = NodeTypes.ELSE_STMT

    def visit(self) -> str:
        return "else{"


class ElifStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.condition = ExprNode()
        self.type = NodeTypes.ELIF_STMT

    def visit(self) -> str:
        return "else if(" + self.condition.visit() + "){"


class ForStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.body = None
        self.iter_name = ""
        self.condition = ExprNode()
        self.type = NodeTypes.FOR_STMT

    def visit(self) -> str:
        # return (
        #     "for("
        #     + "int "
        #     + self.iter_name
        #     + "901;"
        #     + self.iter_name + "901 < "
        #     + self.condition.visit()
        #     + ".vectorVal->size();"
        #     + self.iter_name
        #     + "901++){"
        #     + f'allocateVar("{self.iter_name}",{self.condition.visit()}[{self.iter_name + "901"}]);'
        # )
        # return (f"forLoop({self.condition.tokens[0].token}, {self.condition.tokens[3].token}, Cell(1),[](Cell {self.iter_name}__iter)"+"{\n")
        return (
            f'allocateVar("{self.iter_name}",0);' 
            + "\n"
            +  f'for(int {self.iter_name}__iter = {self.condition.tokens[0].token[5:-1]};'
            +  f'{self.iter_name}__iter < {self.condition.tokens[3].token[5:-1]};'
            +  f'{self.iter_name}__iter++)' 
            + "{\n"
            + f"memory[memory.size()-1] = {self.iter_name}__iter;"
            + "\n"
        )


class WhileStmtNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.condition = ExprNode()
        self.type = NodeTypes.WHILE_STMT

    def visit(self) -> str:
        return "while(" + self.condition.visit() + "){"


class CallNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.name = ""
        self.params = []
        self.type = NodeTypes.FUN_CALL


class PrintNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.value = ExprNode()
        self.type = NodeTypes.PRINT

    def visit(self) -> str:
        return "print(" + self.value.visit() + ");"


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
        self.value = ExprNode()
        self.type = NodeTypes.RETURN


class ImportNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.name = ""
        self.path = ''
        self.type = NodeTypes.IMPORT


class CImportNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.name = ""
        self.path = ''
        self.type = NodeTypes.CIMPORT

class ReturnNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.value = ExprNode()
        self.type = NodeTypes.RETURN
    def visit(self) -> str:
        return "return " + self.value.visit() + ";"

class ClassNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.name = ''
        self.type = NodeTypes.CLASS
    def visit(self) -> str:
        return f'__classes__["{self.name}"] = Class();'

'''
This class is very much similar to FunDeclNode but this is decl as a method of a class.
'''
class MethodNode(ASTNode):
    def __init__(self):
        self.identifier = ""
        self.classname = ''
        self.parameters = []

    def visit(self) -> str:
        code = f'__classes__["{self.classname}"].methods["{self.identifier}"] = [](Cell args)' + "{\n" + 'allocateVar("arg", "any", args);\n'
        return code

class MemberVarDeclNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = ""
        self._class_ = ''
        self.value = ExprNode()
        self.type = NodeTypes.VAR_DECL

    def visit(self) -> str:
        return (
            f'__classes__["{self._class_}"].members["{self.identifier}"] = ' + self.value.visit() + ";"
        )

class MemberVarAssignNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.identifier = []
        self._class_ = ''
        self.value = ExprNode()
        self.type = NodeTypes.VAR_ASSIGN

    def visit(self) -> str:
        result = ''
        result += f'__classes__["{self.identifier[0]}"].members["{self.identifier[1]}"] = {self.value.visit()}'
        return result

class BreakNode(ASTNode):
    def __init__(self):
        super().__init__()
        self.type = NodeTypes.BREAK
    def visit(self) -> str:
        return 'break;'