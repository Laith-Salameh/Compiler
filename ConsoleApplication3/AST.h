#pragma once
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "hash_fun.h"
#include "hash_table.h"
#include "ast.h"

using std::string;
using std::vector;

class Symbol;
class SymbolTable;
class Small;
class Class;
class Func;
class Var_Small;
class Func_Small;
class Var_Decl;
class Var_Decl_List;
class Id;
class Type;
class Decl_List;
class Comp;
class Param_Decl;
class Stmt;
class Variable_Id;
class Expr;
class Visitor;
class Node;

typedef CHashTable<Symbol> HashTab;

class Node
{
public:
	int line;
	int column;
	Node *father;
	Node(int, int);
	void setFather(Node *, Node *);
	virtual void accept(Visitor *);
};

class Error : public Node
{
public:
	string message;
	Error(string message, int, int);
};

class Errors
{
public:
	vector<Error *> *errorLists;
	Errors();
	void AddError(string message, int line, int column);
	void Print();
};

class Symbol
{
public:
	string name;
	int type; 
	int kind;
	int location;
	Func * function;
	Symbol(string, int, int);
	Symbol(string, int, int , Func *);
};



class Scope
{
public:
	HashTab	*hashTab;
	Scope();
};

class SymbolTable
{
public:
	HashTab *hashTab ;
	vector<Scope *> * scopes;
	string kindes[15];
	string types[15];
	Scope * current;
	Errors * errors;
	SymbolTable();
	bool AddSymbol(Id *, int, int);
	bool AddFunc(Id * id, int kind, Decl_List * d, int type , Func *);
	Symbol * LookUp(Id * );
	Symbol * LookupConstructor(Id *);
	void CloseScope();
	void OpenScope();
};






class Class : public Node
{
public:
	Id *name;
	Small *small;
	Class(Id*, Small*, int, int);
	virtual void accept(Visitor *);
};

class Small : public Node
{
public:
	Small(int line , int col ) :Node(line, col){};
	virtual void accept(Visitor *);
};

class Func_Small : public Small
{
public:
	Small* small;
	Func*  func;
	Func_Small(Small*, Func*, int, int);
	virtual void accept(Visitor *);
};

class Var_Small : public Small
{
public:
	Small* small;
	Var_Decl* var_decl; 
	Var_Small(Small*, Var_Decl*, int, int);
	virtual void accept(Visitor *);
};

class Func : public Node
{
public:
	Type *type;
	Id *name;
	Decl_List * args;
	Comp * comp;
	bool CG_visited;
	Func(int l, int c) : Node(l, c) {}
	Func(Type *, Id *, Decl_List *, Comp *, int, int);
	virtual void accept(Visitor *);
};

class Constructor : public Func
{
public:
	Id *name;
	Decl_List * args;
	Comp * comp;
	Constructor( Id *, Decl_List *, Comp *, int, int);
	virtual void accept(Visitor *);
};

class Type : public Node
{
public:
	int type;// 1: int, 2: float , 3: bool , 4 : char , 5 : string , 6 : function
	Type(int, int, int);
	virtual void accept(Visitor *);
};
class Id : public Node
{
public:
	string name;
	Symbol *symbol;
	Id(string, int, int);
	virtual void accept(Visitor *);
};
class Param_Decl :public Node
{
public:
	Type *type;
	Id *name;
	Param_Decl(Type *, Id *, int, int);
	virtual void accept(Visitor *);
};
class Decl_List : public Node
{
public:
	vector<Param_Decl *> *params;
	Decl_List(int l, int c) : Node(l, c) {
		this->params = new vector< Param_Decl * >;
	}
	Decl_List( Param_Decl *, int, int);
	void AddParam(Param_Decl *);
	virtual void accept(Visitor *);
};

class Comp : public Node
{
public:
	int return_type = 10;
	Comp(int line, int col) :Node(line, col) {};
	virtual void accept(Visitor *);
};

