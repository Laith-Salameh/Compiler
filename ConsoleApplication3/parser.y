%{
	#include "AST.h"
	#include <iostream>
	using std::cout;
	using std::endl;
	extern int yylex();
	extern int line,col;
	int yyerror(const char *s1);
	extern int yydebug;
	Class * root;
	extern char* yytext;
	SymbolTable * symbolTable = new SymbolTable();
	int current_type;
	int current_kind = 2;
	int last_func = 0 ;
	int whileLabel = 0;
	int ifLabel = 0;
	int ifElseLabel = 0;
	int forLabel=0;

%}

%union{
Class * tClass;
Small * tSmall;
Func * tfunc;
Type * ttype_specifier;
Decl_List * tdecl_list;
Param_Decl * tParam_decl;
Comp * tcomp;
Var_Decl * tvar_decl;
Var_Decl_List * tvar_decl_list;
Variable_Id * tvariable_id;
Stmt * tstmt;
Expr * texpr;
Expr_List * texprList;
int toperator;
Primary * tprimary;
Id * Tid;
Integer_value * tINTNUM;
Real_value * tFLOATNUM;
Char_value  * tCHARCONST;
}


%type <tClass> Class
%type <tSmall> Small
%type <tfunc> func
%type <ttype_specifier> type_specifier 
%type <tdecl_list> decl_list decl_list_e
%type <tParam_decl> Param_decl
%type <tcomp> comp
%type <tvar_decl> var_decl
%type <tvar_decl_list> var_decl_list
%type <tvariable_id> variable_id
%type <tstmt> stmt cond_stmt while_stmt assignStmt
%type <texpr> expr
%type <texprList> exprList exprList_e
%type <toperator> operator
%type <tprimary> primary 



%debug
%token WHILE IF ELSE INT FLOAT CHAR STRING BOOL BREAK
%token CONTINUE RT NL TRUE FALSE EQ NEQ AND OR 
%token <tINTNUM> INTNUM 
%token <tFLOATNUM> FLOATNUM
%token <Tid> ID
%token <tCHARCONST> CHARCONST
%token  STRINGCONST CLASS





%nonassoc IF_PREC
%nonassoc ELSE


%right '='

%left OR
%left AND
%nonassoc  EQ  NEQ  
%nonassoc '<' '>' 
%left '-' '+'
%left '*' '/' '%'

%left OP
%left eoe


%start Class
%%
Class: CLASS 
			{ 
				symbolTable->OpenScope();
				ReadWrite::ReadWriteAdd();
			} ID {
					symbolTable->AddSymbol($3 , 4  ,  6 );
				 }'{' Small '}' 
						{
							$$ = new Class( $3 , $6 , line , col);
							root = $$;
							//symbolTable->CloseScope();
						}
						;

Small : 
		{
			$$ = new Small(line , col );
		}
	  |Small func
				{
					$$ =  new Func_Small( $1 , $2 , line , col);
				}
      | Small var_decl
	   {
		$$ =  new Var_Small( $1 , $2 , line , col);
	   }
	   ;

func : type_specifier ID {		
							symbolTable->OpenScope();
							current_kind = 3;
							
							last_func = $1->type;
						  }'(' decl_list ')' '{' comp  '}' 
										{
											
											$$ = new Func( $1 , $2 , $5 , $8 , line, col );
											symbolTable->CloseScope();
											current_kind = 2;
											symbolTable->AddFunc($2 , 1 , $5 , $1->type , $$ );
										}
	| ID {
				symbolTable->OpenScope();
				current_kind = 3;
				symbolTable->LookupConstructor($1 );
			}'(' decl_list ')' '{' comp  '}' /* constructor */
						{
							$$ = new Constructor( $1 , $4 , $7 , line , col );
							symbolTable->CloseScope();
							last_func = 0;
						}
						;
	  

type_specifier : INT
					{
						$$ =  new Type( 1 , line , col );
						current_type= 1;
					
					}
				 | FLOAT
					{
						$$ =  new Type( 2 , line , col );
						current_type= 2;
					} 
				| BOOL
					{
						$$ =  new Type( 3 , line , col );
						current_type= 3;
					}
				| CHAR 
					{
						$$ =  new Type( 4 , line , col );
						current_type= 4;
					}
				| STRING   
					{
						$$ =  new Type( 5 , line , col );
						current_type= 5;
					}
					;


decl_list :  
				{
					$$ = new Decl_List(line , col);
				}
			 |decl_list_e 
				{
					$$ = $1;
				}
				;
			  
decl_list_e: decl_list_e ',' Param_decl 
				{
					$1->AddParam($3);
					$$ = $1;
				}  
			 | Param_decl 
				{
					$$ = new Decl_List( $1 ,line , col);

				}
				;

Param_decl : type_specifier ID 
				{
					$$ = new Param_Decl($1 , $2 , line , col);
					symbolTable->AddSymbol($2 , 3  , $1->type );
				}
				;

