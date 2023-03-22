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
        Block body;
        Scope(){}
        Scope(int level, Block body_){
            indent_level = level;
            body = body_;
        };
    };

    //Struct to store infos about statements
    struct Statement{
        int indent_level;
        int statement_number;
        string statement;
        Statement(){}
        Statement(int statement_num, string statement_, int indent_level_){
            statement_number = statement_num;
            statement = statement_;
            indent_level = indent_level_;
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
    vector<Statement> ParseScope(vector<TokenStream> raw_tokens, string id = ""){
        vector<Statement> statements;
        int statNum = 1;
        for(TokenStream tokenStream : raw_tokens){
            statements.push_back(Statement(statNum, TokenStreamToString(tokenStream),getIndentLevel(tokenStream)));
            statNum++;
        }
        return statements;
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

    /*
    Indentation handling shall be done in such a way in which every
    line with certain indentation shall be stored as an object.
    */
    

    vector<Scope> Scopes;

    void ScopeParser(vector<TokenStream> tokens){
        int deepest_indent = DeepestIndentLevel(tokens);
        for(int indent = deepest_indent; indent >= 0; indent--){
            Scopes.push_back(
                Scope(indent,
                    ParseScope(tokens,indent)
                    )
            );
        }
    }

#endif // PARSEr_H_CSQ4