class Stmt_Comp : public Comp
{
public:
	Comp* comp;
	Stmt*  stmt;
	Stmt_Comp(Comp*, Stmt*, int, int);
	virtual void accept(Visitor *);
};

class Var_Comp : public Comp
{
public:
	Comp* comp;
	Var_Decl* var_decl;
	Var_Comp(Comp*, Var_Decl*, int, int);
	virtual void accept(Visitor *);
};

class Var_Decl : public Node
{
public:
	Type* type;
	Var_Decl_List *var_decl_list;
	Var_Decl(Type *, Var_Decl_List *, int, int);
	virtual void accept(Visitor *);
};

class Var_Decl_List : public Node
{
public:
	vector< Variable_Id *> *vars;
	Var_Decl_List(int l, int c) : Node(l, c)
	{
		this->vars = new vector< Variable_Id * >;
	} 
	Var_Decl_List(Variable_Id *, int, int);
	void AddVar(Variable_Id *);
	virtual void accept(Visitor *);
};

class Variable_Id : public Node
{
public:
	Variable_Id(int line, int col) : Node(line, col) {}
	virtual void accept(Visitor *);
};

class Var_Id : public Variable_Id
{
public:
	Id* name;
	Var_Id( Id*, int, int);
	virtual void accept(Visitor *);
};

class Var_Id_Exp : public Variable_Id
{
public:
	Id* name;
	Expr* expr;
	Var_Id_Exp( Id*, Expr*, int, int);
	virtual void accept(Visitor *);
};


class Stmt : public Comp
{
public:
	Stmt(int line , int col) : Comp(line,col) {}
	virtual void accept(Visitor *);
};

class While_Stmt : public Stmt
{
public:
	Expr *expr;
	Comp * comp;
	While_Stmt(Expr *, Comp *, int, int);
	virtual void accept(Visitor *);
};
class cond_stmt : public Stmt
{
public:
	cond_stmt(int l, int c) :Stmt(l, c) {}
	virtual void accept(Visitor *);
};
class If : public cond_stmt
{
public:
	Expr *expr;
	Comp * comp;
	If(Expr *, Comp *, int, int);
	virtual void accept(Visitor *);
};

class If_Else : public cond_stmt
{
public:
	Expr *expr;
	Comp * comp_if;
	Comp * comp_else;
	If_Else(Expr *, Comp *, Comp *, int, int);
	virtual void accept(Visitor *);
};

class assignStmt : public Stmt
{
public:
	Id * name;
	Expr *expr;
	assignStmt(Id *, Expr *, int, int);
	virtual void accept(Visitor *);
};
class RT_expr : public Stmt
{
public:
	Expr *expr;
	RT_expr(Expr*, int ,int, int);
	virtual void accept(Visitor *);
};

class Stmt_expr : public Stmt
{
public:
	Expr *expr;
	Stmt_expr(Expr*, int, int);
	virtual void accept(Visitor *);
};

class Break : public Stmt
{
public:
	Break(int line, int col) : Stmt(line, col) {}
	virtual void accept(Visitor *);
};

class Continue : public Stmt
{
public:
	Continue(int line, int col) : Stmt(line, col) {}
	virtual void accept(Visitor *);
};



class Expr : public  Node
{
public:
	int type;
	Expr(int line, int col) :Node(line, col) {}
	virtual void accept(Visitor *);
};

class Expr_List : public  Node
{
public:
	vector <Expr * > *exprs;
	Expr_List(int line, int col) :Node(line, col) {
		this->exprs = new vector< Expr * >;
	}
	Expr_List(Expr *, int, int);
	void addExpression(Expr *);
	virtual void accept(Visitor *);
};

// '!'Expr
class Ex_Expr : public  Expr
{
public:
	Expr *expr;
	Ex_Expr(Expr*, int, int);
	virtual void accept(Visitor *);
};

//'-' Expr
class MinusExpr : public  Expr
{
public:
	Expr *expr;
	MinusExpr(Expr*, int, int);
	virtual void accept(Visitor *);
};



