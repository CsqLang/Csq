'''
This file binds the code parsed and visited with C/C++ APIs
'''
def bind(current_path, code):
    res = '#include "' + current_path + '/Builtin/basic.h"\n'
    res += 'int main(int argc, char** argv){\n' + code + '\n return 0;\n}\n'
    return res
