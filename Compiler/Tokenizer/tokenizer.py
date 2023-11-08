"""
Python implementation of Csq Tokenizer
"""


from Compiler.Compiletime.error import *

from Compiler.Tokenizer.tokenizerChecker import *

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
    COMMENT = 10
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
    def __init__(self, token: str, token_type: int = 0) -> None:
        """
        Initialize a Token instance.

        Args:
            token (str): The token value.
            token_type (int): The token type represented by TokenType enum.
        """
        self.token = token
        self.type = token_type

    def __str__(self):
        return "('" + self.token + "', " + str(self.type) + ")"


def addToken(value: str, token_type: int) -> Token:
    """Create a Token instance with the given value and token type."""
    token = Token("")
    token.token = value
    token.type = token_type
    return token





def check(val: str, line: int) -> Token:
    """
    Check the type of a token and return a Token object.

    Args:
        val (str): The token value.
        line (int): The line number where the token appears.

    Returns:
        Token: The token object with the determined type.
    """
    token = Token(val)

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


def symbolType(token: Token) -> STOKEN:
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
            elif token.token == "%":
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


def make_token(token: str, token_type: int) -> Token:
    t = Token()
    t.token = token
    t.type = token_type
    return t


def tokenize(line: str) -> list:
    """
    Tokenizes a line of code.

    Args:
        line (str): The input line to tokenize.

    Returns:
        list: A list of Token objects representing the tokens in the line.
    """
    tokens = []
    current_string = current_token = ""
    indentCount = 0
    current_line = 1
    indentation_present = string_presence = False

    # Try to skip parsing a comment since it will be ignored.
    if isComment(line[0]):
        tokens = []

    # Main logic
    else:
        # Check for initial indentation
        if line[0] == " ":
            indentation_present = True
            for char in line:
                if char == " " and indentation_present:
                    tokens.append(Token(" ", TokenType.INDENT))
                    indentCount = indentCount + 1
                else:
                    indentation_present = False

        line = line[indentCount::]  # Remove initial indentation
        for char in line:
            if char == "\n":
                if string_presence:
                    current_string += char
                else:
                    tokens.append(Token("\n", TokenType.NEWLINE))
            elif char == "'" and string_presence == 0:
                string_presence = 1
                # current_string += char
            elif char == "'" and string_presence:
                string_presence = 0
                # current_string += char
                tokens.append(Token('"' + current_string + '"', TokenType.STR))
                current_string = ""
            elif string_presence:
                current_string += char
            elif char == " " or char == "\t" or isSymbolLaterals(char):
                if len(current_token) > 0:
                    # If non-empty string, check if it matches any operator, keyword, or value
                    tokens.append(check(current_token, current_line))
                    current_token = ""
                if isSymbolLaterals(char):
                    # Handle symbols
                    tokens.append(check(char, current_line))
            else:
                current_token += char

        if len(current_token) > 0 and string_presence == 0:
            # Process the last string
            tokens.append(check(current_token, current_line))
        if string_presence:
            SyntaxError(current_line, "unclosed string")

    # Mapping of single-character operators to compound operators
    compound_operators = {
        ":": ":=",
        "=": "==",
        "+": "+=",
        "-": "-=",
        "*": "*=",
        "/": "/=",
        ">": ">=",
        "<": "<=",
        "!": "!=",
    }

    # Final tokens
    resTokens = []

    i = 0
    while i < len(tokens):
        token = tokens[i]
        if (
            token.token in compound_operators
            and i + 1 < len(tokens)
            and tokens[i + 1].token == "="
        ):
            # Use the mapping to get the compound operator
            compound_op = compound_operators[token.token]
            resTokens.append(
                Token(
                    compound_op,
                    TokenType.ASOPERATOR
                    if token.token in (":", "=")
                    else TokenType.COPERATOR,
                )
            )
            i += 1
        elif (
            token.token == "-" 
            and i + 1 < len(tokens) 
            and tokens[i + 1].type == TokenType.VALUE
            and tokens[i - 1].type != TokenType.VALUE
        ):
            resTokens.append(
                Token(
                    "-" + tokens[i + 1].token, TokenType.VALUE
                )
            )
            i+=1

        else:
            resTokens.append(token)
        i += 1

    return resTokens


def to_str(tokens=[]):
    return "".join(map(str, tokens))
