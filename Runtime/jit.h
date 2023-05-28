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
        }
        else if (opt == "-") {
            return leftVal - rightVal;
        }
        else if (opt == "*") {
            return leftVal * rightVal;
        }
        else if (opt == "/") {
            return leftVal / rightVal;
        } 
        else if (opt == "==") {
            return leftVal == rightVal;
        }
        else if (opt == "!=") {
            return leftVal != rightVal;
        }
        else if (opt == ">") {
            return leftVal > rightVal;
        }
        else if (opt == "<") {
            return leftVal < rightVal;
        }
        else if (opt == ">=") {
            return leftVal >= rightVal;
        }
        else if (opt == "<=") {
            return leftVal <= rightVal;
        }
        else if (opt == "&&") {
            return leftVal && rightVal;
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
                    RuntimeError("invalid binary operator '" + token.token + "' for strings.");
                }
            }
        }
        
    }
    return result;
}

double evalValue(TokenStream tokens) {
    if (tokens.empty()) {
        RuntimeError("Invalid expression");
    }

    unique_ptr<JIT_Node> resultNode = nullptr;

    for (size_t i = 0; i < tokens.size(); i++) {
        const Token& token = tokens[i];

        if (token.type == VALUE) {
            double value = stod(token.token);
            unique_ptr<JIT_Node> node = make_unique<JIT_Value>(value);

            if (resultNode) {
                RuntimeError("Invalid expression");
            }

            resultNode = move(node);
        } 
        else if (token.type == AROPERATOR || token.type == COPERATOR) {
            if (!resultNode || i + 1 >= tokens.size()) {
                RuntimeError("Invalid expression");
            }

            const Token& nextToken = tokens[i + 1];
            if (nextToken.type != VALUE) {
                RuntimeError("Invalid expression");
            }

            double leftVal = resultNode->eval();
            double rightVal = stod(nextToken.token);

            // Apply operator precedence
            if (token.token == "*" || token.token == "/") {
                if (!resultNode->type == JBINOP) {
                    RuntimeError("Invalid expression");
                }

                JIT_BINOP* binopNode = static_cast<JIT_BINOP*>(resultNode.get());

                // Check if the current operator has higher precedence than the previous operator
                if (binopNode->opt == "+" || binopNode->opt == "-") {
                    // Create a new binop node with the current operator and operands
                    unique_ptr<JIT_Node> newBinopNode = make_unique<JIT_BINOP>(
                        move(binopNode->rval),
                        token.token,
                        make_unique<JIT_Value>(rightVal)
                    );

                    binopNode->rval = move(newBinopNode);
                } else {
                    // Create a new binop node with the current operator and operands
                    unique_ptr<JIT_Node> binopNode = make_unique<JIT_BINOP>(
                        move(resultNode),
                        token.token,
                        make_unique<JIT_Value>(rightVal)
                    );

                    resultNode = move(binopNode);
                }
            } 
            else {
                // Create a new binop node with the current operator and operands
                unique_ptr<JIT_Node> binopNode = make_unique<JIT_BINOP>(
                    move(resultNode),
                    token.token,
                    make_unique<JIT_Value>(rightVal)
                );

                resultNode = move(binopNode);
            }

            i++; // Skip the next token since it has been processed
        }
        else{
            RuntimeError("Invalid token "  + token.token);
        }
    }

    if (!resultNode) {
        RuntimeError("Invalid expression");
    }

    return resultNode->eval();
}



bool is(TokenStream tokens, TokenType type){
    for(Token token : tokens){
        if(type == token.type){
            return 1;
        }
    }return 0;
}

//For arithmetic and concatenation and add it to memory
int eval(TokenStream tokens)
{
    //do string eval if string is found
    if(is(tokens, STR)){
        if(is(tokens,VALUE)){
            RuntimeError("couldn't do binary operations between string and a value.");
        }
        else{
            addCell(evalString(tokens));
            return memory_size()-1;
        }
    }
    else if(is(tokens,VALUE)){
        addCell(evalValue(tokens));
        return memory_size()-1;
    }return -1;
}

#define JVal(v,x) unique_ptr<JIT_Node> v = make_unique<JIT_Value>(x)
#define JBinOp(v,x,o,y) unique_ptr<JIT_Node> v = std::make_unique<JIT_BINOP>(std::move(x), o, std::move(y))


#endif // JIT_CSQ4
