# AST node types

-   Expr
    This node type represents all expressions such as function calls, binary expressions, unary expressions, etc. To generate the appropriate C++ code with ease else it will require additional code which may consume time and resulting in difficult management of code.
-   VarDecl
    This node type represents all new variable decls.
-   VarAssign
    This node type represents all variable assignments on existing variables it holds same data as VarDecl node but work only for assignments.
-   Block
    This node type represents block.
-   FunctionDecl
    This node type represents function decls.
-   ClassDecl
    This node type represents class decls.
-   ForLoop
    This node type represents for loops.
-   WhileLoop
    This node type represents while loops.
-   IfStmt
    This node type represents if statements.
-   ElifStmt
    This node type represents elif statements.
-   ElseStmt
    This node type represents else statements.
-   Break
    This node type represents the break statements to interupt the control statement.
-   Group
    This node type represents the group statement.