// '+' Expr
class PlusExpr : public  Expr
{
public:
	Expr *expr;
	PlusExpr(Expr*, int, int);
	virtual void accept(Visitor *);
};

//'(' Expr ')'
class ParenthesesExpr : public  Expr
{
public:
	Expr *expr;
	ParenthesesExpr(Expr*, int, int);
	virtual void accept(Visitor *);

};





class Id_Expr_list : public  Expr
{
public:
	Id * name;
	Expr_List * expr_list;
	Func * func;
	Id_Expr_list(Id *, Expr_List*, int, int);
	virtual void accept(Visitor *);
};

class Expr_op_Expr : public  Expr
{
public:
	Expr * left;
	Expr * right;
	int op;
	Func * function;
	Expr_op_Expr(Expr *, int , Expr *, int, int);
	virtual void accept(Visitor *);
};

class Primary : public Expr {
public:
	Primary(int l, int c) : Expr(l, c) {};
	virtual void accept(Visitor *);
};

class Primary_ID : public Primary {
public:
	Id * name;
	Primary_ID(Id * ,int , int ) ;
	virtual void accept(Visitor *);
};


class Integer_value : public  Primary
{
public:
	int value;
	Integer_value(int, int);
	Integer_value(int, int, int);
	virtual void accept(Visitor *);
};

class Real_value : public  Primary
{
public:
	double value;
	Real_value(int, int);
	Real_value(double, int, int);
	virtual void accept(Visitor *);
};

class String_value : public  Primary
{
public:
	string value;
	String_value(int, int);
	String_value(string, int, int);
	virtual void accept(Visitor *);
};
class Char_value : public  Primary
{
public:
	char value;
	Char_value(int, int);
	Char_value(char, int, int);
	virtual void accept(Visitor *);
};

class True_value : public Primary
{
public:
	const bool value = true;
	True_value(int line, int col) : Primary(line, col) {
		this->type = 3;
	}
	virtual void accept(Visitor *);
};

class False_value : public  Primary
{
public:
	const bool value = false;
	False_value(int line, int col) : Primary(line, col) {
		this->type = 3;
	}
	virtual void accept(Visitor *);
};

class Null_value : public Primary
{
public:
	const Expr* exp = NULL;
	Null_value(int, int);
	virtual void accept(Visitor *);
};

/*************************************/
class ReadWrite
{
public:
	static void ReadWriteAdd();
};

/*****************************************************************************************/
class Visitor
{
public:
	virtual void Visit(Node *n) = 0;
	virtual void Visit(Primary *n) = 0;
	virtual void Visit(Id *n) = 0;
	virtual void Visit(Integer_value *n) = 0;
	virtual void Visit(Real_value *n) = 0;
	virtual void Visit(Char_value *n) = 0;
	virtual void Visit(String_value *n) = 0;
	virtual void Visit(True_value *n) = 0;
	virtual void Visit(False_value *n) = 0;
	virtual void Visit(Null_value *n) = 0;
	virtual void Visit(Primary_ID *n) = 0;
	virtual void Visit(Class *n) = 0;
	virtual void Visit(Small *n) = 0;
	virtual void Visit(Func_Small *n) = 0;
	virtual void Visit(Var_Small *n) = 0;
	virtual void Visit(Func *n) = 0;
	virtual void Visit(Constructor *n) = 0;
	virtual void Visit(Type *n) = 0;
	virtual void Visit(Param_Decl *n) = 0;
	virtual void Visit(Decl_List *n) = 0;
	virtual void Visit(Comp *n) = 0;
	virtual void Visit(Stmt_Comp *n) = 0;
	virtual void Visit(Var_Comp *n) = 0;
	virtual void Visit(Var_Decl *n) = 0;
	virtual void Visit(Var_Decl_List *n) = 0;
	virtual void Visit(Variable_Id *n) = 0;
	virtual void Visit(Var_Id *n) = 0;
	virtual void Visit(Var_Id_Exp *n) = 0;
	virtual void Visit(Expr *n) = 0;
	virtual void Visit(Expr_List *n) = 0;
	virtual void Visit(Ex_Expr *n) = 0;
	virtual void Visit(MinusExpr *n) = 0;
	virtual void Visit(PlusExpr *n) = 0;
	virtual void Visit(ParenthesesExpr *n) = 0;
	virtual void Visit( Id_Expr_list *n) = 0;
	virtual void Visit(Expr_op_Expr *n) = 0;
	virtual void Visit(Stmt *n) = 0;
	virtual void Visit(While_Stmt *n) = 0;
	virtual void Visit(cond_stmt *n) = 0;
	virtual void Visit(If *n) = 0;
	virtual void Visit(If_Else *n) = 0;
	virtual void Visit(assignStmt *n) = 0;
	virtual void Visit(RT_expr *n) = 0;
	virtual void Visit(Stmt_expr *n) = 0;
	virtual void Visit(Break *n) = 0;
	virtual void Visit(Continue *n) = 0;

	
};

