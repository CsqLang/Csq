#if !defined(JIT_CSQ4)
#define JIT_CSQ4
#include "core.h"
/*
We already defined that Csq4 is compiled to native machine code but
in the hood it use C++ as intermediate language and then converted into machine code.
So what is this JIT?
JIT -> Just in time compiler is a body in Csq which combines large operations into a simple operation like:

a = 2+58 
it's not directly used as 2+58 instead it is interpreter into 
60 which is easier to use for the memory.
*/

/*
Now you all may wonder why a new ast for jit is written it's already there in ast.h
but here we do it only for JIT data not the overall Csq code.
*/

enum JIT_NODE_TYPE
{
    JVALUE,
    JBINOP,
};

// JIT Node base class with a virtual eval() function
struct JIT_Node {
    JIT_NODE_TYPE type;
    JIT_Node(JIT_NODE_TYPE type_) : type(type_) {}
    virtual double eval() const = 0;
    virtual ~JIT_Node() {}
};

// JIT Value class
struct JIT_Value : JIT_Node {
    double value;

    JIT_Value(double value_) : JIT_Node(JVALUE), value(value_) {}

    double eval() const override {
        return value;
    }
};

struct JIT_BINOP : JIT_Node {
    std::string opt;
    std::unique_ptr<JIT_Node> lval;
    std::unique_ptr<JIT_Node> rval;

    JIT_BINOP(std::unique_ptr<JIT_Node> lval_, const std::string& opt_, std::unique_ptr<JIT_Node> rval_)
        : JIT_Node(JBINOP), opt(opt_), lval(std::move(lval_)), rval(std::move(rval_)) {}

    double eval() const override {
        double leftVal = lval->eval();
        double rightVal = rval->eval();

        if (opt == "+") {
            return leftVal + rightVal;
        } else if (opt == "-") {
            return leftVal - rightVal;
        } else if (opt == "*") {
            return leftVal * rightVal;
        } else if (opt == "/") {
            return leftVal / rightVal;
        }

        // Handle other cases here or return an error value
        return 0.0;
    }
};

string evalString(TokenStream tokens){
    string result = "";
    string last = "";
    for(Token token : tokens){
        if(result == ""){
            if(token.type == STR){
                result = token.token;
            }
            else{
                RuntimeError("invalid syntax \"\"+.");
            }
        }
        else if(last == "+"){
            result  = result + token.token;
            last = "";
        }
        else if(token.type != STR){
            if(token.type == AROPERATOR){
                if(token.token == "+"){
                    last = "+";
                }
                else{
                    RuntimeError("invalid binary operator for strings.");
                }
            }
        }
        
    }
    return result;
}

bool is(TokenStream tokens, TokenType type){
    for(Token token : tokens){
        if(type == token.type){
            return 1;
        }
    }return 0;
}

//For arithmetic and concatenation and add it to memory
void eval(TokenStream tokens)
{
    //do string eval if string is found
    if(is(tokens, STR)){
        if(is(tokens,VALUE)){
            RuntimeError("couldn't do binary operations between string and a value.");
        }
    }
}

#define JVal(v,x) unique_ptr<JIT_Node> v = make_unique<JIT_Value>(x)
#define JBinOp(v,x,o,y) unique_ptr<JIT_Node> v = std::make_unique<JIT_BINOP>(std::move(x), o, std::move(y))


#endif // JIT_CSQ4
