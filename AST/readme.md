## AST node types:
<li>Expr</li>
This node type represents all expressions such as function calls, binary expressions, unary expressions, etc. To generate the appropriate C++ code with ease else it will require additional code which may consume time and resulting in difficult management of code.
<li>VarDecl</li>
This node type represents all new variable decls.
<li>VarAssign</li>
This node type represents all variable assignments on existing variables it holds same data as VarDecl node but work only for assignments.
<li>Block</li>
This node type represents block.
<li>FunctionDecl</li>
This node type represents function decls.
<li>ClassDecl</li>
This node type represents class decls.
<li>ForLoop</li>
This node type represents for loops.
<li>WhileLoop</li>
This node type represents while loops.
<li>IfStmt</li>
This node type represents if statements.
<li>ElifStmt</li>
This node type represents elif statements.
<li>ElseStmt</li>
This node type represents else statements.
<li>Break</li>
This node type represents the break statements to interupt the control statement.
<li>Group</li>
This node type represents the group statement.
