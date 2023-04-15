#include <iostream>
#include<fstream>
#include "AST.h"
using std::cout;
using std::endl;
using std::ofstream;
extern int yylex();
extern int yyerror(const char *s1);
extern int yydebug;
extern int yyparse();
extern bool symanticerror;
extern Class * root;
extern SymbolTable * symbolTable;
ofstream vcode("vm.txt");


int main()
{
	yydebug = 0;
	yyparse();
	root;
	Visitor * printvisitor = new PrintVisitor;
	Visitor * type = new TypeChecker;
	
	//root->accept(printvisitor);
	root->accept(type);
	if (symanticerror) {
		symbolTable->errors->Print();
		cout << "Fix the errors to generate the code"<<endl;
	}
	else {
		symbolTable->errors->Print();
		Visitor * code = new CodeGeneration;
		root->accept(code);
	}
	cout << "parsing done" << endl;
	return 0;

}