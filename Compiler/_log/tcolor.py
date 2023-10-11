# -*- coding: utf-8 -*-

class Tcolor:
    """
    Text-Color

    It print colored text to the terminal

    Usage:
        You can print normal text by:
            >>> from tcolor import Tcolor
            >>> print(Tcolor('Default text color'))

        The above one is equivalent of the below:
            >>> from tcolor import normal
            >>> normal('I am in normal color')

        More examples:
            >>> from tcolor import *

            >>> header('I am purple in color')
            >>> blue('I am blue in color')
            >>> cyan('I am cyan in color')
            >>> green('I am green in color')
            >>> warning('I am yellow in color')
            >>> fail('I am red in color')
            >>> normal('I am a normal text')
            >>> bold('I make text bold')
            >>> underline('I underline text')
    """

    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m' # yellow
    FAIL = '\033[91m' # red
    ENDC = '\033[0m' # normal text
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

    # The `ENDC` is a normal text, that is why we include at the end of the print, to make sure color of previous, won't be for the next unless been choosen.

    def __init__(self, msg: bool = False):
        self.msg = msg

    def header(self, msg):
        """Header, it print text in purple"""
        print(f'{self.HEADER}{msg}{self.ENDC}')

    def okblue(self, msg):
        """Okblue, it print text in blue"""
        print(f'{self.OKBLUE}{msg}{self.ENDC}')

    def okcyan(self, msg):
        """Okcyan, it print text in cyan"""
        print(f'{self.OKCYAN}{msg}{self.ENDC}')

    def okgreen(self, msg):
        """Okgreen, it print text in green"""
        print(f'{self.OKGREEN}{msg}{self.ENDC}')

    def warning(self, msg):
        """Warning, it print text in yellow"""
        print(f'{self.WARNING}{msg}{self.ENDC}')

    def fail(self, msg):
        """Fail, it print text in red"""
        print(f'{self.FAIL}{msg}{self.ENDC}')

    def endc(self, msg):
        """Endc, it print text in normal condition"""
        print(f'{self.ENDC}{msg}{self.ENDC}')

    def bold(self, msg):
        """Bold, it make text to be bold"""
        print(f'{self.BOLD}{msg}{self.ENDC}')

    def underline(self, msg):
        """Underline, it underline text"""
        print(f'{self.UNDERLINE}{msg}{self.ENDC}')

    def __str__(self):
        """__str__, it print text in normal condition"""
        return f'{self.ENDC}{self.msg}{self.ENDC}'
    

# APIs
def header(msg):
    """
    Usage:
        >>> from tcolor import header
        >>> header('I am in header color')
    """
    a = Tcolor()
    a.header(msg)


def blue(msg):
    """
    Usage:
        >>> from tcolor import blue
        >>> blue('I am in blue color')
    """
    a = Tcolor()
    a.okblue(msg)


def cyan(msg):
    """
    Usage:
        >>> from tcolor import cyan
        >>> cyan('I am in cyan color')
    """
    a = Tcolor()
    a.okcyan(msg)


def green(msg):
    """
    Usage:
        >>> from tcolor import green
        >>> green('I am in green color')
    """
    a = Tcolor()
    a.okgreen(msg)


def warning(msg):
    """
    Usage:
        >>> from tcolor import warning
        >>> warning('I am in warning color')
    """
    a = Tcolor()
    a.warning(msg)


def fail(msg):
    """
    Usage:
        >>> from tcolor import fail
        >>> fail('I am in red color')
    """
    a = Tcolor()
    a.fail(msg)


def normal(msg):
    """
    Usage:
        >>> from tcolor import normal
        >>> normal('I am in normal color')
    """
    a = Tcolor()
    a.endc(msg)


def bold(msg):
    """
    Usage:
        >>> from tcolor import bold
        >>> bold('I am in bold color')
    """
    a = Tcolor()
    a.bold(msg)


def underline(msg):
    """
    Usage:
        >>> from tcolor import underline
        >>> underline('I am in underline color')
    """
    a = Tcolor()
    a.underline(msg)
