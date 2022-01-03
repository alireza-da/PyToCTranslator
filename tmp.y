%
%
%%
constant : Number 
 
term : Token_Id | constant
 
StartParse : Token_Newline StartParse| finalStatements Token_Newline StartParse | finalStatements Token_Newline 
 
basic_stmt : break_stmt 
           | assign_stmt 
           | arith_exp 
           | bool_exp 
 
arith_exp : term
          | arith_exp  "+"  arith_exp 
          | arith_exp  "-"  arith_exp 
          | arith_exp  "*"  arith_exp 
          | arith_exp  "/"  arith_exp 
          | "-" arith_exp 
          | "(" arith_exp ")" 
 
bool_exp : bool_term "or" bool_term 
         | arith_exp "<" arith_exp 
         | bool_term "and" bool_term 
         | arith_exp ">" arith_exp 
         | arith_exp "<=" arith_exp 
         | arith_exp "<=" arith_exp 
         | bool_term 
 
bool_term : bool_factor 
          | arith_exp "==" arith_exp
          | arith_exp "==" bool_term 
          | T_True 
          | T_False 
         
bool_factor : "not" bool_factor 
            | "(" bool_exp ")" 
 
break_stmt : "break" 
 
assign_stmt : Token_Id "=" arith_exp 
            | Token_Id "=" bool_exp  
 
finalStatements : basic_stmt 
                | cmpd_stmt 
 
cmpd_stmt : if_stmt 
          | while_stmt 
          | for_stmt 
 
if_stmt : "if" bool_exp "{" start_suite
        | "if" bool_exp "{" start_suite elif_stmts
 
elif_stmts : else_stmt 
           | "elif" bool_exp "{" start_suite elif_stmts
 
else_stmt : "else" "{" start_suite 
 
while_stmt : "while" bool_exp "{" start_suite 
 
myrange : term
        | term "," term
        | term "," term "," term
 
for_stmt : "for" Token_Id "in" "range" "(" myrange ")" "{" start_suite                                                                                                                                                 
                                                             
start_suite : basic_stmt 
      | Token_Newline finalStatements suite 
suite : Token_Newline finalStatements suite 
      | Token_Newline end_suite
end_suite : "}" finalStatements 
          | "}" 
          | epsilon
%%