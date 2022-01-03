
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 1



/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 1 "grammar.y"

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdarg.h>
	#include <ctype.h>
	#include "y.tab.h"

	#define MAXRECST 200
	#define MAXST 100
	#define MAXCHILDREN 100
	#define MAXLEVELS 20
	#define MAXQUADS 1000
	
	
	extern int yylex();
	extern char* yytext;
	extern int yylineno;
	extern int depth;
	extern int scope_depth;
	extern int top();
	extern int pop();
	int currentScope = 1, previousScope = 1;
	
	int *arrayScope = NULL;

	void yyerror(const char *msg)
	{
		printf("\nSyntax Error at Line %d, Column : %d\n",  yylineno, yylloc.last_column);
		exit(0);
	}

	typedef struct record
	{
		char *type;
		char *name;
		int decLineNo;
		int lastUseLine;
	} record;

	typedef struct STable
	{
		int no;
		int noOfElems;
		int scope;
		record *Elements;
		int Parent;
		
	} STable;
	
	typedef struct ASTNode
	{
		int nodeNo;
    /*Operator*/
    char *NType;
    int noOps;
    struct ASTNode** NextLevel;
    
    /*Identifier or Const*/
    record *id;
	
	} node;
  
	typedef struct Quad
	{
		char *R;
		char *A1;
		char *A2;
		char *Op;
		int I;
	} Quad;
	
	STable *symbolTables = NULL;
	int sIndex = -1, aIndex = -1, tabCount = 0, tIndex = 0 , lIndex = 0, qIndex = 0, nodeCount = 0, id_counter = 0, label_counter = 0;
	node *rootNode;
	char *tString = NULL, *lString = NULL;
	Quad *allQ = NULL;
	record records[10000];
	char *labels[10000];
	node ***Tree = NULL;
	int *levelIndices = NULL;
	
	/*-----------------------------Declarations----------------------------------*/
	
	record* findRecord(const char *name, const char *type, int scope);
  	node *createID_Const(char *value, char *type, int scope);
  	int power(int base, int exp);
  	void updateCScope(int scope);
  	void resetDepth();
	int scopeBasedTableSearch(int scope);
	void initNewTable(int scope);
	void init();
	int searchRecordInScope(const char* type, const char *name, int index);
	void insertRecord(const char* type, const char *name, int lineNo, int scope);
	int searchRecordInScope(const char* type, const char *name, int index);
	void printSTable();
	void freeAll();
	int checkIfBinOperator(char *Op);
	
	/*------------------------------------------------------------------------------*/
	
	void Xitoa(int num, char *str)
	{
		if(str == NULL)
		{
			 printf("Allocate Memory\n");
		   return;
		}
		sprintf(str, "%d", num);
	}

	
	char *makeStr(int no, int flag)
	{
		char A[10];
		Xitoa(no, A);
		
		if(flag==1)
		{
				strcpy(tString, "T");
				strcat(tString, A);
				insertRecord("ICGTempVar", tString, -1, 0);
				return tString;
		}
		else
		{
				strcpy(lString, "L");
				strcat(lString, A);
				insertRecord("ICGTempLabel", lString, -1, 0);
				return lString;
		}

	}
	
	void makeQ(char *R, char *A1, char *A2, char *Op)
	{
		
		allQ[qIndex].R = (char*)malloc(strlen(R)+1);
		allQ[qIndex].Op = (char*)malloc(strlen(Op)+1);
		allQ[qIndex].A1 = (char*)malloc(strlen(A1)+1);
		allQ[qIndex].A2 = (char*)malloc(strlen(A2)+1);
		
		strcpy(allQ[qIndex].R, R);
		strcpy(allQ[qIndex].A1, A1);
		strcpy(allQ[qIndex].A2, A2);
		strcpy(allQ[qIndex].Op, Op);
		allQ[qIndex].I = qIndex;
 
		qIndex++;
		
		return;
	}
	
	int checkIfBinOperator(char *Op)
	{
		if((!strcmp(Op, "+")) || (!strcmp(Op, "*")) || (!strcmp(Op, "/")) || (!strcmp(Op, ">=")) || (!strcmp(Op, "<=")) || (!strcmp(Op, "<")) || (!strcmp(Op, ">")) || 
			 (!strcmp(Op, "in")) || (!strcmp(Op, "==")) || (!strcmp(Op, "and")) || (!strcmp(Op, "or")))
			{
				return 1;
			}
			
			else 
			{
				return 0;
			}
	}
	
	void codeGenOp(node *opNode)
	{
		if(opNode == NULL)
		{
			return;
		}
		
		if(opNode->NType == NULL)
		{
			if((!strcmp(opNode->id->type, "Identifier")) || (!strcmp(opNode->id->type, "Constant")))
			{
				printf("T%d = %s\n", opNode->nodeNo, opNode->id->name);
				makeQ(makeStr(opNode->nodeNo, 1), opNode->id->name, "-", "=");
			}
			return;
		}
		
		if((!strcmp(opNode->NType, "If")) || (!strcmp(opNode->NType, "Elif")))
		{			
			switch(opNode->noOps)
			{
				case 2 : 
				{
					int temp = lIndex;
					codeGenOp(opNode->NextLevel[0]);
					printf("If False T%d goto L%d\n", opNode->NextLevel[0]->nodeNo, lIndex);
					makeQ(makeStr(temp, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");
					lIndex++;
					codeGenOp(opNode->NextLevel[1]);
					lIndex--;
					printf("L%d: ", temp);
					makeQ(makeStr(temp, 0), "-", "-", "Label");
					break;
				}
				case 3 : 
				{
					int temp = lIndex;
					codeGenOp(opNode->NextLevel[0]);
					printf("If False T%d goto L%d\n", opNode->NextLevel[0]->nodeNo, lIndex);
					makeQ(makeStr(temp, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");					
					codeGenOp(opNode->NextLevel[1]);
					printf("goto L%d\n", temp+1);
					makeQ(makeStr(temp+1, 0), "-", "-", "goto");
					printf("L%d: ", temp);
					makeQ(makeStr(temp, 0), "-", "-", "Label");
					codeGenOp(opNode->NextLevel[2]);
					printf("L%d: ", temp+1);
					makeQ(makeStr(temp+1, 0), "-", "-", "Label");
					lIndex+=2;
					break;
				}
			}
			return;
		}
		
		if(!strcmp(opNode->NType, "Else"))
		{
			codeGenOp(opNode->NextLevel[0]);
			return;
		}
		
		if(!strcmp(opNode->NType, "While"))
		{
			int temp = lIndex;
			printf("L%d:\n",  lIndex);
			makeQ(makeStr(temp, 0), "-", "-", "Label");
			codeGenOp(opNode->NextLevel[0]);
			printf("If False T%d goto L%d\n", opNode->NextLevel[0]->nodeNo, lIndex+1);		
			makeQ(makeStr(temp+1, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");								
			lIndex+=2;			
			codeGenOp(opNode->NextLevel[1]);
			printf("goto L%d\n", temp);
			makeQ(makeStr(temp, 0), "-", "-", "goto");
			printf("L%d: ", temp+1);
			makeQ(makeStr(temp+1, 0), "-", "-", "Label"); 
			lIndex = lIndex+2;
			return;
		}
		if(!strcmp(opNode->NType, "For")){
			int temp = lIndex;

			// id assigning to zero
			printf("T%d = 0\n", opNode->nodeNo);
			int iteration_condition_temp_no = opNode->NextLevel[0]->NextLevel[0]->nodeNo;
			makeQ(makeStr(iteration_condition_temp_no, 1), "0", "-", "=");
			printf("%s = T%d\n", opNode->NextLevel[1]->id->name, iteration_condition_temp_no);
			char *id_name = opNode->NextLevel[1]->id->name;
			makeQ(opNode->NextLevel[1]->id->name, makeStr(iteration_condition_temp_no, 1), "-", "=");		

			// evaluating boolean expression
			printf("L%d:\n",  lIndex);
			makeQ(makeStr(temp, 0), "-", "-", "Label");
			codeGenOp(opNode->NextLevel[0]);
			printf("If False T%d goto L%d\n", opNode->NextLevel[0]->nodeNo, lIndex+1);		
			makeQ(makeStr(temp+1, 0), makeStr(opNode->NextLevel[0]->nodeNo, 1), "-", "If False");
			
			lIndex+=2;
			// start suite 			
			codeGenOp(opNode->NextLevel[3]);

			// increment operation
			char *X1 = (char*)malloc(10);
			char *X2 = (char*)malloc(10);
			
			strcpy(X1, makeStr(iteration_condition_temp_no, 1));
			strcpy(X2, makeStr(iteration_condition_temp_no, 1));

			printf("%s = T%d %s 1\n", id_name, iteration_condition_temp_no, "+");
			makeQ(X1, X2, "1", "+");
			free(X1);
			free(X2);
			printf("%s = T%d\n", id_name, opNode->nodeNo);
			makeQ( id_name, makeStr(iteration_condition_temp_no, 1), "-", "=");

			// iteration
			printf("goto L%d\n", temp);
			makeQ(makeStr(temp, 0), "-", "-", "goto");

			// end of iteration
			printf("L%d: ", temp+1);
			makeQ(makeStr(temp+1, 0), "-", "-", "Label"); 
			lIndex = lIndex+2;
			return;

		}
		if(!strcmp(opNode->NType, "Next"))
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);
			return;
		}
		
		if(!strcmp(opNode->NType, "BeginBlock"))
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);		
			return;	
		}
		
		if(!strcmp(opNode->NType, "EndBlock"))
		{
			switch(opNode->noOps)
			{
				case 0 : 
				{
					break;
				}
				case 1 : 
				{
					codeGenOp(opNode->NextLevel[0]);
					break;
				}
			}
			return;
		}
		
		if(!strcmp(opNode->NType, "ListIndex"))
		{
			printf("T%d = %s[%s]\n", opNode->nodeNo, opNode->NextLevel[0]->id->name, opNode->NextLevel[1]->id->name);
			makeQ(makeStr(opNode->nodeNo, 1), opNode->NextLevel[0]->id->name, opNode->NextLevel[1]->id->name, "=[]");
			return;
		}
		
		if(checkIfBinOperator(opNode->NType)==1)
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);
			char *X1 = (char*)malloc(10);
			char *X2 = (char*)malloc(10);
			char *X3 = (char*)malloc(10);
			
			strcpy(X1, makeStr(opNode->nodeNo, 1));
			strcpy(X2, makeStr(opNode->NextLevel[0]->nodeNo, 1));
			strcpy(X3, makeStr(opNode->NextLevel[1]->nodeNo, 1));

			printf("T%d = T%d %s T%d\n", opNode->nodeNo, opNode->NextLevel[0]->nodeNo, opNode->NType, opNode->NextLevel[1]->nodeNo);
			makeQ(X1, X2, X3, opNode->NType);
			free(X1);
			free(X2);
			free(X3);
			return;
		}
		
		if(!strcmp(opNode->NType, "-"))
		{
			if(opNode->noOps == 1)
			{
				codeGenOp(opNode->NextLevel[0]);
				char *X1 = (char*)malloc(10);
				char *X2 = (char*)malloc(10);
				strcpy(X1, makeStr(opNode->nodeNo, 1));
				strcpy(X2, makeStr(opNode->NextLevel[0]->nodeNo, 1));
				printf("T%d = %s T%d\n", opNode->nodeNo, opNode->NType, opNode->NextLevel[0]->nodeNo);
				makeQ(X1, X2, "-", opNode->NType);	
			}
			
			else
			{
				codeGenOp(opNode->NextLevel[0]);
				codeGenOp(opNode->NextLevel[1]);
				char *X1 = (char*)malloc(10);
				char *X2 = (char*)malloc(10);
				char *X3 = (char*)malloc(10);
			
				strcpy(X1, makeStr(opNode->nodeNo, 1));
				strcpy(X2, makeStr(opNode->NextLevel[0]->nodeNo, 1));
				strcpy(X3, makeStr(opNode->NextLevel[1]->nodeNo, 1));

				printf("T%d = T%d %s T%d\n", opNode->nodeNo, opNode->NextLevel[0]->nodeNo, opNode->NType, opNode->NextLevel[1]->nodeNo);
				makeQ(X1, X2, X3, opNode->NType);
				free(X1);
				free(X2);
				free(X3);
				return;
			
			}
		}
		
		if(!strcmp(opNode->NType, "NewLine"))
		{
			codeGenOp(opNode->NextLevel[0]);
			codeGenOp(opNode->NextLevel[1]);
			return;
		}
		
		if(!strcmp(opNode->NType, "="))
		{
			codeGenOp(opNode->NextLevel[1]);
			printf("%s = T%d\n", opNode->NextLevel[0]->id->name, opNode->NextLevel[1]->nodeNo);
			makeQ(opNode->NextLevel[0]->id->name, makeStr(opNode->NextLevel[1]->nodeNo, 1), "-", opNode->NType);
			return;
		}
		
		
		if(!(strcmp(opNode->NType, "Print")))
		{
			codeGenOp(opNode->NextLevel[0]);
			printf("Print T%d\n", opNode->NextLevel[0]->nodeNo);
			makeQ("-", makeStr(opNode->nodeNo, 1), "-", "Print");
		}
		if(opNode->noOps == 0)
		{
			if(!strcmp(opNode->NType, "break"))
			{
				printf("goto L%d\n", lIndex);
				makeQ(makeStr(lIndex, 0), "-", "-", "goto");
			}

			
			if(!strcmp(opNode->NType, "return"))
			{
				printf("return\n");
				makeQ("-", "-", "-", "return");
			}
		}
		
		
	}
	
  node *createID_Const(char *type, char *value, int scope)
  {
    node *newNode;
    newNode = (node*)calloc(1, sizeof(node));
    newNode->NType = NULL;
    newNode->noOps = -1;
    newNode->id = findRecord(value, type, scope);
    newNode->nodeNo = nodeCount++;
    return newNode;
  }

  node *createOp(char *oper, int noOps, ...)
  {
    va_list params;
    node *newNode;
    int i;
    newNode = (node*)calloc(1, sizeof(node));
    
    newNode->NextLevel = (node**)calloc(noOps, sizeof(node*));
    
    newNode->NType = (char*)malloc(strlen(oper)+1);
    strcpy(newNode->NType, oper);
    newNode->noOps = noOps;
    va_start(params, noOps);
    for (i = 0; i < noOps; i++)
    	newNode->NextLevel[i] = va_arg(params, node*);
		if(newNode->NextLevel[i]){
			printf("\n node type: %d\n", newNode->NextLevel[i]->noOps);
		}
			
		
    va_end(params);
    newNode->nodeNo = nodeCount++;
    return newNode;
  }
  
  
  
	int power(int base, int exp)
	{
		int i =0, res = 1;
		for(i; i<exp; i++)
		{
			res *= base;
		}
		return res;
	}
	
	void updateCScope(int scope)
	{
		currentScope = scope;
	}
	
	void resetDepth()
	{
		while(top()) pop();
		depth = 10;
	}
	
	int scopeBasedTableSearch(int scope)
	{
		int i = sIndex;
		for(i; i > -1; i--)
		{
			if(symbolTables[i].scope == scope)
			{
				return i;
			}
		}
		return -1;
	}
	
	void initNewTable(int scope)
	{
		arrayScope[scope]++;
		sIndex++;
		symbolTables[sIndex].no = sIndex;
		symbolTables[sIndex].scope = power(scope, arrayScope[scope]);
		symbolTables[sIndex].noOfElems = 0;		
		symbolTables[sIndex].Elements = (record*)calloc(MAXRECST, sizeof(record));
		
		symbolTables[sIndex].Parent = scopeBasedTableSearch(currentScope); 
	}
	
	void init()
	{
		int i = 0;
		symbolTables = (STable*)calloc(MAXST, sizeof(STable));
		arrayScope = (int*)calloc(100, sizeof(int));
		initNewTable(1);
		tString = (char*)calloc(10, sizeof(char));
		lString = (char*)calloc(10, sizeof(char));
		allQ = (Quad*)calloc(MAXQUADS, sizeof(Quad));
		
		levelIndices = (int*)calloc(MAXLEVELS, sizeof(int));
		Tree = (node***)calloc(MAXLEVELS, sizeof(node**));
		for(i = 0; i<MAXLEVELS; i++)
		{
			Tree[i] = (node**)calloc(MAXCHILDREN, sizeof(node*));
		}
	}

	int searchRecordInScope(const char* type, const char *name, int index)
	{
		int i =0;
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if((strcmp(symbolTables[index].Elements[i].type, type)==0) && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				return i;
			}	
		}
		return -1;
	}
		
	void modifyRecordID(const char *type, const char *name, int lineNo, int scope)
	{
		int i =0;
		int index = scopeBasedTableSearch(scope);
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					symbolTables[index].Elements[i].lastUseLine = lineNo;
					return;
				}	
			}
			printf("%s '%s' at line %d Not Declared\n", type, name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				symbolTables[index].Elements[i].lastUseLine = lineNo;
				return;
			}	
		}
		return modifyRecordID(type, name, lineNo, symbolTables[symbolTables[index].Parent].scope);
	}
	
	void insertRecord(const char* type, const char *name, int lineNo, int scope)
	{ 
		int FScope = power(scope, arrayScope[scope]);
		int index = scopeBasedTableSearch(FScope);
		int recordIndex = searchRecordInScope(type, name, index);
		if(recordIndex==-1)
		{
			
			symbolTables[index].Elements[symbolTables[index].noOfElems].type = (char*)calloc(30, sizeof(char));
			symbolTables[index].Elements[symbolTables[index].noOfElems].name = (char*)calloc(20, sizeof(char));
		
			strcpy(symbolTables[index].Elements[symbolTables[index].noOfElems].type, type);	
			strcpy(symbolTables[index].Elements[symbolTables[index].noOfElems].name, name);
			symbolTables[index].Elements[symbolTables[index].noOfElems].decLineNo = lineNo;
			symbolTables[index].Elements[symbolTables[index].noOfElems].lastUseLine = lineNo;
			symbolTables[index].noOfElems++;

		}
		else
		{
			symbolTables[index].Elements[recordIndex].lastUseLine = lineNo;
		}
	}
	
	
	record* findRecord(const char *name, const char *type, int scope)
	{
		int i =0;
		int index = scopeBasedTableSearch(scope);
		//printf("FR: %d, %s\n", scope, name);
		if(index==0)
		{
			for(i=0; i<symbolTables[index].noOfElems; i++)
			{
				
				if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
				{
					return &(symbolTables[index].Elements[i]);
				}	
			}
			printf("\n%s '%s' at line %d Not Found in Symbol Table\n", type, name, yylineno);
			exit(1);
		}
		
		for(i=0; i<symbolTables[index].noOfElems; i++)
		{
			if(strcmp(symbolTables[index].Elements[i].type, type)==0 && (strcmp(symbolTables[index].Elements[i].name, name)==0))
			{
				return &(symbolTables[index].Elements[i]);
			}	
		}
		return findRecord(name, type, symbolTables[symbolTables[index].Parent].scope);
	}

	void printSTable()
	{
		int i = 0, j = 0;
		
		printf("\n----------------------------All Symbol Tables----------------------------");
		printf("\nScope\tName\tType\t\tDeclaration\tLast Used Line\n");
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				printf("(%d, %d)\t%s\t%s\t%d\t\t%d\n", symbolTables[i].Parent, symbolTables[i].scope, symbolTables[i].Elements[j].name, symbolTables[i].Elements[j].type, symbolTables[i].Elements[j].decLineNo,  symbolTables[i].Elements[j].lastUseLine);
			}
		}
		
		printf("-------------------------------------------------------------------------\n");
		
	}
	
	void ASTToArray(node *root, int level)
	{
	  if(root == NULL )
	  {
	    return;
	  }
	  
	  if(root->noOps <= 0)
	  {
	  	Tree[level][levelIndices[level]] = root;
	  	levelIndices[level]++;
	  }
	  
	  if(root->noOps > 0)
	  {
	 		int j;
	 		Tree[level][levelIndices[level]] = root;
	 		levelIndices[level]++; 
	    for(j=0; j<root->noOps; j++)
	    {
	    	ASTToArray(root->NextLevel[j], level+1);
	    }
	  }
	}
	
	void printAST(node *root)
	{
		printf("\n-------------------------Abstract Syntax Tree--------------------------\n");
		ASTToArray(root, 0);
		int j = 0, p, q, maxLevel = 0, lCount = 0;
		
		while(levelIndices[maxLevel] > 0) maxLevel++;
		
		while(levelIndices[j] > 0)
		{
			for(q=0; q<lCount; q++)
			{
				printf(" ");
			
			}
			for(p=0; p<levelIndices[j] ; p++)
			{
				if(Tree[j][p]->noOps == -1)
				{
					printf("%s  ", Tree[j][p]->id->name);
					lCount+=strlen(Tree[j][p]->id->name);
				}
				else if(Tree[j][p]->noOps == 0)
				{
					printf("%s  ", Tree[j][p]->NType);
					lCount+=strlen(Tree[j][p]->NType);
				}
				else
				{
					printf("%s(%d) ", Tree[j][p]->NType, Tree[j][p]->noOps);
				}
			}
			j++;
			printf("\n");
		}
	}
	
	int IsValidNumber(char * string)
	{
   for(int i = 0; i < strlen( string ); i ++)
   {
      //ASCII value of 0 = 48, 9 = 57. So if value is outside of numeric range then fail
      //Checking for negative sign "-" could be added: ASCII value 45.
      if (string[i] < 48 || string[i] > 57)
         return 0;
   }
 
   return 1;
	}
	
	int deadCodeElimination()
	{
		int i = 0, j = 0, flag = 1, XF=0;
		while(flag==1)
		{
			flag=0;
			for(i=0; i<qIndex; i++)
			{
				XF=0;
				if(!((strcmp(allQ[i].R, "-")==0) | (strcmp(allQ[i].Op, "Call")==0) | (strcmp(allQ[i].Op, "Label")==0) | (strcmp(allQ[i].Op, "goto")==0) | (strcmp(allQ[i].Op, "If False")==0)))
				{
					for(j=0; j<qIndex; j++)
					{
							if(((strcmp(allQ[i].R, allQ[j].A1)==0) && (allQ[j].I!=-1)) | ((strcmp(allQ[i].R, allQ[j].A2)==0) && (allQ[j].I!=-1)))
							{
								XF=1;
							}
					}
				
					if((XF==0) & (allQ[i].I != -1))
					{
						allQ[i].I = -1;
						flag=1;
					}
				}
			}
		}
		return flag;
	}
	
	
	void printQuads()
	{
		printf("\n--------------------------------All Quads---------------------------------\n");
		int i = 0;
		qIndex;
		
		for(i=0; i<qIndex; i++)
		{
			if(allQ[i].I > -1)
				printf("%d\t%s\t%s\t%s\t%s\n", allQ[i].I, allQ[i].Op, allQ[i].A1, allQ[i].A2, allQ[i].R);
		}
		printf("\n--------------------------------------------------------------------------\n");
		
	}

	int ContainsLetter(const char* String){
		//Abort if no string is passed
		if(String == NULL) return 0;
	
		while((*String) != '\0')
		{
			if(isalpha(*String)) return 1;
			String++;
		}
		return 0;
	}

	

	char* check_data_type(char* data){
		// it's a number
		if(ContainsLetter(data) == 0){
			if(strchr(data, '.')){
				return "double";
			}
			else return "int";	
		}
		else if(strchr(data, '"')) return "char*";
		else return "id";
	}

	char* find_id_data_type(char* name){
		int i = 0;
		if(id_counter == 0){
			return NULL;
		}
		for(i=0; i<id_counter; i++){
			// printf("%s-%s\n", records[i].name, name);
			if(!strcmp(records[i].name, name)){
				// printf("type: %s\n", records[i].type);
				return records[i].type;
			}
		}
		return NULL;
	}

	int check_label(char *label){
		int i;
		for(int i = 0; i < label_counter;i++){
			if(!strcmp(labels[i], label)){
				return 0;
			}
		}
		return 1;
	}
	int find_index_of_condition(char* lv_name){
		for(int i=0; i<qIndex; i++){
			if(!strcmp(lv_name, allQ[i].R)){
				return i;
			}
		}
		return -1;
	}
	// generate c output code
	void generateCCode(){
		FILE *file = fopen("output.c", "w");
		if (file == NULL){   
			printf("Error! Could not open file\n"); 
			exit(-1); // must include stdlib.h 
		} 
		fprintf(file, "//Auto Generated C Code. Call the c_code() function inside your main() Function.\n//It can be included by either linking or defining.\n//Include all preprocessors into your code\n"); // write to file
		// write main
		fprintf(file, "#include <stdio.h>\n#define True 1\n#define False 0\n");
		// Declarations
		fprintf(file, "void c_code();\n");
		// Main
		fprintf(file, "int main(){\n");
		fprintf(file, "\tc_code();\n}\n");
		// c_code() Definition
		printf("\n--------------------------------C-Code---------------------------------\n");
		fprintf(file, "void c_code(){\n");
		printf("void c_code(){\n");
		int i;
		for(i=0; i<qIndex; i++)
		{
			if(allQ[i].I > -1){
				// right value is an id
				if(strstr(allQ[i].Op, "goto")){
					fprintf(file, "\tgoto %s;\n", allQ[i].R);
					printf("\tgoto %s;\n", allQ[i].R);
				}
				
				else if(strstr(allQ[i].Op, "Label")){
					// dead label elimination
					if(check_label(allQ[i].R)){
						labels[label_counter] = (char *)malloc(strlen(allQ[i].R)+1);
						labels[label_counter] = allQ[i].R;
						label_counter++;
						fprintf(file, "%s: ;\n",  allQ[i].R);
						printf("%s: ;\n",  allQ[i].R);
					}
					// fprintf(file, "%s:\n",  allQ[i].R);
					// printf("%s:\n",  allQ[i].R);
				}
				else if(strstr(allQ[i].Op, "If")){
					if(!strcmp("If False", allQ[i].Op)){
						// if(find_index_of_condition(allQ[i].A1)){
						// 	int idx = find_index_of_condition(allQ[i].A1);
						// 	// fprintf(file, "\t%s %s %s;\n", allQ[idx].A1, allQ[idx].Op, allQ[idx].A2);
						// 	// printf("\t%s %s %s;\n", allQ[idx].A1, allQ[idx].Op, allQ[idx].A2);
						// 	fprintf(file, "\tif(!(%s %s %s)){\n\t\tgoto %s;\n\t}\n", allQ[idx].A1, allQ[idx].Op, allQ[idx].A2,  allQ[i].R);
						// 	printf("\tif(!(%s %s %s)){\n\t\tgoto %s;\n\t}\n", allQ[idx].A1, allQ[idx].Op, allQ[idx].A2,  allQ[i].R);
						// }
						fprintf(file, "\tif(!%s){\n\t\tgoto %s;\n\t}\n", allQ[i].A1,  allQ[i].R);
						printf("\tif(!%s){\n\t\tgoto %s;\n\t}\n", allQ[i].A1,  allQ[i].R);		
					}
					else if(!strcmp("If True", allQ[i].Op)){
						fprintf(file, "\tif(%s){\n\t\tgoto %s;\n\t}\n", allQ[i].A1,  allQ[i].R);
						printf("\tif(%s){\n\t\tgoto %s;\n\t}\n", allQ[i].A1,  allQ[i].R);		
					}
				}
				// other ops such as "=" 
				else{
					// printf("\t%s\t%s\t%s\t%s\n",   allQ[i].Op, allQ[i].A1, allQ[i].A2, allQ[i].R);
					// if rl has id
					if(check_data_type(allQ[i].A1) == "id"){
						// one left value operation
						if(strchr(allQ[i].A2, '-')){
							char* type;
							if(find_id_data_type(allQ[i].A1) != NULL){
								
								type = find_id_data_type(allQ[i].A1);
								// printf("type: %s\n", type);
							}
							// create a record for left id if it is not existed 
							if(find_id_data_type(allQ[i].R)){
								// reassign the variable
								fprintf(file, "\t%s %s %s;\n", allQ[i].R, allQ[i].Op, allQ[i].A1);
								printf("\t%s %s %s;\n", allQ[i].R, allQ[i].Op, allQ[i].A1);
							}
							else{
								record lr;
								records[id_counter] = lr;
								lr.name = allQ[i].R;
								lr.type = type;
								lr.decLineNo = 0;
								lr.lastUseLine = 0;
								// printf("type: %s\n", lr.type);
								records[id_counter] = lr;
								id_counter++;
								// define the variable
								fprintf(file, "\t%s %s %s %s;\n", type, allQ[i].R, allQ[i].Op, allQ[i].A1);
								printf("\t%s %s %s %s;\n", type, allQ[i].R, allQ[i].Op, allQ[i].A1);
							}	
						}
						else{
							char* type;
							if(find_id_data_type(allQ[i].A1)){
								type = find_id_data_type(allQ[i].A1);
							}
							// create a record for left id if it is not existed 
							if(find_id_data_type(allQ[i].R)){
								// reassign the variable
								fprintf(file, "\t%s = %s %s %s;\n", allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
								printf("\t%s  = %s %s %s;\n", allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
							}
							else{
								record lr;
								lr.name = allQ[i].R;
								lr.type = type;
								records[id_counter] = lr;
								id_counter++;
								// define the variable
								fprintf(file, "\t%s %s = %s %s %s;\n", type, allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
								printf("\t%s %s  = %s %s %s;\n", type, allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
							}
						}
						// fprintf("\t%s\t%s\t%s\t%s\n",   allQ[i].Op, allQ[i].A1, allQ[i].A2, allQ[i].R);
					}
					// if rl is a number or a string
					else {
						
						if(strchr(allQ[i].A2, '-')){
							char* type = check_data_type(allQ[i].A1);						
							if(find_id_data_type(allQ[i].R) != NULL){
								// reassign the variable
								fprintf(file, "\t%s %s %s;\n", allQ[i].R, allQ[i].Op, allQ[i].A1);
								printf("\t%s %s %s;\n", allQ[i].R, allQ[i].Op, allQ[i].A1);
							}
							else{								
								records[id_counter].name = (char *)malloc(strlen(allQ[i].R)+1);
								records[id_counter].type = (char *)malloc(strlen(type)+1);
								strcpy(records[id_counter].name, allQ[i].R);
								strcpy(records[id_counter].type, type);
								id_counter++;
								// define the variable
								fprintf(file, "\t%s %s %s %s;\n", type, allQ[i].R, allQ[i].Op, allQ[i].A1);
								printf("\t%s %s %s %s;\n", type, allQ[i].R, allQ[i].Op, allQ[i].A1);
							}	
						}
						else{
							char* type;
							if(find_id_data_type(allQ[i].A1)){
								type = find_id_data_type(allQ[i].A1);
							}
							// create a record for left id if it is not existed 
							if(find_id_data_type(allQ[i].R)){
								// reassign the variable
								fprintf(file, "\t%s = %s %s %s;\n", allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
								printf("\t%s  = %s %s %s;\n", allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
							}
							else{
								// printf("[DEBUG] saving into table");
								record lr;
								lr.name = allQ[i].R;
								lr.type = type;
								records[id_counter] = lr;
								id_counter++;
								// define the variable
								fprintf(file, "\t%s %s = %s %s %s;\n", type, allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
								printf("\t%s %s  = %s %s %s;\n", type, allQ[i].R, allQ[i].A1, allQ[i].Op, allQ[i].A2);
							}
						}
					}
				}
				
			}
				
		}

		fprintf(file, "}\n");
		fclose(file);
		printf("}\n");
		printf("\n--------------------------------------------------------------------------\n");
	}
	
	void freeAll()
	{		
		printf("\n------------------------After Dead Code Elimination ----------------------\n");
		deadCodeElimination();
		printQuads();
		generateCCode();
		printf("\n");
		int i = 0, j = 0;
		for(i=0; i<=sIndex; i++)
		{
			for(j=0; j<symbolTables[i].noOfElems; j++)
			{
				free(symbolTables[i].Elements[j].name);
				free(symbolTables[i].Elements[j].type);	
			}
			free(symbolTables[i].Elements);
		}
		free(symbolTables);
		free(allQ);
	}


/* Line 189 of yacc.c  */
#line 1091 "grammar.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_EndOfFile = 258,
     T_Return = 259,
     T_Number = 260,
     T_True = 261,
     T_False = 262,
     T_ID = 263,
     T_Print = 264,
     T_Range = 265,
     T_Cln = 266,
     T_NL = 267,
     T_EQL = 268,
     T_NEQ = 269,
     T_EQ = 270,
     T_GT = 271,
     T_LT = 272,
     T_EGT = 273,
     T_ELT = 274,
     T_Or = 275,
     T_And = 276,
     T_Not = 277,
     T_In = 278,
     ID = 279,
     ND = 280,
     DD = 281,
     T_String = 282,
     T_If = 283,
     T_Elif = 284,
     T_While = 285,
     T_For = 286,
     T_Else = 287,
     T_Break = 288,
     T_MN = 289,
     T_PL = 290,
     T_DV = 291,
     T_ML = 292,
     T_OP = 293,
     T_CP = 294,
     T_OB = 295,
     T_CB = 296,
     T_Def = 297,
     T_Comma = 298,
     T_List = 299
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 1018 "grammar.y"
 char *text; int depth; int scope_depth; struct ASTNode* node;


/* Line 214 of yacc.c  */
#line 1175 "grammar.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 1200 "grammar.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
	     && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   207

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  65
/* YYNRULES -- Number of states.  */
#define YYNSTATES  122

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   299

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     4,     8,    10,    12,    14,    17,    18,
      23,    26,    28,    30,    32,    34,    36,    38,    42,    46,
      50,    54,    57,    61,    65,    69,    73,    77,    81,    85,
      87,    89,    93,    95,    97,   100,   104,   106,   110,   114,
     119,   121,   123,   126,   128,   130,   132,   137,   143,   145,
     151,   155,   160,   162,   166,   172,   182,   184,   185,   190,
     194,   197,   198,   202,   203,   206
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      46,     0,    -1,    -1,    47,    50,     3,    -1,     5,    -1,
       8,    -1,    48,    -1,    12,    50,    -1,    -1,    60,    12,
      51,    50,    -1,    60,    12,    -1,    57,    -1,    58,    -1,
      53,    -1,    54,    -1,    59,    -1,    49,    -1,    53,    35,
      53,    -1,    53,    34,    53,    -1,    53,    37,    53,    -1,
      53,    36,    53,    -1,    34,    53,    -1,    38,    53,    39,
      -1,    55,    20,    55,    -1,    53,    17,    53,    -1,    55,
      21,    55,    -1,    53,    16,    53,    -1,    53,    19,    53,
      -1,    53,    18,    53,    -1,    55,    -1,    56,    -1,    53,
      15,    53,    -1,     6,    -1,     7,    -1,    22,    56,    -1,
      38,    54,    39,    -1,    33,    -1,     8,    13,    53,    -1,
       8,    13,    54,    -1,     9,    38,    49,    39,    -1,    52,
      -1,    61,    -1,     1,    12,    -1,    62,    -1,    65,    -1,
      67,    -1,    28,    54,    11,    68,    -1,    28,    54,    11,
      68,    63,    -1,    64,    -1,    29,    54,    11,    68,    63,
      -1,    32,    11,    68,    -1,    30,    54,    11,    68,    -1,
      49,    -1,    49,    43,    49,    -1,    49,    43,    49,    43,
      49,    -1,    31,     8,    23,    10,    38,    66,    39,    11,
      68,    -1,    52,    -1,    -1,    12,    69,    60,    70,    -1,
      12,    60,    70,    -1,    12,    71,    -1,    -1,    41,    72,
      60,    -1,    -1,    41,    73,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,  1034,  1034,  1034,  1037,  1039,  1040,  1044,  1044,  1044,
    1044,  1046,  1047,  1048,  1049,  1050,  1052,  1053,  1054,  1055,
    1056,  1057,  1058,  1061,  1062,  1063,  1064,  1065,  1066,  1067,
    1069,  1070,  1071,  1072,  1074,  1075,  1077,  1079,  1080,  1082,
    1084,  1085,  1086,  1088,  1089,  1090,  1093,  1094,  1096,  1097,
    1099,  1101,  1103,  1104,  1105,  1107,  1113,  1114,  1114,  1117,
    1118,  1120,  1120,  1121,  1121,  1122
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_EndOfFile", "T_Return", "T_Number",
  "T_True", "T_False", "T_ID", "T_Print", "T_Range", "T_Cln", "T_NL",
  "T_EQL", "T_NEQ", "T_EQ", "T_GT", "T_LT", "T_EGT", "T_ELT", "T_Or",
  "T_And", "T_Not", "T_In", "ID", "ND", "DD", "T_String", "T_If", "T_Elif",
  "T_While", "T_For", "T_Else", "T_Break", "T_MN", "T_PL", "T_DV", "T_ML",
  "T_OP", "T_CP", "T_OB", "T_CB", "T_Def", "T_Comma", "T_List", "$accept",
  "StartDebugger", "$@1", "constant", "term", "StartParse", "$@2",
  "basic_stmt", "arith_exp", "bool_exp", "bool_term", "bool_factor",
  "break_stmt", "assign_stmt", "print_stmt", "finalStatements",
  "cmpd_stmt", "if_stmt", "elif_stmts", "else_stmt", "while_stmt",
  "myrange", "for_stmt", "start_suite", "$@3", "suite", "end_suite", "$@4",
  "$@5", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    47,    46,    48,    49,    49,    50,    51,    50,
      50,    52,    52,    52,    52,    52,    53,    53,    53,    53,
      53,    53,    53,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    56,    56,    57,    58,    58,    59,
      60,    60,    60,    61,    61,    61,    62,    62,    63,    63,
      64,    65,    66,    66,    66,    67,    68,    69,    68,    70,
      70,    72,    71,    73,    71,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     0,     3,     1,     1,     1,     2,     0,     4,
       2,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     3,     1,     1,     2,     3,     1,     3,     3,     4,
       1,     1,     2,     1,     1,     1,     4,     5,     1,     5,
       3,     4,     1,     3,     5,     9,     1,     0,     4,     3,
       2,     0,     3,     0,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     4,    32,    33,     5,     0,
       0,     0,     0,     0,     0,    36,     0,     0,     6,    16,
       0,    40,    13,    14,    29,    30,    11,    12,    15,     0,
      41,    43,    44,    45,    42,     0,     0,     7,     0,    34,
       5,     0,     0,     0,     0,     0,    21,     0,     0,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     8,    37,    38,     0,     0,     0,     0,     0,    22,
      35,    31,    26,    24,    28,    27,    18,    17,    20,    19,
       0,    23,    25,     0,    39,    57,    56,    46,    51,     0,
       9,     0,     0,     0,    47,    48,     0,     0,     0,     0,
      52,     0,     0,    58,     0,    50,     0,     0,    61,     0,
      60,     0,    53,     0,     0,    64,    59,    49,     0,    55,
      62,    54
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    18,    19,    20,    83,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    94,    95,
      32,   101,    33,    87,    91,   103,   110,   114,   115
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -50
static const yytype_int16 yypact[] =
{
     -50,    21,   104,   -50,    11,   -50,   -50,   -50,    44,    23,
     104,    -2,    84,    84,    54,   -50,    20,    84,   -50,   -50,
      60,   -50,   164,   -50,    17,   -50,   -50,   -50,   -50,    56,
     -50,   -50,   -50,   -50,   -50,    84,    14,   -50,    84,   -50,
     -50,   164,    82,    90,    79,    20,   -27,    -4,    38,   -50,
      20,    20,    20,    20,    20,    20,    20,    20,    20,    84,
      84,   100,   164,   -50,    69,   156,   156,   105,   168,   -50,
     -50,    50,    50,    50,    50,    50,   -27,   -27,   -50,   -50,
     136,   -50,   -50,   104,   -50,   -50,   -50,    37,   -50,    76,
     -50,   122,    84,   106,   -50,   -50,    14,   107,   109,   156,
      78,    85,    66,   -50,   156,   -50,    14,   128,    47,   107,
     -50,    37,    97,   156,   122,   -50,   -50,   -50,    14,   -50,
     -50,   -50
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -50,   -50,   -50,   -50,   -36,    -3,   -50,   -49,   -11,    -9,
      -7,   130,   -50,   -50,   -50,    34,   -50,   -50,    22,   -50,
     -50,   -50,   -50,   -48,   -50,    36,   -50,   -50,   -50
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -66
static const yytype_int8 yytable[] =
{
      64,    41,    41,    42,    43,    46,    47,    37,    48,    57,
      58,    50,    51,    52,    53,    54,    86,    86,    88,     5,
      11,     3,    40,    34,    62,     5,    63,    41,    40,    48,
      55,    56,    57,    58,    68,    69,    38,    59,    60,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    80,
      86,   105,    81,    82,    16,    86,   111,    35,    45,   -63,
     100,    36,    44,    49,    86,   119,    92,     4,    61,    93,
     112,     5,     6,     7,     8,     9,   -63,    70,   -65,   -63,
      90,    41,   121,    98,    55,    56,    57,    58,    11,     5,
       6,     7,    40,    65,    12,   -65,    13,    14,   -65,    15,
      16,    66,    67,   -10,    17,     4,    11,   108,    84,     5,
       6,     7,     8,     9,    96,    89,    10,    99,    16,   102,
     104,   106,    17,     4,   107,    97,    11,     5,     6,     7,
       8,     9,    12,   117,    13,    14,   109,    15,    16,   113,
     118,    39,    17,     0,    11,   116,     0,     0,   120,     0,
      12,    50,    13,    14,     0,    15,    16,     0,     0,     0,
      17,     5,     6,     7,     8,     9,     0,     0,    85,     0,
      55,    56,    57,    58,     0,     0,     0,     0,    11,    50,
      51,    52,    53,    54,     0,     0,     0,     0,     0,    15,
      16,     0,     0,     0,    17,     0,     0,     0,    55,    56,
      57,    58,    55,    56,    57,    58,     0,    69
};

static const yytype_int8 yycheck[] =
{
      36,    12,    13,    12,    13,    16,    17,    10,    17,    36,
      37,    15,    16,    17,    18,    19,    65,    66,    66,     5,
      22,     0,     8,    12,    35,     5,    35,    38,     8,    38,
      34,    35,    36,    37,    45,    39,    38,    20,    21,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      99,    99,    59,    60,    34,   104,   104,    13,    38,    12,
      96,    38,     8,     3,   113,   113,    29,     1,    12,    32,
     106,     5,     6,     7,     8,     9,    29,    39,    12,    32,
      83,    92,   118,    92,    34,    35,    36,    37,    22,     5,
       6,     7,     8,    11,    28,    29,    30,    31,    32,    33,
      34,    11,    23,     3,    38,     1,    22,    41,    39,     5,
       6,     7,     8,     9,    38,    10,    12,    11,    34,    12,
      11,    43,    38,     1,    39,    91,    22,     5,     6,     7,
       8,     9,    28,   111,    30,    31,   102,    33,    34,    11,
      43,    11,    38,    -1,    22,   109,    -1,    -1,   114,    -1,
      28,    15,    30,    31,    -1,    33,    34,    -1,    -1,    -1,
      38,     5,     6,     7,     8,     9,    -1,    -1,    12,    -1,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    22,    15,
      16,    17,    18,    19,    -1,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    38,    -1,    -1,    -1,    34,    35,
      36,    37,    34,    35,    36,    37,    -1,    39
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    46,    47,     0,     1,     5,     6,     7,     8,     9,
      12,    22,    28,    30,    31,    33,    34,    38,    48,    49,
      50,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    65,    67,    12,    13,    38,    50,    38,    56,
       8,    53,    54,    54,     8,    38,    53,    53,    54,     3,
      15,    16,    17,    18,    19,    34,    35,    36,    37,    20,
      21,    12,    53,    54,    49,    11,    11,    23,    53,    39,
      39,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    55,    55,    51,    39,    12,    52,    68,    68,    10,
      50,    69,    29,    32,    63,    64,    38,    60,    54,    11,
      49,    66,    12,    70,    11,    68,    43,    39,    41,    60,
      71,    68,    49,    11,    72,    73,    70,    63,    43,    68,
      60,    49
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (yylocationp);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, yylocationp)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    YYLTYPE const * const yylocationp;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yylsp, yyrule)
    YYSTYPE *yyvsp;
    YYLTYPE *yylsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       , &(yylsp[(yyi + 1) - (yynrhs)])		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, yylsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, yylocationp)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Location data for the lookahead symbol.  */
YYLTYPE yylloc;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.
       `yyls': related to locations.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[2];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;
  yylsp = yyls;

#if YYLTYPE_IS_TRIVIAL
  /* Initialize the default location before parsing starts.  */
  yylloc.first_line   = yylloc.last_line   = 1;
  yylloc.first_column = yylloc.last_column = 1;
#endif

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;
	YYLTYPE *yyls1 = yyls;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);

	yyls = yyls1;
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
	YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;
  *++yylsp = yylloc;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 1034 "grammar.y"
    {init();;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 1034 "grammar.y"
    {printf("\nValid Python Syntax\n"); printAST((yyvsp[(2) - (3)].node));
 				codeGenOp((yyvsp[(2) - (3)].node)); printQuads(); printSTable(); freeAll(); exit(0);;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 1037 "grammar.y"
    {insertRecord("Constant", (yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", (yyvsp[(1) - (1)].text), currentScope);;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 1039 "grammar.y"
    {modifyRecordID("Identifier", (yyvsp[(1) - (1)].text), (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Identifier", (yyvsp[(1) - (1)].text), currentScope);;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 1040 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 1044 "grammar.y"
    {(yyval.node)=(yyvsp[(2) - (2)].node);;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 1044 "grammar.y"
    {resetDepth();;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 1044 "grammar.y"
    {(yyval.node) = createOp("NewLine", 2, (yyvsp[(1) - (4)].node), (yyvsp[(4) - (4)].node));;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 1044 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (2)].node);;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 1046 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 1047 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 1048 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 1049 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 1050 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 1052 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 1053 "grammar.y"
    {(yyval.node) = createOp("+", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 18:

/* Line 1455 of yacc.c  */
#line 1054 "grammar.y"
    {(yyval.node) = createOp("-", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 1055 "grammar.y"
    {(yyval.node) = createOp("*", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 1056 "grammar.y"
    {(yyval.node) = createOp("/", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 1057 "grammar.y"
    {(yyval.node) = createOp("-", 1, (yyvsp[(2) - (2)].node));;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 1058 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 1061 "grammar.y"
    {(yyval.node) = createOp("or", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 1062 "grammar.y"
    {(yyval.node) = createOp("<", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 1063 "grammar.y"
    {(yyval.node) = createOp("and", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 1064 "grammar.y"
    {(yyval.node) = createOp(">", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 1065 "grammar.y"
    {(yyval.node) = createOp("<=", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 1066 "grammar.y"
    {(yyval.node) = createOp(">=", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 1067 "grammar.y"
    {(yyval.node)=(yyvsp[(1) - (1)].node);;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 1069 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 1070 "grammar.y"
    {(yyval.node) = createOp("==", 2, (yyvsp[(1) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 1071 "grammar.y"
    {insertRecord("Constant", "True", (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "True", currentScope);;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 1072 "grammar.y"
    {insertRecord("Constant", "False", (yylsp[(1) - (1)]).first_line, currentScope); (yyval.node) = createID_Const("Constant", "False", currentScope);;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 1074 "grammar.y"
    {(yyval.node) = createOp("!", 1, (yyvsp[(2) - (2)].node));;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 1075 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (3)].node);;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 1077 "grammar.y"
    {(yyval.node) = createOp("break", 0);;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 1079 "grammar.y"
    {insertRecord("Identifier", (yyvsp[(1) - (3)].text), (yylsp[(1) - (3)]).first_line, currentScope); (yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[(1) - (3)].text), currentScope), (yyvsp[(3) - (3)].node));;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 1080 "grammar.y"
    {insertRecord("Identifier", (yyvsp[(1) - (3)].text), (yylsp[(1) - (3)]).first_line, currentScope);(yyval.node) = createOp("=", 2, createID_Const("Identifier", (yyvsp[(1) - (3)].text), currentScope), (yyvsp[(3) - (3)].node));;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 1082 "grammar.y"
    {(yyval.node) = createOp("Print", 1, (yyvsp[(3) - (4)].node));;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 1084 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 1085 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 1086 "grammar.y"
    {yyerrok; yyclearin; (yyval.node)=createOp("SyntaxError", 0);;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 1088 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 1089 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 1090 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 1093 "grammar.y"
    {(yyval.node) = createOp("If", 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 1094 "grammar.y"
    {(yyval.node) = createOp("If", 3, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 1096 "grammar.y"
    {(yyval.node)= (yyvsp[(1) - (1)].node);;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 1097 "grammar.y"
    {(yyval.node)= createOp("Elif", 3, (yyvsp[(2) - (5)].node), (yyvsp[(4) - (5)].node), (yyvsp[(5) - (5)].node));;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 1099 "grammar.y"
    {(yyval.node) = createOp("Else", 1, (yyvsp[(3) - (3)].node));;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 1101 "grammar.y"
    {(yyval.node) = createOp("While", 2, (yyvsp[(2) - (4)].node), (yyvsp[(4) - (4)].node));;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 1107 "grammar.y"
    {node* bool_node;bool_node=(node*)calloc(1, sizeof(node));
																		insertRecord("Identifier", (yyvsp[(2) - (9)].text), (yylsp[(1) - (9)]).first_line, currentScope);
																		node* id = createID_Const("Identifier", (yyvsp[(2) - (9)].text), currentScope);
																		bool_node=createOp("<", 2, id, (yyvsp[(6) - (9)].node));
																		(yyval.node) = createOp("For", 4, createOp("<", 2, id, (yyvsp[(6) - (9)].node)), id, (yyvsp[(6) - (9)].node), (yyvsp[(9) - (9)].node));;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 1113 "grammar.y"
    {(yyval.node) = (yyvsp[(1) - (1)].node);;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 1114 "grammar.y"
    {initNewTable(scope_depth); updateCScope(scope_depth);;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 1114 "grammar.y"
    {(yyval.node) = createOp("BeginBlock", 2, (yyvsp[(3) - (4)].node), (yyvsp[(4) - (4)].node));;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 1117 "grammar.y"
    {(yyval.node) = createOp("Next", 2, (yyvsp[(2) - (3)].node), (yyvsp[(3) - (3)].node));;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 1118 "grammar.y"
    {(yyval.node) = (yyvsp[(2) - (2)].node);;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 1120 "grammar.y"
    {updateCScope(scope_depth);;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 1120 "grammar.y"
    {(yyval.node) = createOp("EndBlock", 1, (yyvsp[(3) - (3)].node));;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 1121 "grammar.y"
    {updateCScope(scope_depth);;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 1121 "grammar.y"
    {(yyval.node) = createOp("EndBlock", 0);;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 1122 "grammar.y"
    {(yyval.node) = createOp("EndBlock", 0); resetDepth();;}
    break;



/* Line 1455 of yacc.c  */
#line 2988 "grammar.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }

  yyerror_range[0] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, &yylloc);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[0] = yylsp[1-yylen];
  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      yyerror_range[0] = *yylsp;
      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;

  yyerror_range[1] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, (yyerror_range - 1), 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, &yylloc);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 1125 "grammar.y"




int main()
{
	//printf("Enter the Expression\n");
	yyparse();
	return 0;
}

