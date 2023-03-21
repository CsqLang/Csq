#if !defined(PARSEr_H_CSQ4)
#define PARSEr_H_CSQ4
    //Imports
    #include "../Tokenizer/tokenizer.h"
    #include "../AST/ast.h"
    #include "../Memory/stack.h"

    //Total count of errors.
    int error_count = 0;
    //Some alias
    typedef vector<Token> TokenStream;
    typedef vector<string> StringStream;
    typedef Ptr<Node> NodePtr;
    //Tools required for parsing

    //Program node to store all the childs
    typedef struct : Node{
        vector<Block> statements;
        void addChild(Block child){
            statements.push_back(child);
        }
    }Program;
    //Root for all nodes.
    Program root;


    //Scope for the statements
    struct Scope{
        int indent_level;
        string id;
        Scope(){}
        Scope(int level, string id_){
            indent_level = level;
            id = id_;
        }
    };

    //Getting current indentation level.
    int getIndentLevel(TokenStream tokens){
        int indent_level = 0;
        if(tokens[0].type != INDENT)
            return indent_level;
        else{
            for(Token token : tokens){
                if(token.type == INDENT)
                    indent_level++;
                else
                    break; 
            }
            return indent_level;
        }
    }

    vector<TokenStream> Tokenizer(string code){
        code += "\n";
        vector<TokenStream> lines;
        string current = "";
        for(char ch : code){
            if(ch != '\n')
                current.push_back(ch);
            else{
                lines.push_back(tokenize(current));
                current = "";
            }
        }
        return lines;
    }
    //We can't directly use TokenStream as body of block so for that we use string.
    string TokenStreamToString(TokenStream tokens){
        string result;
        for(Token token : tokens){
            if(token.type == STR)
                result += "\"" + token.token + "\" ";
            else
                result += token.token + " ";
        }
        return result;
    }
    //Function to parse scope of the particular indent_level;
    Block ParseScope(vector<TokenStream> raw_tokens, int indent_level,string id = ""){
        Block block;
        for(TokenStream tokenStream : raw_tokens){
            if(getIndentLevel(tokenStream) == indent_level)
                block.statements.push_back(TokenStreamToString(tokenStream));
        }
        return block;
    }

    //This function is gonna return the deepest indent level.
    int DeepestIndentLevel(vector<TokenStream> tokens)
    {
        int indent_level = 0;
        for(TokenStream tokenStream : tokens)
        {
            if(getIndentLevel(tokenStream) > indent_level){
                indent_level = getIndentLevel(tokenStream);
            }
            else{}
        }
        return indent_level;
    }

    

#endif // PARSEr_H_CSQ4
