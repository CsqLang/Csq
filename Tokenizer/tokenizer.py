'''
Python implementation of Csq Tokenizer
'''
from Grammar.grammar import *
import re
# Type of Tokens  
class TokenType:
    KEYWORD = 1
    IDENTIFIER = 2
    STR = 3
    VALUE = 4
    SYMBOL = 5
    AROPERATOR = 6
    ASOPERATOR = 7
    COPERATOR = 8
    LOPERATOR = 9
    COMMENT =10
    INDENT = 11
    NEWLINE = 12
    ACCESS_OPERATOR = 13
    UNKNOWN = 14
    BLANK = 15

class STOKEN:
    LBRACE = 1
    RBRACE = 2
    LPAREN = 3
    RPAREN = 4
    LBRACK = 5
    RBRACK = 6
    PERCENT = 7
    EQUAL = 8
    TILDE = 9
    COMMA = 10
    GREATER = 11
    LESSER = 12
    SEMI = 13
    COLAN = 14
    PLUS = 15
    MINUS = 16
    STAR = 17
    BSLASH = 18
    HASHTAG = 19
    AMPER = 20
    VBAR = 21
    NOT = 22
    HAT = 23
    NOTSYMBOL = 24
    DOT = 25
    OR = 26
    AND = 27
    MOD = 28
    FSLASH = 29
    WALRUS = 30

class Token:
    def __init__(self,token:str, token_type:int) -> None:
        self.token = token
        self.type = token_type
    def __str__(self):
        return "('" + self.token + "', " + str(self.type) + ")" 

def addToken(value:str,token_type:int) -> Token:
    token = Token()
    token.token = value
    token.type = token_type
    return token

# This Func not need in Python
# def _in(item:str,list:list) -> bool:
#     """Check Item is present in List"""
#     if item in list:
#         return True
#     else:
#         return False

def isIdentifier(val:str) -> bool:
    return re.match(pattern=IDENTIFIERS,string=val)

def isInt(val:str) -> bool:
    return re.match(pattern=INTEGER,string=val)

def isDecimal(val:str) -> bool:
    return re.match(pattern=DECIMAL,string=val)

def isValue(val:str) -> bool:
    if isDecimal(val) or isInt(val):
        return True
    else:
        return False

def isComment(val:str) -> bool:
    return val == "#"

def isLogicalOperator(val:str) -> bool:
    if val in LOGICAL_OPERATORS:
        return True
    else:
        return False

def isAssignmentOperator(val:str) -> bool:
    if val in ASSIGNMENT_OPERATORS:
        return True
    else:
        return False

def isComparisonOperator(val:str) -> bool:
    if val in COMPARISON_OPERATORS:
        return True
    else:
        return False

def isArithmeticOperator(val:str) -> bool:
    if val in ARITHMETIC_OPERATORS:
        return True
    else:
        return False

def isOperator(val:str) -> bool:
    if (isArithmeticOperator(val) or isLogicalOperator(val) or 
        isAssignmentOperator(val) or isComparisonOperator(val)):
        return True
    else:
        return False

def isSymbol(val:str) -> bool:
    if val in SYMBOLS:
        return True
    else:
        return False

def isSymbolLaterals(val:str) -> bool:
    if isSymbol(val) or isOperator(val):
        return True
    else:
        return False
    
def isKeyword(val:str) -> bool:
    if val in KEYWORDS_TABLE:
        return True
    else:
        return False
    
def check(val:str,line:int) -> Token:
    """check token which type of this"""
    token = Token()
    token.token = val
    if isKeyword(val):
        token.type = TokenType.KEYWORD
    
    elif isOperator(val):
        if isArithmeticOperator(val):
            token.type = TokenType.AROPERATOR
        elif isLogicalOperator(val):
            token.type = TokenType.LOPERATOR
        elif isAssignmentOperator(val):
            token.type = TokenType.ASOPERATOR
        elif isComparisonOperator(val):
            token.type = TokenType.COPERATOR
    
    elif isValue(val):
        token.type = TokenType.VALUE
    
    elif isIdentifier(val):
        token.type = TokenType.IDENTIFIER
    
    elif isSymbol(val):
        token.type = TokenType.SYMBOL
    
    else:
        token.type = TokenType.UNKNOWN


    return token

def symbolType(token:Token) -> STOKEN:
    """Brief token check and about the symbole"""
    match token.type:
        case TokenType.ASOPERATOR:
            if token.token == "=":
                return STOKEN.EQUAL
        
        case TokenType.ASOPERATOR:
            if token.token == "+":
                return STOKEN.PLUS
            elif token.token == "-":
                return STOKEN.MINUS
            elif token.token == "*":
                return STOKEN.STAR
            elif token.token == "/":
                return STOKEN.FSLASH
            elif token.token =="%":
                return STOKEN.MOD
            elif token.token == "^":
                return STOKEN.HAT
            
        case TokenType.SYMBOL:
            if token.token == "!":
                return STOKEN.NOT
            elif token.token == "|":
                return STOKEN.VBAR
            elif token.token == "&":
                return STOKEN.AMPER 
            elif token.token == "{":
                return STOKEN.LBRACE
            elif token.token == "}":
                return STOKEN.RBRACE
            elif token.token == "(":
                return STOKEN.LPAREN
            elif token.token == ")":
                return STOKEN.RPAREN
            elif token.token == "[":
                return STOKEN.LBRACK
            elif token.token == "]":
                return STOKEN.RBRACK
            elif token.token == ".":
                return STOKEN.DOT
            elif token.token == ",":
                return STOKEN.COMMA
            elif token.token == ":":
                return STOKEN.COLAN
            elif token.token == ";":
                return STOKEN.SEMI
            elif token.token == "~":
                return STOKEN.TILDE
        
        case TokenType.LOPERATOR:
            if token.token == "or":
                return STOKEN.OR
            elif token.token == "and":
                return STOKEN.AND
            elif token.token == "not":
                return STOKEN.NOT

        case TokenType.COPERATOR:
            if token.token == ">":
                return STOKEN.GREATER
            elif token.token == "<":
                return STOKEN.LESSER
            
        case _:
            return STOKEN.NOTSYMBOL
