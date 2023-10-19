# Define a base Error class for handling different types of errors.
class Error:
    """Base class for handling errors in the Csq language."""

    def __init__(self, line: int, message: str) -> None:
        """
        Initialize an Error object.

        Args:
            line (int): The line number where the error occurred.
            message (str): The error message.

        Returns:
            None
        """
        self.msg = message  # Error message
        self.line = line  # Line number where the error occurred

    def __str__(self) -> str:
        """
        Return a string representation of the error.

        Returns:
            str: A string containing the error message and line number.
        """
        return f"At Line {self.line}\n{self.__class__.__name__}: {self.msg}"


# Define a SyntaxError class that inherits from the base Error class.
class SyntaxError(Error):
    """Syntax errors occur when the code violates the rules of the Csq language,
    such as missing colons, mismatched parentheses, or incorrect use of keywords."""

    pass


# Define an IndentationError class that inherits from the base Error class.
class IndentationError(Error):
    """This error occurs when you have inconsistent or incorrect indentation in your code."""

    pass


# Define a TypeError class that inherits from the base Error class.
class TypeError(Error):
    """Type errors occur when you attempt operations on data of incompatible types
    or use undeclared variables."""

    pass


# Define a NameError class that inherits from the base Error class.
class NameError(Error):
    """This error occurs when you try to use a variable or name that hasn't been defined yet."""

    pass
