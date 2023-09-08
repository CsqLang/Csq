
# Identifiers lookup
IDENTIFIERS = r"^[a-zA-Z_][a-zA-Z0-9_]*$"

# Value lookup
INTEGER = r"[+-]?\d+"
DECIMAL = r"[+-]?\d+(\.\d+)?"

# Operators lookup
# Arithmetic operators
ARITHMETIC_OPERATORS = ["+", "-", "*", "/", "%", "^"]
# Logical operators
LOGICAL_OPERATORS = ["or", "and", "not"]
# Comparison operators
COMPARISON_OPERATORS = ["==", "!=", "<", ">", "<=", ">="]
# Assignment operators
ASSIGNMENT_OPERATORS = ["="]
# Symbols lookup
SYMBOLS = ["{", "}", "(", ")", "[", "]", ",", "~", "@", "$", "&", "!", ":", ";", "."]

# Keyword lookup
KEYWORDS_TABLE = [
    "if", "elif", "else", "def", "for", "while", "return",'in',
    'import', 'cimport'
]