def make_token(token:str,token_type:int) -> Token:
    t = Token()
    t.token = token
    t.type = token_type
    return t

def tokenize(line:str) -> list:
    tokens = list()
    current_string, identifier,number, code_ = '','','',''

    identifier_ = 0
    value_end = 0
    current_line = 1
    indentCount = 0
    indent_ended = True
    indentation_present = False
    char_start = False
    string_presence = False
    comment = False

    #Try to skip parsing a comment since it will be ignored.
    if isComment(line[0]):
        tokens = []
    #Main logic
    else:
        # indent is there
        if line[0] == ' ':
            indentation_present = True
            for char in line:
                if char == ' ' and indentation_present:
                    tokens.append(Token(' ', TokenType.INDENT))
                    indentCount = indentCount + 1
                else:
                    indentation_present = False
        # print(indentCount)
        line = line[indentCount::]
        #Proceed Futher
        i = 0
        while i < len(line):
            char = line[i]
            if char == "'" and string_presence == False:
                string_presence = True; 
            elif char == "'" and string_presence:
                string_presence = False
                tokens.append(Token('\"'+current_string + '"', TokenType.STR))
                current_string = ""
            elif char != "'" and string_presence:
                current_string += char
            elif isIdentifier(char) and string_presence == False:
                identifier += char
                identifier_ = 1
            elif isValue(char) and string_presence == False:
                if identifier_:
                    identifier += char
                else:
                    number += char
            elif char == ' ' and string_presence == False:
                if len(identifier) != 0:
                    if identifier in KEYWORDS_TABLE:
                        tokens.append(Token(identifier, TokenType.KEYWORD))
                    else:
                        tokens.append(Token(identifier, TokenType.IDENTIFIER))
                    identifier = ''
                    identifier_ = 0
                elif len(number) != 0:
                    tokens.append(Token(number, TokenType.VALUE))
                    number = ''
            elif isSymbolLaterals(char) and string_presence == False:
                if len(identifier) != 0:
                    if identifier in KEYWORDS_TABLE:
                        tokens.append(Token(identifier, TokenType.KEYWORD))
                    else:
                        tokens.append(Token(identifier, TokenType.IDENTIFIER))
                    identifier = ''
                    identifier_ = 0
                    #Now lets decide the fate of the operator came
                    
                    match char:
                        case ':':
                            if i != len(line)-1:
                                match line[i+1]:
                                    case '=':
                                        tokens.append(Token(':=',TokenType.ASOPERATOR))
                                        i = i+1
                                    case _:
                                        tokens.append(Token(':',TokenType.SYMBOL))
                            else:
                                tokens.append(Token(':',TokenType.SYMBOL))
                        case '>':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('>=',TokenType.COPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('>=',TokenType.COPERATOR))
                        case '<':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('<=',TokenType.COPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('<=',TokenType.COPERATOR))
                        case '=':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('==',TokenType.COPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('=',TokenType.ASOPERATOR))
                        case '+':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('+=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('+',TokenType.AROPERATOR))
                        case '-':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('-=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('-',TokenType.AROPERATOR))
                        case '*':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('*=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('*',TokenType.AROPERATOR))
                        case '/':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('/=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('/',TokenType.AROPERATOR))
                else:
                    tokens.append(Token(number, TokenType.VALUE))
                    identifier = ''
                    identifier_ = ''
                    number = ''

                    #Now lets decide the fate of the operator came
                    
                    match char:
                        case ':':
                            if i != len(line)-1:
                                match line[i+1]:
                                    case '=':
                                        tokens.append(Token(':=',TokenType.ASOPERATOR))
                                        i = i+1
                                    case _:
                                        tokens.append(Token(':',TokenType.SYMBOL))
                            else:
                                tokens.append(Token(':',TokenType.SYMBOL))
                        case '>':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('>=',TokenType.COPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('>=',TokenType.COPERATOR))
                        case '<':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('<=',TokenType.COPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('<=',TokenType.COPERATOR))
                        case '=':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('==',TokenType.COPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('=',TokenType.ASOPERATOR))
                        case '+':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('+=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('+',TokenType.AROPERATOR))
                        case '-':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('-=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('-',TokenType.AROPERATOR))
                        case '*':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('*=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('*',TokenType.AROPERATOR))
                        case '/':
                            match line[i+1]:
                                case '=':
                                    tokens.append(Token('/=',TokenType.AROPERATOR))
                                    i+=1
                                case _:
                                    tokens.append(Token('/',TokenType.AROPERATOR))
            i+=1
        if identifier_:
            if identifier in KEYWORDS_TABLE:
                tokens.append(Token(identifier, TokenType.KEYWORD))
            else:
                tokens.append(Token(identifier, TokenType.IDENTIFIER))
            identifier = ''
            identifier_ = 0
        elif len(number) > 0:
            tokens.append(Token(number,TokenType.VALUE))
        


                    
    return tokens
            
