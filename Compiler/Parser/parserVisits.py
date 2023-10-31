'''
Function to import code on the basis of given ImportNode
'''
from Compiler.utils import _curr_path
from Compiler.Tokenizer.tokenizer import tokenize
from Compiler.Parser.parser import Compile
import os

def visit_ImportNode(node):
    csq_include_path = os.getenv("CSQ_INCLUDE")
    importPath = os.path.join(csq_include_path, "Core", "Include", "Import")
   
    modulePath = None

    if os.path.isfile(os.path.join(_curr_path , node.path+".csq")):
        modulePath = os.path.join(_curr_path , node.path+".csq")
    else:
        modulePath = os.path.join(importPath , node.path+".csq")
    
    module = open(modulePath, "r")
    # Read the file and process it
    code_ = module.read()
    # Convert it into stream of tokens
    lines = []
    for line in code_.split("\n"):
        if line != "":
            lines.append(tokenize(line))

    # Moving forth to compilation
    compiled_code = Compile(lines)
    return compiled_code
'''
Function to import C/C++ code on the basis of given CImportNode
'''
def visit_CImportNode(node):
    csq_include_path = os.getenv("CSQ_INCLUDE")
    cimportPath = os.path.join(csq_include_path, "Core", "Include", "Cimport")
   
    modulePath = None

    if os.path.isfile(os.path.join(_curr_path , node.path+".cpp")):
        modulePath = os.path.join(_curr_path , node.path+".cpp")
    else:
        modulePath = os.path.join(cimportPath , node.path+".cpp")
    
    module = open(modulePath, "r")

    # Read the file and process it
    code_ = module.read()
    return code_
