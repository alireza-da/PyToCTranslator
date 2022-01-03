%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "y.tab.h"
	#define stack_size 100
	#define DEBUG 1
	
	int yycolumn = 1;
	int startFlag = 1;
	
	#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; 		\
    yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; 	\
    yycolumn += yyleng;												
    
 	static int sp=0, stack [stack_size];
 	static void debug(const char *s){
 		#ifdef DEBUG
		fflush(stdin);
 
		 
 		if(startFlag){
 			printf("------------------------TOKENS--------------------------\n");
 			startFlag=0;
 		}
		int res= strcmp(s, "NL");
		int temp=yylineno;
 		if(res==0){
			printf("\nline: %d ",temp);
 			printf("NEWLINE ");
			fflush(stdout);

 		}
		else{
			printf("Token_%s ", s);	
		}
 		#endif
 	}
 	static void push (int i) 
 	{
   		if (++sp<stack_size) stack[sp]= i;
   		else {printf ("error: stack overflow\n"); exit(1);}
 	}
 	
 	int pop () 
 	{
   		if (sp>-1) return stack[sp--];
   		else {printf ("error: stack underflow\n"); exit(1);}
 	}
 	
 	int top()
 	{
 		if(sp>-1) return stack[sp];
 		else return 1;
 	}
 	
 	static int indent_depth(const char *K)
	{
		int len = strlen(K), i, tab_count=1;
		for(i=0; i< len ; i++)
		{
			if(K[i]=='\t'){
				tab_count++;
			}
			else{
				printf("Nope");
				break;
			}	
		}
		return tab_count;
	}	
 	int depth = 1;
	int scope_depth = 1;
 		
%}
%option yylineno
whitespace [ ]
Multiline_comment \'\'\'.+\'\'\'
%%

[\t" "]*		{ }			
"print"  {debug("Print"); return T_Print;}
"if" {debug("If"); return T_If;}
"in" {debug("In"); return T_In;}
"range" {debug("Range"); return T_Range;}
"for" {debug("For"); return T_For;}
"while" {debug("While"); return T_While;}
"break" {debug("Break"); return T_Break;}
"and" {debug("And"); return T_And;}
"or" {debug("Or"); return T_Or;}
"not" {debug("Not"); return T_Not;}
"elif" {debug("Elif"); return T_Elif;}
"else" {debug("Else"); return T_Else;}
"{" {debug("OB"); scope_depth++; return T_Cln;}
"}" {debug("CB"); scope_depth--; return T_CB;}
">" {debug("GT"); return T_GT;}
"<" {debug("LT"); return T_LT;}
">=" {debug("EGT"); return T_EGT;}
"<=" {debug("ELT"); return T_ELT;}
"==" {debug("EQ"); return T_EQ;}
"!=" {debug("NEQ"); return T_NEQ;}
"True" {debug("True"); return T_True;}
"False" {debug("False"); return T_False;}
"+" {debug("PL"); return T_PL;}
"-" {debug("MN"); return T_MN;}
"*" {debug("ML"); return T_ML;}
"/" {debug("DV"); return T_DV;}
"(" { debug("OP"); return T_OP;}
")" {debug("CP"); return T_CP;}
"[" {debug("OB"); return T_OB;}
"]" {debug("CB"); return T_CB;}
"," {debug("Comma"); return T_Comma;}
"=" {debug("EQL"); return T_EQL;}

-?(([0-9]+)|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {yylval.text = strdup(yytext); debug(yylval.text); return T_Number;}
[_a-zA-Z][_a-zA-Z0-9]* {yylval.text = strdup(yytext); debug(yylval.text); return T_ID;}
"#"([a-z]|[0-9]|[A-Z]|" ")* {}
"\n" {yycolumn=1; debug("NL"); return T_NL;}
<<EOF>> {debug("EOF"); return T_EndOfFile;}

%%
