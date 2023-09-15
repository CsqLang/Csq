import ast
import glob
import os
import subprocess
from itertools import zip_longest as t_iter
from pathlib import Path

import pycodestyle
"""
This file (or module) runs the files in the current
    directory and its subdirectories.
The iterative nature of the file may make the code slow.
Every file that ends with '.py' is checked, this is to ensure that
    only python files are run to not cause any issues.

This file is run with no arguments, this can be changed later
    if need be.

The following modules (external) are needed to run the code:
    pycodestyle
    pydocstyle

"""

curr_dir = os.getcwd()
DOC_LEN = 20


class StyleChecker:
    """Check the style conformity of the code.

    Functions and classes are the ones considered.
    They needed arguments are supplied when each individual
        method is called


    """

    @staticmethod
    def file_code_style(file_path):
        """Check for files whole files conformity to the style(s)

        :param file_path: The name (or absolute path) of the file path

        """
        StyleChecker.__file = file_path
        style_checker = pycodestyle.StyleGuide(config_file="setup.cfg")
        style_checker.check_files([file_path])
        """
        I couldn't figure out how to run the rest of the commands,
            in a script like manner, so I'll just run them using
            subprocess
        """
        subprocess.run(["pydocstyle", file_path])

    @staticmethod
    def function_code_style(func_):
        """Check for functions conformity to the style(s)

        :param func_: The function(s) found in the file(s)

        """
        func_doc = func_.__doc__
        f_ = Path(StyleChecker.__file).relative_to(curr_dir)
        if (len(func_doc)) < DOC_LEN:
            print("{}: function '{}' Should be documented".format(f_, func_))

    @staticmethod
    def class_code_style(class_):
        """Check for classes conformity to the style(s)

        :param class_: Class(es) found in the file

        """
        class_doc = class_.__doc__
        f_ = Path(StyleChecker.__file).relative_to(curr_dir)
        if (len(class_doc)) < DOC_LEN:
            print("{}: class '{}' should be documented".format(f_, class_))


def collect_names(file_path, node_type):
    """Collect the names of the nodes in a file.

    The nodes include classes and functions which are later used
        in the script

    :param file_path: The location of the file absolute by default
    :param node_type: The type of the object e.g class or function

    """
    with open(file_path, "r") as file:
        source_code = file.read()

    ast_tree = ast.parse(source_code)
    visitor = NameCollector(node_type)
    visitor.visit(ast_tree)

    return visitor.names


class NameCollector(ast.NodeVisitor):
    """The class that defines how the "name" collection will be done"""

    def __init__(self, node_type):
        """Initialize the class"""
        self.names = []
        self.node_type = node_type

    def visit(self, node):
        """Visit each node in a file.

        The function appends the name of the node to its name
            e.g if the node is a function, it is appended to
            function array

        :param node: The type of the object

        """
        if isinstance(node, self.node_type):
            self.names.append(node.name)
        self.generic_visit(node)


py_files = glob.glob(os.path.join(curr_dir, "**/*.py"), recursive=True)

if __name__ == "__main__":
    for file in py_files:
        f_ = Path(file).relative_to(Path(curr_dir))
        print("\n==========< {} >==========\n".format(f_))
        StyleChecker.file_code_style(file)
        class_names = collect_names(file, ast.ClassDef)
        function_names = collect_names(file, ast.FunctionDef)
        for class_name, func_name in t_iter(class_names, function_names):
            if class_name is not None and not class_name.startswith("__"):
                StyleChecker.class_code_style(class_name)
            if func_name is not None and not func_name.startswith("__"):
                StyleChecker.function_code_style(func_name)

        print("\n==========</ {} >==========\n".format(f_))
