"""
Module: Code Binding Functions

This module contains functions for binding the parsed and visited code with C/C++ APIs.
"""


def bind(current_path, code):
    """
    Bind the parsed and visited code with C/C++ APIs to create a complete C/C++ program.

    Args:
        current_path (str): The path to the current working directory.
        code (str): The code to be bound with C/C++ APIs.

    Returns:
        str: The complete C/C++ program including necessary headers and main function.
    """
    res = (
        '#include "'
        + current_path
        + '/Core/Builtin/basic.h"\n\n//Code starts from here.\n'
    )
    res += "main\n\n" + code + "\nendmain\n"
    return res
