'''
Python implementation of Csq AST
'''

#Node types
VARDECL = 0
VARASSIGN = 1
EXPR = 2
IFSTMT = 3
ELIFSTMT = 4
ELSESTMT = 5
FUNDECL = 6
CLASSDECL = 7
BREAK = 8
#Parent AST node type
class Node:
    pass

class Expr(Node):
    value = ''

class VarDecl(Node):
    name = ''
    dtype = ''
    value = Expr()

class VarAssign(Node):
    name = ''
    value = Expr()

class IfStmt(Node):
    conditon = Expr()

class ElifStmt(Node):
    conditon = Expr()

class ElseStmt(Node):
    pass