class PrintVisitor : public Visitor
{

	
public:
	string types[8];
	string operators[16];
	PrintVisitor();
	virtual void Visit(Node *)  ;
	virtual void Visit(Primary *)  ;
	virtual void Visit(Id *)  ;
	virtual void Visit(Integer_value *)  ;
	virtual void Visit(Real_value *)  ;
	virtual void Visit(Char_value *)  ;
	virtual void Visit(String_value *)  ;
	virtual void Visit(True_value *)  ;
	virtual void Visit(False_value *)  ;
	virtual void Visit(Null_value *)  ;
	virtual void Visit(Primary_ID *)  ;
	virtual void Visit(Class *)  ;
	virtual void Visit(Small *)  ;
	virtual void Visit(Func_Small *)  ;
	virtual void Visit(Var_Small *)  ;
	virtual void Visit(Func *)  ;
	virtual void Visit(Constructor *)  ;
	virtual void Visit(Type *)  ;
	virtual void Visit(Param_Decl *)  ;
	virtual void Visit(Decl_List *)  ;
	virtual void Visit(Comp *)  ;
	virtual void Visit(Stmt_Comp *)  ;
	virtual void Visit(Var_Comp *)  ;
	virtual void Visit(Var_Decl *)  ;
	virtual void Visit(Var_Decl_List *)  ;
	virtual void Visit(Variable_Id *)  ;
	virtual void Visit(Var_Id *)  ;
	virtual void Visit(Var_Id_Exp *)  ;
	virtual void Visit(Expr *)  ;
	virtual void Visit(Expr_List *)  ;
	virtual void Visit(Ex_Expr *)  ;
	virtual void Visit(MinusExpr *)  ;
	virtual void Visit(PlusExpr *)  ;
	virtual void Visit(ParenthesesExpr *)  ;
	virtual void Visit(Id_Expr_list *)  ;
	virtual void Visit(Expr_op_Expr *)  ;
	virtual void Visit(Stmt *)  ;
	virtual void Visit(While_Stmt *)  ;
	virtual void Visit(cond_stmt *)  ;
	virtual void Visit(If *)  ;
	virtual void Visit(If_Else *)  ;
	virtual void Visit(assignStmt *)  ;
	virtual void Visit(RT_expr *)  ;
	virtual void Visit(Stmt_expr *);
	virtual void Visit(Break *)  ;
	virtual void Visit(Continue *)  ;
};




