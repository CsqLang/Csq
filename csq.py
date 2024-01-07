#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
from os import access
from os import getcwd as pwd
from os import getenv, getuid, path, system
from sys import argv as arguments
from sys import version_info

from Compiler.code_format import readCode, toTokens, writeCode
from Compiler.Compiletime.wrapper import bind
from Compiler.Parser.parser import Compile

VERSION = "4.3"


def is_root():
    return geteuid() == 0


def can_write(directory):
    return access(directory, os.W_OK)


def check_python_version():
    """Check python version
    Check if the python version is 3.10 or above
    If not, print an error message and exit
    """

    if version_info.major < 3 or version_info.minor < 10:
        print("Error: Python version 3.10 or above required")
        exit(1)


def printHelp():
    """Print help
    Print the help message for the program
    """

    parser.print_help()


def isFileValid(file):
    """Check if the file is valid
    Check if the arguments passed are enough or and valid
    """

    if len(arguments) < 2 or not path.exists(file):
        printHelp()
        return False

    return True


def findIncludePath():
    """Find the include path
            The function finds the include path for the csq compiler
            Check for predefined locations instead of just relying on environment variables
            Sometimes the environment variables are not set (or shell incorrectly configured)

    Check for the following locations:
            1. $HOME/.csq/include/csq
            2. /usr/local/include/csq
            3. /opt/csq
            4. /usr/include/csq
            4. Current directory (Maybe a developer is testing the compiler)
    """

    # Check for $HOME/.csq/include/csq
    home = getenv("HOME")
    if home is not None:
        csq_include_path = home + "/.csq/include/csq"
        if path.exists(csq_include_path):
            return csq_include_path

    # Check for /usr/local/include/csq
    if path.exists("/usr/local/include/csq"):
        return "/usr/local/include/csq"

    # Check for /opt/csq
    if path.exists("/opt/csq"):
        return "/opt/csq"

    # Check for /usr/include/csq
    if path.exists("/usr/include/csq"):
        return "/usr/include/csq"

    # Check for current directory
    if path.exists(pwd()):
        return pwd()

    # If none of the above locations are found, return None
    return None


def compileFile(file, options, keep=False):
    """Compile the code in a file
    The function takes in a file as string and compiles it.
    The compiled code is stored in a file with the same name
    """
    # csq include path path
    csq_include_path = findIncludePath()

    if csq_include_path is None:
        print("Error: csq include path not found")
        exit(1)

    # Read the file and process it
    raw_code = readCode(file)

    # Convert it into stream of tokens
    lines = toTokens(raw_code)

    # Moving forth to compilation
    compiled_code = Compile(lines)

    # cpp file
    cpp_file = file.replace(".csq", ".cpp")

    final_code = bind(csq_include_path, compiled_code)
    name = file.replace(".csq", "")
    writeCode(final_code, cpp_file)

    print("g++ {} {}".format(options, cpp_file))
    system("g++ {} {}".format(options, cpp_file))
    if not keep:
        system("rm {}".format(cpp_file))


def uninstall():
    """Uninstall csq
    The function uninstalls the csq compiler
    The function removes the csq executable and the csq include path

    First remove the include directory if available
    Then check for the executable and remove it
    The executable should be accessible from the PATH environment variable
    Use the whereis command to find the executable, this should return an array of paths
    Remove the paths (if any)
    If the include directory is the current directory ignore as this is a developer environment
    """
    dirs = [
        path.join(getenv("HOME"), ".csq/include/csq"),
        "/usr/local/include/csq",
        "/opt/csq",
        "/usr/include/csq",
        path.join(getenv("HOME"), ".local/share/csq"),
        path.join(getenv("HOME"), ".local/lib/csq"),
    ]

    bins = ["/usr/local/bin/csq", path.join(getenv("HOME"), ".local/bin/csq")]

    for directory in dirs:
        if path.exists(directory):
            system(f"rm -rf {directory}")
            print(f"Uninstalled from {directory}")

    for binary in bins:
        if path.islink(binary):
            system(f"unlink {binary}")
            print(f"Unlinked binary from {binary}")


if __name__ == "__main__":
    check_python_version()

    parser = argparse.ArgumentParser(description="Compiler for %(prog)s language")
    parser.add_argument("file", help="Input file to compile", nargs="?")
    parser.add_argument(
        "-v", "--version", action="store_true", help="Print the version of csq"
    )
    parser.add_argument(
        "-u", "--uninstall", action="store_true", help="Uninstall the csq"
    )
    parser.add_argument(
        "-k", "--keep", action="store_true", help="Keep the generated cpp file"
    )
    parser.add_argument("-o", "--output", help="Specify the output file")
    parser.add_argument("-O", "--optimize", help="Specify the optimization level")
    parser.add_argument(
        "-c",
        "--compile",
        action="store_true",
        help="Compile the file and generate object file",
    )
    parser.add_argument(
        "-S", "--assembly", action="store_true", help="Generate assembly code"
    )
    parser.add_argument(
        "-E", "--preprocess", action="store_true", help="Generate preprocessed code"
    )
    parser.add_argument(
        "-g", "--debug", action="store_true", help="Generate debug symbols"
    )
    parser.add_argument(
        "-l",
        "--leaks",
        action="store_true",
        help="Compile and find memory leaks in the code.",
    )

    args = parser.parse_args()

    if args.version:
        print("csq version {}".format(VERSION))
        exit(0)

    if args.uninstall:
        uninstall()
        exit(0)

    if args.file and isFileValid(args.file):
        compiler_flags = "-std=c++17"
        if args.optimize:
            try:
                opt_level = int(args.optimize)
                if opt_level > 0 and opt_level <= 3:
                    compiler_flags += " -O" + args.optimize
                elif opt_level < 0:
                    compiler_flags += " -Ofast"
                elif opt_level > 3:
                    compiler_flags += " -Oz"
            except (NameError, ValueError):
                pass
        if args.debug:
            compiler_flags += " -g"
        if args.compile:
            compiler_flags += " -c"
        if args.assembly:
            compiler_flags += " -S"
        if args.preprocess:
            compiler_flags += " -E"
        if args.leaks:
            compiler_flags += " -g -fsanitize=address"
        if args.output:
            compiler_flags += " -o " + args.output
        elif args.compile and not args.output:
            compiler_flags += " -o " + args.file.replace(".csq", ".o")
        else:
            compiler_flags += " -o " + args.file.replace(".csq", "")

        compileFile(args.file, compiler_flags, args.keep)
    else:
        printHelp()
        exit(1)
