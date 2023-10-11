# -*- coding: utf-8 -*-

"""
    The `cli_txt.py` is mainly for logging
    The `tcolor.py` is mainly for print (equivalent)
"""

from .tcolor import *
from .cli_txt import log_style

__all__ = [
    'header',
    'blue',
    'cyan',
    'green',
    'warning',
    'fail',
    'normal',
    'bold',
    'underline',
    'log_style',
]