class TypeChecker : public Visitor
{


public:
	string types[8];
	string operators[16];
	TypeChecker();
	vector< Func *> *functions;
	virtual void Visit(Node *);
	virtual void Visit(Primary *);
	virtual void Visit(Id *);
	virtual void Visit(Integer_value *);
	virtual void Visit(Real_value *);
	virtual void Visit(Char_value *);
	virtual void Visit(String_value *);
	virtual void Visit(True_value *);
	virtual void Visit(False_value *);
	virtual void Visit(Null_value *);
	virtual void Visit(Primary_ID *);
	virtual void Visit(Class *);
	virtual void Visit(Small *);
	virtual void Visit(Func_Small *);
	virtual void Visit(Var_Small *);
	virtual void Visit(Func *);
	virtual void Visit(Constructor *);
	virtual void Visit(Type *);
	virtual void Visit(Param_Decl *);
	virtual void Visit(Decl_List *);
	virtual void Visit(Comp *);
	virtual void Visit(Stmt_Comp *);
	virtual void Visit(Var_Comp *);
	virtual void Visit(Var_Decl *);
	virtual void Visit(Var_Decl_List *);
	virtual void Visit(Variable_Id *);
	virtual void Visit(Var_Id *);
	virtual void Visit(Var_Id_Exp *);
	virtual void Visit(Expr *);
	virtual void Visit(Expr_List *);
	virtual void Visit(Ex_Expr *);
	virtual void Visit(MinusExpr *);
	virtual void Visit(PlusExpr *);
	virtual void Visit(ParenthesesExpr *);
	virtual void Visit(Id_Expr_list *);
	virtual void Visit(Expr_op_Expr *);
	virtual void Visit(Stmt *);
	virtual void Visit(While_Stmt *);
	virtual void Visit(cond_stmt *);
	virtual void Visit(If *);
	virtual void Visit(If_Else *);
	virtual void Visit(assignStmt *);
	virtual void Visit(RT_expr *);
	virtual void Visit(Stmt_expr *);
	virtual void Visit(Break *);
	virtual void Visit(Continue *);
};








extern int whileLabel;
extern int ifLabel;
extern int ifElseLabel;
extern int ifLabel;
extern int forLabel;





/****************************************CG********************************************************/

class CodeGeneration : public Visitor
{
public:
	int g;
	int f;
	int c;
	string types[8];
	string operators[16];
	vector < Symbol * > * funcs;
	CodeGeneration();
	void generateReadWriteFunction();
	void w(string s);
	virtual void Visit(Node *);
	virtual void Visit(Primary *);
	virtual void Visit(Id *);
	virtual void Visit(Integer_value *);
	virtual void Visit(Real_value *);
	virtual void Visit(Char_value *);
	virtual void Visit(String_value *);
	virtual void Visit(True_value *);
	virtual void Visit(False_value *);
	virtual void Visit(Null_value *);
	virtual void Visit(Primary_ID *);
	virtual void Visit(Class *);
	virtual void Visit(Small *);
	virtual void Visit(Func_Small *);
	virtual void Visit(Var_Small *);
	virtual void Visit(Func *);
	virtual void Visit(Constructor *);
	virtual void Visit(Type *);
	virtual void Visit(Param_Decl *);
	virtual void Visit(Decl_List *);
	virtual void Visit(Comp *);
	virtual void Visit(Stmt_Comp *);
	virtual void Visit(Var_Comp *);
	virtual void Visit(Var_Decl *);
	virtual void Visit(Var_Decl_List *);
	virtual void Visit(Variable_Id *);
	virtual void Visit(Var_Id *);
	virtual void Visit(Var_Id_Exp *);
	virtual void Visit(Expr *);
	virtual void Visit(Expr_List *);
	virtual void Visit(Ex_Expr *);
	virtual void Visit(MinusExpr *);
	virtual void Visit(PlusExpr *);
	virtual void Visit(ParenthesesExpr *);
	virtual void Visit(Id_Expr_list *);
	virtual void Visit(Expr_op_Expr *);
	virtual void Visit(Stmt *);
	virtual void Visit(While_Stmt *);
	virtual void Visit(cond_stmt *);
	virtual void Visit(If *);
	virtual void Visit(If_Else *);
	virtual void Visit(assignStmt *);
	virtual void Visit(RT_expr *);
	virtual void Visit(Stmt_expr *);
	virtual void Visit(Break *);
	virtual void Visit(Continue *);
};

