# Regular expression for identifying valid identifiers
IDENTIFIERS = r"^[a-zA-Z_][a-zA-Z0-9_]*$"

# Regular expressions for matching integer and decimal number literals
INTEGER = r"[+-]?\d+"
DECIMAL = r"[+-]?\d+(\.\d+)?"

# Lists of operators
# Arithmetic operators
ARITHMETIC_OPERATORS = ["+", "-", "*", "/", "%", "^"]
# Logical operators
LOGICAL_OPERATORS = ["or", "and", "not"]
# Comparison operators
COMPARISON_OPERATORS = ["==", "!=", "<", ">", "<=", ">="]
# Assignment operators
ASSIGNMENT_OPERATORS = ["="]

# List of symbols
SYMBOLS = ["{", "}", "(", ")", "[", "]", ",", "~", "@", "$", "&", "!", ":", ";", "."]

# List of keywords
KEYWORDS_TABLE = [
    "if",
    "elif",
    "else",
    "def",
    "for",
    "while",
    "return",
    "in",
    "import",
    "cimport",
    "print",
    "break",
]
