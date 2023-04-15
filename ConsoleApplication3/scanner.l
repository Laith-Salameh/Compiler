%{
	#include "AST.h"
	#include <iostream>
	using std::cout;
	using std::endl;
	#include "parser.h"
	int line=1;
	int col=1;
	int errorno=0;
%}

%x comment
%option noyywrap
%%
"/*"								{BEGIN(comment); col += yyleng;}
<comment>"*/"						{BEGIN(0); col += yyleng;}
<comment>[^\n\t]?					{col+=yyleng;}
<comment>\n							{line++; col = 1;}
<comment>\t							{col+=4*yyleng;}

[\t]*	{
						col += 4*yyleng;
						}
[ ]*	{
						col += yyleng;
						}
[\n]	{
						col =1;
						line++;
						}

[/][/][^\n]*\n {
						line++;
						col = 1;
						}


						 
"while" {
		col += yyleng;
		return WHILE;
		}
"else" {
		col += yyleng;
		return ELSE;
		}
"if" {
		col += yyleng;
		return IF;
	}
"int" {
		col += yyleng;
		return INT;
		}
"float" {
		col += yyleng;
		return FLOAT;
		}
"bool" {
		col += yyleng;
		return BOOL;
		}
"char" {
		col += yyleng;
		return CHAR;
		}
"string" {
		col += yyleng;
		return STRING;
		}
"break" {
		col += yyleng;
		return BREAK;
		}
"continue" {
		col += yyleng;
		return CONTINUE;
		}
"return" {
		col += yyleng;
		return RT;
		}
"null" {
		col += yyleng;
		return NL;
		}
"true" {
		col += yyleng;
		return TRUE;
		}
"false" {
		col += yyleng;	
		return FALSE;
		}
"==" {
		col += yyleng;
		return EQ;
	}
"&&" {
		col += yyleng;
		return AND;
	}
"||" {
		col += yyleng;
		return OR;
	}
"Class" {
	col += yyleng;
	return CLASS;
	}
"!=" {
	col += yyleng;
	return NEQ;
}

[a-zA-Z_][_a-z0-9A-Z]* {
		col+=yyleng;
		yylval.Tid=new Id(strdup(yytext), line, col);
		return ID;
		}
0|[1-9][0-9]* {
	col+=yyleng;
	yylval.tINTNUM = new Integer_value(atoi(yytext), line, col);
	return INTNUM;
	}

(([0-9]+)[.][0]([eE][0-9]+)?)|(([0-9]+)[.][0-9]*([eE][0-9]+)?)|([.][0-9]+([eE][0-9]+)?) {
	col+=yyleng;
	yylval.tFLOATNUM = new Real_value(atof(yytext), line, col);
	return FLOATNUM;
}
 

"\'"[^\n\t]"\'" {
		col+=yyleng;
		yylval.tCHARCONST = new Char_value( yytext[0]  ,line , col );
		return CHARCONST;
		}
"\""[^\n\t]*"\"" {
		col+=yyleng;
		return STRINGCONST;
		}


[-(),{}=;?:!+*/<>\[\]\%]  {
				col+=yyleng;
				return *yytext;
				}

. {
	col += yyleng;
	errorno++;
	cout<<"\n\n_________________________Parser Error_________________________"<<endl;
	cout<<"Error Number: " <<errorno<<" "<<*yytext<<endl;
	cout<<"input.txt, Line: "<<line <<" , col: "<<col<<endl;
	cout<<"Lexical Error"<<endl;
	}

%%