comp: comp var_decl 
			{
				$$= new Var_Comp($1 , $2 , line , col);
			}
       | comp stmt 
			{
				$$= new Stmt_Comp($1 , $2 , line , col);
			}
	   |
			{
				$$= new Comp(line , col);
			}
			;


var_decl : type_specifier  var_decl_list ';' 
							{
								$$= new Var_Decl( $1 , $2 , line , col);
				
							}
			;

var_decl_list :  var_decl_list ',' variable_id 
						{
							$1->AddVar($3);
							$$ = $1;
						} 
                  | variable_id
						{
							$$ = new Var_Decl_List($1 , line , col);
						}
						;

variable_id : ID 
				{
					$$ = new Var_Id($1 , line , col);
					symbolTable->AddSymbol($1 , current_kind  , current_type );
				}
              | ID '=' expr
				{
					$$ = new Var_Id_Exp( $1 , $3 , line , col);
					symbolTable->AddSymbol($1 , current_kind  , current_type );
				}
			    ;

stmt :      cond_stmt 
				{
					$$ = $1;
				}
		  | while_stmt
				{
					$$ = $1;
				} 
		  | BREAK ';'
				{
					$$ = new Break(line , col );
				} 
		  | assignStmt ';'
				{
					$$ = $1;
				} 
		  | CONTINUE ';'
				{
					$$ = new Continue(line , col);
				} 
		  | RT expr ';'
				{
					$$ = new RT_expr($2,last_func, line , col ) ;
						
				}
		 | expr ';'
		 {
					$$ = new Stmt_expr( $1 , line , col );
		 }
				;

cond_stmt : IF '(' expr ')' '{' comp '}' %prec IF_PREC
					{
						$$ = new If($3 , $6 , line , col);
					}
            | IF '(' expr ')' '{' comp '}' ELSE '{' comp '}' 
					{
						$$ = new If_Else($3 , $6 , $10 , line , col);
					}
					;

while_stmt : WHILE '(' expr ')' '{' comp '}'
				{
				   $$ = new While_Stmt( $3 , $6 , line , col);
				}
				;

assignStmt : ID '=' expr 
			{
				$$ = new assignStmt( $1 , $3 , line , col);
				symbolTable->LookUp($1 );
			}
			;
             
expr : primary 
		{
			$$ = $1;
		}
| expr operator expr %prec eoe
		{
			$$ = new Expr_op_Expr( $1 , $2 , $3 , line , col);
		}
| '!' expr %prec OP
		{
			$$ = new Ex_Expr( $2 , line , col);
		}
| '(' expr ')'
		{
			$$ = new ParenthesesExpr($2 , line , col);
		}
| '-' expr %prec OP
		{
			$$ = new MinusExpr($2 , line , col);
		}
| '+' expr  %prec OP
		{
			$$ = new PlusExpr($2 , line , col);
		}
| ID '(' exprList ')' 
		{
			$$ = new Id_Expr_list( $1 , $3 , line , col);
			//symbolTable->LookupFunction($1 );
		}
		;

exprList :   
				{
					$$ = new Expr_List(line , col );
				}
            | exprList_e
					{
						$$ = $1;
					}
					;  
			
exprList_e : expr
				{
					$$ = new Expr_List($1, line , col);
				}
			| exprList_e ',' expr
				{
				  $1->addExpression($3);
				  $$ = $1;
				}
				;

operator :	  '+'
				{
					$$ = 1;
				}
			| '-' 
				{
					$$ = 2;
				}
			| '*'
				{
					$$ = 3;
				} 
			| '/'
				{
					$$ = 4;
				} 
			| '%'
				{
					$$ = 5;
				} 
			| '>'
				{
					$$ = 6;
				} 
			| '<'
				{
					$$ = 7;
				} 
			| EQ
				{
					$$ = 8;
				} 
			| AND
				{
					$$ = 9;
				} 
			| OR 
				{
					$$ = 10;
				}
			| NEQ
				{
					$$ = 11;
				}
				;

primary :	  INTNUM
				{
				$$= $1;
				}
			| FLOATNUM 
				{
				$$= $1;
				}
			| CHARCONST 
				{
				$$= $1;
				}
			| STRINGCONST
				{
				$$= new String_value(strdup(yytext),line,col);
				} 
			| ID
				{
				$$ = new Primary_ID($1 , line , col);
				symbolTable->LookUp($1);
				} 
			| TRUE
				{
				$$ = new True_value(line,col);
				} 
			| FALSE
				{
				$$ = new False_value(line,col);
				} 
			| NL
				{
				$$= new Null_value(line,col);
				}
				;
%%

int yyerror(const char *s1){
cout << "Parsing Error !!! in line= " <<line <<"and col= " <<col <<endl;
return 1;
}

