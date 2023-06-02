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

// #include <vector>
// #include <stack>
// #include <cmath>
// #include <cstdlib>

double evalValue(TokenStream ts) {
    vector<string> tokens;
    for (Token token : ts) {
        tokens.push_back(token.token);
    }
    std::stack<double> values;
    std::stack<string> operators;

    auto applyOperator = [&](const string& op) {
        double rightOperand = values.top();
        values.pop();
        double leftOperand = values.top();
        values.pop();

        if (op == "+") {
            values.push(leftOperand + rightOperand);
        } else if (op == "-") {
            values.push(leftOperand - rightOperand);
        } else if (op == "*") {
            values.push(leftOperand * rightOperand);
        } else if (op == "/") {
            values.push(leftOperand / rightOperand);
        } else if (op == "==") {
            values.push(leftOperand == rightOperand);
        } else if (op == ">=") {
            values.push(leftOperand >= rightOperand);
        } else if (op == "<=") {
            values.push(leftOperand <= rightOperand);
        } else if (op == "<") {
            values.push(leftOperand < rightOperand);
        } else if (op == ">") {
            values.push(leftOperand > rightOperand);
        } else if (op == "!=") {
            values.push(leftOperand != rightOperand);
        }
    };

    auto isOperator = [&](const string& token) {
        return (token == "+" || token == "-" || token == "*" || token == "/" || token == "==" || token == ">=" || token == "<=" || token == "<" || token == ">" || token == "!=");
    };

    auto getPrecedence = [&](const string& op) {
        if (op == "+" || op == "-")
            return 1;
        else if (op == "*" || op == "/")
            return 2;
        else if (op == "==" || op == ">=" || op == "<=" || op == "<" || op == ">" || op == "!=")
            return 3;
        return 0;
    };

    for (const string& token : tokens) {
        if (isOperator(token)) {
            while (!operators.empty() && operators.top() != "(" && getPrecedence(operators.top()) >= getPrecedence(token)) {
                applyOperator(operators.top());
                operators.pop();
            }
            operators.push(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                applyOperator(operators.top());
                operators.pop();
            }
            if (!operators.empty())
                operators.pop();
        } else {
            values.push(std::stod(token));
        }
    }

    while (!operators.empty()) {
        applyOperator(operators.top());
        operators.pop();
    }

    if (!values.empty())
        return values.top();
    else
        return 0;
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
