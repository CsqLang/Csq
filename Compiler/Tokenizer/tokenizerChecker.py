
from Compiler.Grammar.grammar import *
import re

def isIdentifier(val: str) -> bool:
    return re.match(pattern=IDENTIFIERS, string=val)


def isInt(val: str) -> bool:
    return re.match(pattern=INTEGER, string=val)


def isDecimal(val: str) -> bool:
    return re.match(pattern=DECIMAL, string=val)


def isValue(val: str) -> bool:
    if isDecimal(val) or isInt(val):
        return True
    else:
        return False


def isComment(val: str) -> bool:
    return val == "#"


def isLogicalOperator(val: str) -> bool:
    if val in LOGICAL_OPERATORS:
        return True
    else:
        return False


def isAssignmentOperator(val: str) -> bool:
    if val in ASSIGNMENT_OPERATORS:
        return True
    else:
        return False


def isComparisonOperator(val: str) -> bool:
    if val in COMPARISON_OPERATORS:
        return True
    else:
        return False


def isArithmeticOperator(val: str) -> bool:
    if val in ARITHMETIC_OPERATORS:
        return True
    else:
        return False


def isOperator(val: str) -> bool:
    if (
        isArithmeticOperator(val)
        or isLogicalOperator(val)
        or isAssignmentOperator(val)
        or isComparisonOperator(val)
    ):
        return True
    else:
        return False


def isSymbol(val: str) -> bool:
    if val in SYMBOLS:
        return True
    else:
        return False


def isSymbolLaterals(val: str) -> bool:
    if isSymbol(val) or isOperator(val):
        return True
    else:
        return False


def isKeyword(val: str) -> bool:
    if val in KEYWORDS_TABLE:
        return True
    else:
        return False