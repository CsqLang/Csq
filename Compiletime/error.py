class Error:
    def __init__(self,line:int,message:str) -> None:
        self.msg = message
        self.line = line
    def __str__(self) -> str:
        return f"At Line {self.line} \n {self.__class__.__name__} : {self.msg}"

class SyntaxError(Error):
    """ Syntax errors occur when the code violates
        the rules of the Csq language, such as missing colons,
        mismatched parentheses, or incorrect use of keywords."""

class IndentationError(Error):
    """This error occurs when you have inconsistent 
       or incorrect indentation in your code."""
    
class TypeError(Error):
    """ Type errors occur when you attempt 
        operations on data of incompatible types or 
        use undeclared variables."""
    
class NameError:
    """This error occurs when you try to use 
       a variable or name that hasn't been defined yet."""