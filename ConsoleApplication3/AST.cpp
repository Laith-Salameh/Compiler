#include "AST.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
using std::cout;
using std::ostringstream;
using std::endl;
using std::ofstream;


extern int last_func;
Func * writeline_write_int;
Func * writeline_write_real;
Func * writeline_write_string;
Func * writeline_write_bool;
Func * writeline_write_char;
Func * readline_read_int;
Func * readline_read_real;
Func * readline_read_string;
Func * readline_read_char;
Func * readline_read_bool;
bool symanticerror = false;
extern SymbolTable * symbolTable;
extern ofstream vcode;
extern Class * root;



/***********************errors**********************/
Error::Error(string message, int line, int col) :Node(line, col)
{
	this->message = message;
}
Errors::Errors()
{
	this->errorLists = new vector<Error *>;

}
void Errors::AddError(string message, int line, int column)
{
	Error *error = new Error(message, line, column);
	this->errorLists->push_back(error);
}
void Errors::Print()
{
	int size = this->errorLists->size();
	if (size == 0)
		cout << "Semntic analysis was done successfully! " << endl;
	else
	{
		cout << "There are " << size << " semantic errors: " << endl;
		for (int i = 0; i < size; i++)
		{
			cout << this->errorLists->at(i)->message << " at line: "
				<< this->errorLists->at(i)->line << " , column: "
				<< this->errorLists->at(i)->column << endl;
		}
	}
}


/****************************************/
Symbol::Symbol(string name , int kind, int type) {
	this->name = name;
	this->kind = kind;
	this->type = type;
}

Symbol::Symbol(string name, int kind, int type, Func * f) {
	this->name = name;
	this->kind = kind;
	this->type = type;
	this->function = f;
}

Scope::Scope()
{
	this->hashTab = new HashTab();
	//this->children = new vector<Scope *>;
}

SymbolTable::SymbolTable() {
	
	this->scopes = new vector < Scope* >;
	this->scopes->push_back(new Scope());
	this->errors = new Errors();
	this->current = this->scopes->at(0);
	kindes[1] = "F";
	kindes[2] = "GV";
	kindes[3] = "LV";
	kindes[4] = "C";
	types[1] = "int";
	types[2] = "float";
	types[3] = "boolean";
	types[4] = "char";
	types[5] = "string";
	types[6] = "null";
}

bool SymbolTable::AddSymbol(Id * id , int kind , int type) {
	Symbol * sym = new Symbol(id->name, kind, type);
	string key = kindes[kind] + id->name;
	Symbol * temp = this->current->hashTab->GetMember(key);
	if (temp == NULL) {
		this->current->hashTab->AddKey(key , sym );
		id->symbol = sym;
		return true;
	}
	else {
		//cout << " redifined variable : " << id->name <<" in line: " << id->line<<endl;
		symbolTable->errors->AddError("redifined variable : " + id->name, id->line, 0);
		symanticerror = true;
		return false;
	}
}
bool SymbolTable::AddFunc(Id * id, int kind, Decl_List * d ,  int type , Func * f) {
	Symbol * sym = new Symbol(id->name, kind, type , f);
	string key = kindes[kind] + id->name;
	if (d) {
		for (int i = 0; i < (int)(d->params->size()); i++)
		{
			int e = d->params->at(i)->type->type;
			key += "@" + types[e];
		}
	}
		
		//cout << id->name << " in line: " << id->line<< "Key: " << key << endl;
	Symbol * temp = this->current->hashTab->GetMember(key);
	
	if (temp == NULL) {
		this->current->hashTab->AddKey(key, sym);
		id->symbol = sym;
		return true;
	}
	else {
		//cout << " redifined function : " << id->name << " in line: " << id->line << endl;
		symbolTable->errors->AddError("redifined function : " + id->name, id->line, 0);

		symanticerror = true;
		return false;
	}
}

Symbol * SymbolTable::LookUp(Id * id  ) 
{
	string key;
	Symbol * sym;

	key = kindes[3] +id->name;
	sym = this->current->hashTab->GetMember(key);
	if (sym != NULL) {
		id->symbol = sym;
		return sym;
	}
	else {
		key = kindes[2] + id->name;
		sym = this->scopes->at(this->scopes->size() - 2)->hashTab->GetMember(key);
		if (sym != NULL) {
			id->symbol = sym;
			return sym;
		}
		else {
			//cout << " undefined variable: " << id->name << " in line: " << id->line << endl;
			symbolTable->errors->AddError("undifined variable : " + id->name, id->line, 0);

			symanticerror = true;
			return NULL;
		}
	}
	 
}

Symbol * SymbolTable::LookupConstructor(Id * id)
{
	string key;
	Symbol * sym;
	key = kindes[4] + id->name;
	sym = this->scopes->at(1)->hashTab->GetMember(key);
	if (sym != NULL) {
		id->symbol = sym;
		return sym;
	}
	else {
			//cout << " undefined class constrcutor in line: " << id->line << endl ;
			symbolTable->errors->AddError("undefined class constrcutor " , id->line, 0);

			symanticerror = true;
			return NULL;
	}

}

void SymbolTable::OpenScope() {
	this->scopes->push_back(new Scope());
	this->current = this->scopes->at(this->scopes->size() - 1);

}

void SymbolTable::CloseScope() {
	this->scopes->pop_back();
	this->current = this->scopes->at(this->scopes->size() - 1);
}



Node::Node(int line, int column)
{
	this->line = line;
	this->column = column;
	this->father = NULL;
}

void Node::setFather(Node * x, Node * y) {
	if (x != NULL) x->father = y;
}

Class::Class(Id* id, Small* small, int l , int c ): Node(l , c)
{
	this->name = id;
	this->small = small;
	setFather(id, this);
	setFather(small, this);
}

Func_Small::Func_Small(Small* small, Func* func, int l , int c):Small(l,c) {
	this->small = small;
	this->func = func;
	setFather(small, this);
	setFather(func, this);
}

Var_Small::Var_Small(Small* small, Var_Decl * var_decl , int l, int c) :Small(l, c) {
	this->small = small;
	this->var_decl = var_decl;
	setFather(small, this);
	setFather(var_decl , this);
}

Func::Func(Type * type, Id * id, Decl_List * decl_list , Comp * comp , int l , int c):Node(l,c) {
	this->type = type;
	this->name = id;
	this->args = decl_list;
	this->comp = comp;
	this->CG_visited = false;
	setFather(type , this);
	setFather(id , this );
	setFather(decl_list , this);
	setFather(comp ,this);
}

Constructor::Constructor(Id * name , Decl_List * decl_list , Comp *  comp , int l, int c) : Func(l,c) {
	this->name = name;
	this->args = decl_list;
	this->comp = comp;
	setFather(name, this);
	setFather(decl_list, this);
	setFather(comp, this);
}

Type::Type(int t, int l, int c) : Node(l, c) {
	this->type = t;

}

Id::Id(string s, int l, int c) : Node(l, c) {
	this->name = s;
	this->symbol = NULL;
}

Param_Decl::Param_Decl(Type * type, Id * name, int l, int c) : Node(l, c) {
	this->type = type;
	this->name = name;
	setFather(type, this);
	setFather(name, this);
}

Decl_List::Decl_List(Param_Decl * param , int l, int c) : Node(l, c) {
	this->params = new vector< Param_Decl * >;
	this->AddParam( param );

}

void Decl_List::AddParam(Param_Decl * param) {
	this->params->push_back(param);
	setFather(param, this);
}

Stmt_Comp::Stmt_Comp(Comp* comp, Stmt* stmt, int l, int c) : Comp(l, c) {
	this->comp = comp; 
	this->stmt = stmt;
	setFather(comp, this);
	setFather(stmt, this);

}

Var_Comp::Var_Comp(Comp* comp, Var_Decl* var_decl, int l, int c) : Comp(l, c) {
	this->comp = comp;
	this->var_decl = var_decl;
	setFather(comp, this);
	setFather(var_decl, this);
}

Var_Decl::Var_Decl(Type * type , Var_Decl_List * var_decl_list , int l, int c) :Node(l, c) {
	this->type = type;
	this->var_decl_list = var_decl_list;
	setFather(type, this);
	setFather(var_decl_list, this);
}

Var_Decl_List::Var_Decl_List(Variable_Id * var , int l, int c) :Node(l, c) {
	this->vars = new vector< Variable_Id *>;
	AddVar(var);
}

void Var_Decl_List::AddVar(Variable_Id * var) {
	this->vars->push_back(var);
	setFather(var, this);
}

Var_Id::Var_Id( Id* id, int l, int c) : Variable_Id(l, c)
{
	this->name = id;

	setFather(id, this);
}

Var_Id_Exp::Var_Id_Exp( Id* id , Expr* expr , int l , int c) : Variable_Id(l, c)
{
	this->name = id;
	this->expr = expr;
	setFather(id, this);
	setFather( expr , this);
}




While_Stmt::While_Stmt(Expr* expr, Comp* comp, int l, int c) : Stmt(l, c)
{
	this->expr = expr;
	this->comp = comp;
	setFather(expr, this);
	setFather(comp, this);
}


If::If(Expr* expr, Comp * comp, int l, int c) : cond_stmt(l, c)
{
	this->expr = expr;
	this->comp = comp;
	setFather(expr, this);
	setFather(comp, this);
}
If_Else::If_Else(Expr* expr, Comp * if_comp, Comp* else_comp, int l, int c) : cond_stmt( l, c)
{
	this->expr = expr;
	this->comp_if = if_comp;
	this->comp_else = else_comp;
	setFather(expr, this);
	setFather(if_comp, this);
	setFather(else_comp, this);
}
assignStmt::assignStmt(Id* id, Expr* expr, int l, int c) : Stmt(l, c)
{
	this->name = id;
	this->expr = expr;
	setFather(id, this);
	setFather(expr, this);
}

RT_expr::RT_expr(Expr* expr, int r , int l, int c) : Stmt(l, c)
{
	this->expr = expr;
	this->return_type = r;
	setFather(expr, this);
}

Stmt_expr::Stmt_expr(Expr* expr, int l , int c) : Stmt(l, c) {

	this->expr = expr;
	setFather(expr, this);
}

Expr_List::Expr_List(Expr * expr , int l, int c): Expr_List(l,c) {
	this->exprs = new vector< Expr* >;
	addExpression(expr);
}
void Expr_List::addExpression(Expr * expr) {
	this->exprs->push_back(expr);
	setFather(expr, this);
}

Ex_Expr::Ex_Expr(Expr* expr, int l , int c):Expr(l,c) {
	this->expr = expr;
	setFather(expr, this);
}

MinusExpr::MinusExpr(Expr* expr, int l, int c) : Expr(l, c) {
	this->expr = expr;
	setFather(expr, this);
}

PlusExpr::PlusExpr(Expr* expr, int l, int c) : Expr(l, c) {
	this->expr = expr;
	setFather(expr, this);
}


ParenthesesExpr::ParenthesesExpr(Expr* expr, int l, int c) : Expr(l, c) {
	this->expr = expr;
	setFather(expr, this);
}

Expr_op_Expr::Expr_op_Expr(Expr * left , int op , Expr * right , int l, int c ): Expr ( l,c) {
	this->right = right;
	this->op = op;
	this->left = left;
	setFather(right, this);
	setFather(left, this);
}


Id_Expr_list::Id_Expr_list(Id * id , Expr_List* expr_list, int l , int c): Expr( l,c) {
	this->name = id;
	this->expr_list = expr_list;
	setFather(id, this);
	setFather(expr_list, this);
}

Primary_ID::Primary_ID(Id * name, int l, int c) : Primary(l, c) {
	this->name = name;
	setFather(name, this);
}

Integer_value::Integer_value(int l, int c): Primary(l, c)
{
	this->type = 1;
	this->value = 0;
}
Integer_value::Integer_value(int value, int line, int col)
	: Primary(line, col)
{
	this->type = 1;
	this->value = value;
}

// Class Real_value
Real_value::Real_value(int line, int col)
	: Primary(line, col)
{
	this->type = 2;
	this->value = 0;
}
Real_value::Real_value(double value, int line, int col)
	: Primary(line, col)
{
	this->type = 2;
	this->value = value;
}

String_value::String_value(int line, int col)
	: Primary(line, col)
{
	this->type = 5;
	this->value = "";
}
String_value::String_value(string value, int line, int col)
	: Primary(line, col)
{
	this->type = 5;
	this->value = value;
}
Char_value::Char_value( int l, int c) : Primary(l, c) {
	this->type = 4;
	this->value = ' ';
}
Char_value::Char_value(char value, int l, int c) : Primary(l, c) {
	this->type = 4;
	this->value = value;
}

Null_value::Null_value(int l, int c): Primary(l,c) {
	this->type = 6;
}



void Node::accept(Visitor *v)
{
	v->Visit(this);
}
void Primary::accept( Visitor *v)
{
	v->Visit(this);
}
void Id::accept( Visitor *v)
{
	v->Visit(this);
}
void Integer_value::accept(Visitor *v)
{
	v->Visit(this);
}
void Real_value::accept(Visitor *v)
{
	v->Visit(this);
}
void Char_value::accept(Visitor *v)
{
	v->Visit(this);
}
void String_value::accept(Visitor *v)
{ 
	v->Visit(this); 
}
void True_value::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void False_value::accept( Visitor *v)
{ 
	v->Visit(this); 
}
void Null_value::accept( Visitor *v)
{ 
	v->Visit(this); 
}
void Primary_ID::accept( Visitor *v) 
{ 
	v->Visit(this); 
}
void Class::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Small::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Func_Small::accept( Visitor *v) 
{ 
	v->Visit(this); 
}
void Var_Small::accept( Visitor *v) 
{ 
	v->Visit(this); 
}
void Func::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Constructor::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Type::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Param_Decl::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Decl_List::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Comp::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Stmt_Comp::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Var_Comp::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Var_Decl::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Var_Decl_List::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Variable_Id::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Var_Id::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Var_Id_Exp::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Expr::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Expr_List::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Ex_Expr::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void MinusExpr::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void PlusExpr::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void ParenthesesExpr::accept( Visitor *v) 
{ 
	v->Visit(this);
}

void Id_Expr_list::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Expr_op_Expr::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void Stmt::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void While_Stmt::accept( Visitor *v) 
{ 
	v->Visit(this); 
}
void cond_stmt::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void If::accept( Visitor *v)
{ 
	v->Visit(this);
}
void If_Else::accept( Visitor *v)
{ 
	v->Visit(this);
}
void assignStmt::accept( Visitor *v) 
{ 
	v->Visit(this);
}
void RT_expr::accept( Visitor *v)
{ 
	v->Visit(this);
}
void Stmt_expr::accept(Visitor *v)
{
	v->Visit(this);
}
void Break::accept( Visitor *v) 
{ 
	v->Visit(this); 
}
void Continue::accept( Visitor *v) 
{ 
	v->Visit(this);
}

/**********************print visitor *********************/
PrintVisitor::PrintVisitor() {
		types[1] = "int";
		types[2] = "float";
		types[3] = "boolean";
		types[4] = "char";
		types[5] = "string";
		types[6] = "null";
		operators[1] = "+";
		operators[2] = "-";
		operators[3] = "*";
		operators[4] = "/";
		operators[5] = "%";
		operators[6] = ">";
		operators[7] = "<";
		operators[8] = "==";
		operators[9] = "&&";
		operators[10] = "||";
		operators[11] = "!=";
		
		
}

void PrintVisitor::Visit(Node *n)
{ 
	cout << "";
}
void PrintVisitor::Visit(Primary *n)
{
	//n->accept(this);
}
void PrintVisitor::Visit(Id *n)
{ 
	cout << "name: " << n->name;
}
void PrintVisitor::Visit(Integer_value *n)
{
	cout << "type: " << types[n->type] << " ,value: " << n->value ;
}
void PrintVisitor::Visit(Real_value *n)
{
	cout << "type: " << types[n->type] << " ,value: " << n->value ;
}
void PrintVisitor::Visit(Char_value *n)
{
	cout << "type: " << types[n->type] << " ,value: " << n->value ;
}
void PrintVisitor::Visit(String_value *n)
{
	cout << "type: " << types[n->type] << " ,value: " << n->value ;

}
void PrintVisitor::Visit(True_value *n)
{
	cout << "type: " << types[n->type] << " ,value: " << n->value;
}
void PrintVisitor::Visit(False_value *n)
{
	cout << "type: " << types[n->type] << " ,value: " << n->value ;
}
void PrintVisitor::Visit(Null_value *n)
{
	cout << "type: " << types[n->type] << " ,value: null" ;

}
void PrintVisitor::Visit(Primary_ID *n)
{
	cout << "name: " << n->name->name ;
}
void PrintVisitor::Visit(Class *n)
{
	cout << " Class: " << n->name->name << endl;
	cout << " { " << endl;
	n->small->accept(this);
	cout << " } " << endl;
}
void PrintVisitor::Visit(Small *n)
{
	cout << endl;
}
void PrintVisitor::Visit(Func_Small *n)
{
	n->small->accept(this);
	n->func->accept(this);
	cout << endl;
}
void PrintVisitor::Visit(Var_Small *n)
{
	n->small->accept(this);
	n->var_decl->accept(this);
	cout << endl;
}
void PrintVisitor::Visit(Func *n)
{
	n->type->accept(this);
	cout << "Function " << n->name->name;   cout << ": arguments (";
	n->args->accept(this);
	cout << " )" << endl;
	cout << " { " << endl;
	n->comp->accept(this);
	cout << " } " << endl;
}
void PrintVisitor::Visit(Constructor *n)
{
	cout << "Constructor " << n->name->name << " : arguments (";
	n->args->accept(this);
	cout << " )" << endl;
	cout << " { " << endl;
	n->comp->accept(this);
	cout << " } " << endl;
}
void PrintVisitor::Visit(Type *n)
{
	cout << "Type: " << types[n->type] << " ";
}
void PrintVisitor::Visit(Param_Decl *n)
{
	n->type->accept(this);
	n->name->accept(this);
}
void PrintVisitor::Visit(Decl_List *n)
{	
	try {
		for (int i = 0; i < (int)(n->params->size()); i++)
		{
			n->params->at(i)->accept(this);
			if (i != (int)(n->params->size() - 1)) cout << ",";
		}
	}
	catch (std::exception e) {
		cout << "";
	}
	
}
void PrintVisitor::Visit(Comp *n)
{
	cout << endl;
}
void PrintVisitor::Visit(Stmt_Comp *n)
{
	n->comp->accept(this);
	n->stmt->accept(this);
	cout << endl;
	
}
void PrintVisitor::Visit(Var_Comp *n)
{
	n->comp->accept(this);
	n->var_decl->accept(this);
	cout << endl;
}
void PrintVisitor::Visit(Var_Decl *n)
{
	n->type->accept(this);
	n->var_decl_list->accept(this);
	cout << endl;
}
void PrintVisitor::Visit(Var_Decl_List *n)
{ 
	bool t = n->vars->empty();
	if (t) return;
	for (int i = 0; i < (int)(n->vars->size()); i++)
	{
		n->vars->at(i)->accept(this);
		if (i != (int)(n->vars->size() - 1)) cout << ",";
	}
}
void PrintVisitor::Visit(Variable_Id *n)
{
	//n->accept(this);
}
void PrintVisitor::Visit(Var_Id *n)
{ 
	cout << "name: " << n->name->name << " "; 
}
void PrintVisitor::Visit(Var_Id_Exp *n)
{
	cout << "name: " << n->name->name << " = ";
	n->expr->accept(this);
}
void PrintVisitor::Visit(Expr *n)
{
	//n->accept(this);
}
void PrintVisitor::Visit(Expr_List *n)
{
	bool t = n->exprs->empty();
	if (t) return;
	for (int i = 0; i < (int)(n->exprs->size()); i++)
	{
		n->exprs->at(i)->accept(this);
		if (i != (int)(n->exprs->size() - 1)) cout << ",";
	}
}
void PrintVisitor::Visit(Id_Expr_list *n)
{
	n->name->accept(this);
	cout << " (";
	n->expr_list->accept(this);
	cout << " )" << endl;
}

void PrintVisitor::Visit(Ex_Expr *n)
{
	cout << "!";
	n->expr->accept(this);
}
void PrintVisitor::Visit(MinusExpr *n)
{
	cout << "-";
	n->expr->accept(this);
}
void PrintVisitor::Visit(PlusExpr *n)
{
	cout << "+";
	n->expr->accept(this);
}
void PrintVisitor::Visit(ParenthesesExpr *n)
{
	cout << "(";
	n->expr->accept(this);
	cout << ")";
}

void PrintVisitor::Visit(Expr_op_Expr *n)
{
	n->left->accept(this);
	cout<<operators[n->op];
	n->right->accept(this);
}
void PrintVisitor::Visit(Stmt *n)
{

}
void PrintVisitor::Visit(While_Stmt *n)
{
	cout << "While (";
	n->expr->accept(this);
	cout << ") {" << endl;
	n->comp->accept(this);
	cout << "}" << endl;
}
void PrintVisitor::Visit(cond_stmt *n)
{

}
void PrintVisitor::Visit(If *n)
{
	cout << "if (";
	n->expr->accept(this);
	cout << ") {" << endl;
	n->comp->accept(this);
	cout << "}" << endl;
}
void PrintVisitor::Visit(If_Else *n)
{
	cout << "if (";
	n->expr->accept(this);
	cout << ") {" << endl;
	n->comp_if->accept(this);
	cout << "}" << endl<<"Else {";
	n->comp_else->accept(this);
	cout << "}" << endl;
}
void PrintVisitor::Visit(assignStmt *n)
{
	cout<< "name" <<n->name->name << "=";
	n->expr->accept(this);
}
void PrintVisitor::Visit(RT_expr *n)
{
	cout << "Return ";
	n->expr->accept(this);
	cout<< ";" << endl;
}
void PrintVisitor::Visit(Stmt_expr *n)
{
	n->expr->accept(this);
	cout << ";" << endl;
}
void PrintVisitor::Visit(Break *n)
{
	cout << "Break ;" << endl;
}
void PrintVisitor::Visit(Continue *n)
{
	cout << "Break ;" << endl;
}


/************************Typechecker****/

bool typechecking_assign(int l, int r)
{
	bool mismatch = false;
	if (l == 1)
	{
		if (r == 1 || r == 2 ||r == 3 || r == 4) mismatch = false;
		else mismatch = true;
	}
	else if (l == 2)
	{
		if (r == 1 || r == 2)  mismatch = false;
		else mismatch = true;
	}
	else if (l == 3)
	{
		if (r == 3)  mismatch = false;
		else mismatch = true;
	}
	else if (l == 4) {
		if (r == 4)  mismatch = false;
		else mismatch = true;
	}
	else if (l == 5) {
		if (r == 5)  mismatch = false;
		else mismatch = true;
	}
	return mismatch;
}

bool check_mismatch(int l, string op, int r) {
	bool mis = false; 
	if (op == "+" ) {
		if (l == r) mis = true;
		else {
			if (l == 1 || l == 2) {
				if (r != 6 && r!= 5) mis = true;
				else mis = false;
			}
			if (l == 3) {
				if (r == 4 || r == 5 || r == 6) mis = false;
				else mis = true;
			}
			if (l == 4) {
				if (r == 4 || r == 5 || r==1 || r ==2) mis = true;
				else mis = false;
			}
			if (l == 5) {
				if (r == 3 || r == 1 || r == 2 || r == 6) mis = false;
				else mis = true;
			}
			if (l == 6)
			{
				return false;
			}
		}
	}
	else {
		if (op == "-") {
			if (l == r && l != 5) mis = true;
			else {
				if (l == 1 || l == 2) {
					if (r != 6 && r != 5) mis = true;
					else mis = false;
				}
				if (l == 3) {
					if (r == 4 || r == 5 || r == 6) mis = false;
					else mis = true;
				}
				if (l == 4) {
					if (r == 4 || r == 1 || r == 2) mis = true;
					else mis = false;
				}
				if (l == 5) {
					mis = false;

				}
				if (l == 6)
				{
					return false;
				}
			}
		}
		else {
			if (op == "*" || op == "/" || op == "%" ) {
			if (l == r && l != 5 && l != 4 && l != 3) mis = true;
			else {
				if (l == 1 || l == 2) {
					if (r != 6 && r != 5 && l != 4 && l != 3) mis = true;
					else mis = false;
				}
				if (l == 3 || l == 4 || l == 5) {
					mis = false;
				}
				if (l == 6)
				{
					return false;
				}
			}
		}
			else {
				if (op == "&&" || op == "||") {
					if (l == 3 && r == 3) {
						mis = true;
					}
					else
						mis = false;
				}
				else {
					if (op == "!=" || op == "==") {
						if (l == r) mis = true;
						else mis = false;
					}
					else {
						if (op == ">" || op == "<") {
								if (l == 1 || l == 2) {
									if (r != 6 && r != 5 && r!=4 && r != 3 ) mis = true;
									else mis = false;
								}
								if (l == 3 || l == 4 || l == 5 || l == 6) {
									 mis = false;
									
								}
							
						}
					}
				}
			}
	}
	}

	return mis;
}

int get_type(int l, string op, int r) {
	if (op == "+") {
		if (l == r) return l;
		else {
			if (l == 1) {
				if (r == 2) return 2;
				if (r == 3) return 1;
				if (r == 4) return 4;
			}
			if (l == 2) {
				if (r == 1) return 2;
				if (r == 3) return 2;
				if (r == 4) return 4;
			}
			if (l == 3) {
				if (r == 1) return 1;
				if (r == 2) return 2;
			}
			if (l == 4) {
				if (r == 1) return 4;
				if (r == 2) return 4;
				if (r == 5) return 5;
			}
			if (l == 5) {
				return 5;
			}
		}
	}
	else {
		if (op == "-") {
				if (l == 1) {
					if (r == 1) return 1;
					if (r == 2) return 2;
					if (r == 3) return 1;
					if (r == 4) return 4;
				}
				if (l == 2) {
					if (r == 1) return 2;
					if (r == 2 ) return 2;
					if (r == 3) return 2;
					if (r == 4) return 4;
				}
				if (l == 3) {
					if (r == 1) return 1;
					if (r == 2) return 2;
					if (r == 3) return 3;
				}
				if (l == 4) {
					if (r == 1) return 4;
					if (r == 2) return 4;
					if (r == 4) return 4;
					if (r == 5) return 5;
				}
				if (l == 5) {
					return 5;
				}
			
		}
		else {
			if (op == "*" || op == "/" || op == "%"  ) {
				if (l == 1) {
					if (r == 1) return 1;
					if (r == 2) return 2;
				}
				if (l == 2) {
					if (r == 1) return 2;
					if (r == 2) return 2;
				}
			}
			else {
				if (op == "==" || op == "!=" || op == ">" || op == "<" || op =="&&" || op == "||" ) {
					return 3;
				}
			}
			
		}

	}
	return 0;
}



/*****************************/

TypeChecker::TypeChecker() {
	types[1] = "int";
	types[2] = "float";
	types[3] = "boolean";
	types[4] = "char";
	types[5] = "string";
	types[6] = "null";
	operators[1] = "+";
	operators[2] = "-";
	operators[3] = "*";
	operators[4] = "/";
	operators[5] = "%";
	operators[6] = ">";
	operators[7] = "<";
	operators[8] = "==";
	operators[9] = "&&";
	operators[10] = "||";
	operators[11] = "!=";
	

}

void TypeChecker::Visit(Node *n)
{
}
void TypeChecker::Visit(Primary *n)
{
}
void TypeChecker::Visit(Id *n)
{
}
void TypeChecker::Visit(Integer_value *n)
{
}
void TypeChecker::Visit(Real_value *n)
{
}
void TypeChecker::Visit(Char_value *n)
{
}
void TypeChecker::Visit(String_value *n)
{
}
void TypeChecker::Visit(True_value *n)
{

}
void TypeChecker::Visit(False_value *n)
{
}
void TypeChecker::Visit(Null_value *n)
{
}
void TypeChecker::Visit(Primary_ID *n)
{
	n->type = n->name->symbol->type;
}
void TypeChecker::Visit(Class *n)
{
	n->small->accept(this);
	if (symbolTable->current->hashTab->GetMember("Fmain") == NULL)
	{
		//cout<< "There is no main function" << endl;
		symbolTable->errors->AddError("There is no main Function", 0, 0);
		symanticerror = true;
	}
}
void TypeChecker::Visit(Small *n)
{
}
void TypeChecker::Visit(Func_Small *n)
{
	n->small->accept(this);
	n->func->accept(this);
}
void TypeChecker::Visit(Var_Small *n)
{
	n->small->accept(this);
	n->var_decl->accept(this);
}
void TypeChecker::Visit(Func *n)
{
	n->type->accept(this);
	n->args->accept(this);
	n->comp->accept(this);
	if (n->comp->return_type == 10) {
		symbolTable->errors->AddError("not all paths return in function : " + n->name->name, n->line, n->column);
		symanticerror = true;
	}
}
void TypeChecker::Visit(Constructor *n)
{
	n->args->accept(this);
	n->comp->accept(this);
}
void TypeChecker::Visit(Type *n)
{
}
void TypeChecker::Visit(Param_Decl *n)
{
	n->type->accept(this);
	n->name->accept(this);
}
void TypeChecker::Visit(Decl_List *n)
{
		for (int i = 0; i < (int)(n->params->size()); i++)
		{
			n->params->at(i)->accept(this);
		}
}
void TypeChecker::Visit(Comp *n)
{
}
void TypeChecker::Visit(Stmt_Comp *n)
{
	n->comp->accept(this);
	n->stmt->accept(this);

	n->return_type = (n->comp->return_type <= n->stmt->return_type ? n->comp->return_type : n->stmt->return_type);

}
void TypeChecker::Visit(Var_Comp *n)
{
	n->comp->accept(this);
	n->var_decl->accept(this);
	n->return_type = n->comp->return_type;
}
void TypeChecker::Visit(Var_Decl *n)
{
	n->type->accept(this);
	n->var_decl_list->accept(this);
}
void TypeChecker::Visit(Var_Decl_List *n)
{
	for (int i = 0; i < (int)(n->vars->size()); i++)
	{
		n->vars->at(i)->accept(this);
	}
}
void TypeChecker::Visit(Variable_Id *n)
{
}
void TypeChecker::Visit(Var_Id *n)
{
}
void TypeChecker::Visit(Var_Id_Exp *n)
{
	
	n->expr->accept(this);
	int l = n->name->symbol->type;
	int r = n->expr->type;
	bool t=typechecking_assign(l, r);
	if (t) {
		//cout << "mismatching assignment of var :" << n->name->name << " in line: " << n->line<<endl;
		symbolTable->errors->AddError("mismatching assignment of var :" + n->name->name, n->line, n->column);
		symanticerror = true;
	}

}
void TypeChecker::Visit(Expr *n)
{
	//n->accept(this);
}
void TypeChecker::Visit(Expr_List *n)
{
	for (int i = 0; i < (int)(n->exprs->size()); i++)
	{
		n->exprs->at(i)->accept(this);
		
	}
}
void TypeChecker::Visit(Id_Expr_list *n)
{
	n->name->accept(this);
	n->expr_list->accept(this);
	 
	string key = "F" + n->name->name; 
	if (n->expr_list) {
		for (int i = 0; i < (int)(n->expr_list->exprs->size()); i++)
		{
			int e = n->expr_list->exprs->at(i)->type;
			key += "@" + types[e];
		}
	}
	Symbol * temp = symbolTable->current->hashTab->GetMember(key);
	if (temp == NULL) {
		symbolTable->errors->AddError("no such function exists : " + n->name->name, n->name->line, 0);
		symanticerror = true;
	}
	else {
		n->type = temp->type;
		n->func = temp->function; 
	}

}

void TypeChecker::Visit(Ex_Expr *n)
{
	n->expr->accept(this);
	int l = n->expr->type;
	if (l != 3) {
		//cout << "mismatching type on operation ! :" << " in line: " << n->line << endl;
		symbolTable->errors->AddError("mismatching type on operation '!' ", n->line, n->column);
		symanticerror = true;
		n->type = 6;
		return ;
	}
	n->type = 3;
}
void TypeChecker::Visit(MinusExpr *n)
{
	n->expr->accept(this);
	int l = n->expr->type;
	if (l ==4 || l == 5 || l == 6) {
		//cout << "mismatching type on operation - :" << " in line: " << n->line << endl;
		symbolTable->errors->AddError("mismatching type on operation '-' ", n->line, n->column);
		symanticerror = true;
		n->type = 6;
		return;
	}
	n->type = l;
}
void TypeChecker::Visit(PlusExpr *n)
{
	
	n->expr->accept(this);
	n->type = n->expr->type;
}
void TypeChecker::Visit(ParenthesesExpr *n)
{
	
	n->expr->accept(this);
	n->type = n->expr->type;
}

void TypeChecker::Visit(Expr_op_Expr *n)
{
	n->left->accept(this);
	int op = n->op;
	n->right->accept(this);
	bool t = check_mismatch(n->left->type, operators[op], n->right->type);
	if (t) {
		int x=get_type(n->left->type, operators[op], n->right->type);
		n->type = x;
	}
	else {
		//cout << "mismatching type on expr " << operators[op] <<" expr :" << " in line: " << n->line << endl;
		symbolTable->errors->AddError("mismatching type on expr " + operators[op] + " expr ", n->line, n->column);
		symanticerror = true;
		n->type = 6;
	}
}
void TypeChecker::Visit(Stmt *n)
{

}
void TypeChecker::Visit(While_Stmt *n)
{
	n->expr->accept(this);
	int l = n->expr->type;
	if (l == 4 || l == 5 || l == 6) {
		symbolTable->errors->AddError("mismatching type should be bool in while condition: ", n->expr->line, n->expr->column);
		//cout << "mismatching type should be bool in while condition:" << " in line: " << n->line << endl;
		symanticerror = true;
		n->expr->type = 6;
	}
	n->comp->accept(this);

}
void TypeChecker::Visit(cond_stmt *n)
{

}
void TypeChecker::Visit(If *n)
{
	n->expr->accept(this);
	int l = n->expr->type;
	if (l == 4 || l == 5 || l == 6) {
		symbolTable->errors->AddError("mismatching type should be bool in if condition: ", n->expr->line, n->expr->column);
		//cout << "mismatching type should be bool in if condition:" << " in line: " << n->line << endl;
		symanticerror = true;
		n->expr->type = 6;
	}
	n->comp->accept(this);
}
void TypeChecker::Visit(If_Else *n)
{
	n->expr->accept(this);
	int l = n->expr->type;
	if (l == 4 || l == 5 || l == 6) {
		//nvgjhhjkl.l
		//cout << "mismatching type should be bool in if condition:" << " in line: " << n->line << endl;
		symbolTable->errors->AddError("mismatching type should be bool in if condition: ", n->expr->line, n->expr->column);
		symanticerror = true;
		n->expr->type = 6;
	}
	n->comp_if->accept(this);
	n->comp_else->accept(this);

	if (n->comp_if->return_type != 10 && n->comp_else->return_type != 10) {
		n->return_type = n->comp_if->return_type;
	}
}
void TypeChecker::Visit(assignStmt *n)
{
	n->expr->accept(this);
	int r = n->expr->type;
	int l = n->name->symbol->type;
	bool t = typechecking_assign(l, r);
	//cout << l << " " << r << endl;
	if (t) {
		symbolTable->errors->AddError("mismatching assignment of var :" +  n->name->name, n->line, n->column);
		//cout << "mismatching assignment of var :" << n->name->name << " in line: " << n->line << endl;
		symanticerror = true;
	}

}
void TypeChecker::Visit(RT_expr *n)
{
	n->expr->accept(this);
	int r = n->expr->type;
	int l = n->return_type;
	bool t = typechecking_assign(l, r);
	if (t) {
		symbolTable->errors->AddError("mismatching assignment of return function , should be : " + types[l], n->line, n->column);
		symanticerror = true;
	}

}
void TypeChecker::Visit(Stmt_expr *n)
{
	n->expr->accept(this);

}
void TypeChecker::Visit(Break *n)
{
}
void TypeChecker::Visit(Continue *n)
{
}


/************************************************************/

void ReadWrite::ReadWriteAdd()
{
	//  _write_int
	Id * id_write_int = new Id("write", 0, 0);
	Id * id_param_write_int = new Id("1_write_int_x", 0, 0);
	symbolTable->AddSymbol(id_param_write_int, 2, 1);
	Decl_List * prameters_write_int = new Decl_List(new Param_Decl(new Type(1,0,0), id_param_write_int, 0, 0), 0, 0);
	writeline_write_int = new Func(new Type( 6, 0 ,0),id_write_int, prameters_write_int, NULL, 0, 0);
	writeline_write_int->CG_visited = true;
	symbolTable->AddFunc(id_write_int, 1, prameters_write_int , 6 , writeline_write_int);

	
	//  _write_real
	Id * id_write_real = new Id("write", 0, 0);
	Id * id_param_write_real = new Id("1_write_real_x", 0, 0);
	symbolTable->AddSymbol(id_param_write_real, 2, 2);
	Decl_List * prameters_write_real = new Decl_List(new Param_Decl(new Type(2, 0, 0), id_param_write_real, 0, 0), 0, 0);
	writeline_write_real = new Func(new Type(6, 0, 0),id_write_real, prameters_write_real, NULL, 0, 0);
	writeline_write_real->CG_visited = true;
	symbolTable->AddFunc(id_write_real, 1, prameters_write_real, 6 , writeline_write_real);

	//  _write_bool
	Id * id_write_bool = new Id("write", 0, 0);
	Id * id_param_write_bool = new Id("1_write_bool_x", 0, 0);
	symbolTable->AddSymbol(id_param_write_bool, 2, 3);
	Decl_List * prameters_write_bool = new Decl_List(new Param_Decl(new Type(3, 0, 0), id_param_write_bool, 0, 0), 0, 0);
	writeline_write_bool = new Func(new Type(6, 0, 0), id_write_bool, prameters_write_bool, NULL, 0, 0);
	writeline_write_bool->CG_visited = true;
	symbolTable->AddFunc(id_write_bool, 1, prameters_write_bool, 6 , writeline_write_bool);

	//  _write_char
	Id * id_write_char = new Id("write", 0, 0);
	Id * id_param_write_char = new Id("1_write_char_x", 0, 0);
	symbolTable->AddSymbol(id_param_write_char, 2, 4);
	Decl_List * prameters_write_char = new Decl_List(new Param_Decl(new Type(4, 0, 0), id_param_write_char, 0, 0), 0, 0);
	writeline_write_char = new Func(new Type(6, 0, 0), id_write_char, prameters_write_char, NULL, 0, 0);
	writeline_write_char->CG_visited = true;
	symbolTable->AddFunc(id_write_char, 1, prameters_write_char, 6 , writeline_write_char);

	//  _write_string
	Id * id_write_string = new Id("write", 0, 0);
	Id * id_param_write_string = new Id("1_write_string_x", 0, 0);
	symbolTable->AddSymbol(id_param_write_string, 2, 5);
	Decl_List * prameters_write_string = new Decl_List(new Param_Decl(new Type(5, 0, 0), id_param_write_string, 0, 0), 0, 0);
	writeline_write_string = new Func(new Type(6, 0, 0),id_write_string, prameters_write_string, NULL, 0, 0);
	writeline_write_string->CG_visited = true;
	symbolTable->AddFunc(id_write_string, 1, prameters_write_string, 6 , writeline_write_string);

	

	
	//  _read_int
	Id * id_read_int = new Id("readInt", 0, 0);
	readline_read_int = new Func(new Type( 1, 0 ,0), id_read_int, NULL, NULL, 0, 0);
	readline_read_int->CG_visited = true;
	symbolTable->AddFunc(id_read_int, 1, NULL , 1 , readline_read_int);
	
	//  _read_real
	Id * id_read_real = new Id("readReal", 0, 0);
	readline_read_real = new Func(new Type(2, 0, 0), id_read_real, NULL, NULL, 0, 0);
	readline_read_real->CG_visited = true;
	symbolTable->AddFunc(id_read_real, 1, NULL, 2 , readline_read_real);

	////  _read_bool
	Id * id_read_bool = new Id("readBool", 0, 0);
	readline_read_bool = new Func(new Type(3,0,0), id_read_bool, NULL, NULL, 0, 0);
	readline_read_bool->CG_visited = true;
	symbolTable->AddFunc(id_read_bool, 1, NULL, 3 , readline_read_bool);

	//  _read_char
	Id * id_read_char = new Id("readChar", 0, 0);
	readline_read_char = new Func(new Type(4, 0, 0), id_read_char, NULL, NULL, 0, 0);
	readline_read_char->CG_visited = true;
	symbolTable->AddFunc(id_read_char, 1, NULL, 4 , readline_read_char);

	
	//  _read_string
	Id * id_read_string = new Id("readString", 0, 0);
	readline_read_string = new Func(new Type(5, 0, 0), id_read_string, NULL, NULL, 0, 0);
	readline_read_string->CG_visited = true;
	symbolTable->AddFunc(id_read_string, 1, NULL, 5 , readline_read_string);
	
	
}

/********************************************codegeneration****************************************/
CodeGeneration::CodeGeneration()
{
	f = 0; g = 999;
	types[1] = "int";
	types[2] = "float";
	types[3] = "boolean";
	types[4] = "char";
	types[5] = "string";
	types[6] = "null";
	operators[1] = "+";
	operators[2] = "-";
	operators[3] = "*";
	operators[4] = "/";
	operators[5] = "%";
	operators[6] = ">";
	operators[7] = "<";
	operators[8] = "==";
	operators[9] = "&&";
	operators[10] = "||";
	operators[11] = "!=";
	funcs = new vector < Symbol* >();
}
void CodeGeneration::w(string s)
{
	vcode << s << endl;
}
void CodeGeneration::Visit(Node *n)
{
}
void CodeGeneration::Visit(Primary *n)
{
}
void CodeGeneration::Visit(Id *n)
{
}
void CodeGeneration::Visit(Integer_value *n)
{
	w("pushi " + std::to_string(n->value));
}
void CodeGeneration::Visit(Real_value *n)
{
	w("pushf " + std::to_string(n->value));
}
void CodeGeneration::Visit(Char_value *n)
{
	string s = "";
		s = n->value;
	w("pushs \"" + s + "\"");
}
void CodeGeneration::Visit(String_value *n)
{
	string s = "";
	for (int i = 1; i < (int)(n->value.length()) - 1; i++)
	{
		s += n->value[i];
	}
	w("pushs \"" + s + "\"");
}
void CodeGeneration::Visit(True_value *n)
{
	w("pushi 1");
}
void CodeGeneration::Visit(False_value *n)
{
	w("pushi 0");
}
void CodeGeneration::Visit(Null_value *n)
{
}
void CodeGeneration::Visit(Primary_ID *n)
{
	
	
	if (n->name != NULL)
	{
		n->name->accept(this);
		if (n->name->symbol->kind == 2)
		{
			w("pushg " + std::to_string(n->name->symbol->location));
		}
		else
		{
			w("pushl " + std::to_string(n->name->symbol->location));
		}
	}
	
}

void CodeGeneration::Visit(Small *n)
{
}
void CodeGeneration::Visit(Func_Small *n)
{
	n->small->accept(this);
}
void CodeGeneration::Visit(Var_Small *n)
{
	n->small->accept(this);
	n->var_decl->accept(this);
}
void CodeGeneration::Visit(Func *n)
{
	if (n->CG_visited == false)
	{
		f = 0;
		n->CG_visited = true;
		string label = "";
		label += n->name->name;
		if (n->args)
		{
			for (int i = 0; i < (int)(n->args->params->size()); i++)
			{
				label += "__" + types[n->args->params->at(i)->type->type];
			}
		}
		w(label + ":");
		if (n->args) n->args->accept(this);
		if (n->comp) n->comp->accept(this);
		
	}
}
void CodeGeneration::Visit(Constructor *n)
{

}
void CodeGeneration::Visit(Type *n)
{

}
void CodeGeneration::Visit(Param_Decl *n)
{
	
}
void CodeGeneration::Visit(Decl_List *n)
{
	for (int i = 0; i < (int)(n->params->size()); i++)
	{
		Param_Decl* p = n->params->at(i);
		p->name->symbol->location = i - n->params->size();
	}
}
void CodeGeneration::Visit(Comp *n)
{
}
void CodeGeneration::Visit(Stmt_Comp *n)
{
	n->comp->accept(this);
	n->stmt->accept(this);
}
void CodeGeneration::Visit(Var_Comp *n)
{
	n->comp->accept(this);
	n->var_decl->accept(this);
}
void CodeGeneration::Visit(Var_Decl *n)
{
	
		for (int i = 0; i < (int)(n->var_decl_list->vars->size()); i++) {
			n->var_decl_list->vars->at(i)->accept(this);
		}
	
	
}
void CodeGeneration::Visit(Var_Decl_List *n)
{

}
void CodeGeneration::Visit(Variable_Id *n)
{
}
void CodeGeneration::Visit(Var_Id *n)
{
		n->name->accept(this);
		if (n->name->symbol->kind == 2)
		{
			w("pushi 0");
			if (n->name->symbol->type == 2) {
				w("itof");
			}
			n->name->symbol->location = g;
			w("storeg " + std::to_string(g));
			w("pushg " + std::to_string(g));
			g--;
		}
		else
		{
			w("pushi 0");
			if (n->name->symbol->type == 2) {
				w("itof");
			}
			n->name->symbol->location = f;
			w("storel " + std::to_string(f));
			w("pushl " + std::to_string(f));
			f++;
		}
	
}
void CodeGeneration::Visit(Var_Id_Exp *n)
{

	if (n->name->symbol->kind == 2)
	{
		n->expr->accept(this);
		n->name->symbol->location = g;
		if (n->name->symbol->type == 2 && n->expr->type == 1) w("itof");
		w("storeg " + std::to_string(g));
		w("pushg " + std::to_string(g));
		g--;
	}
	else if (n->name->symbol->kind == 3)
	{
		n->expr->accept(this);
		n->name->symbol->location = f;
		if (n->name->symbol->type == 2 && n->expr->type == 1) w("itof");
		w("storel " + std::to_string(f));
		w("pushl " + std::to_string(f));
		f++;
	}
}
void CodeGeneration::Visit(Expr *n)
{
}
void CodeGeneration::Visit(Expr_List *n)
{

}
void CodeGeneration::Visit(Id_Expr_list *n)
{
	if (n->expr_list) {
		for (int i = 0; i < (int)(n->expr_list->exprs->size()); i++)
		{
			n->expr_list->exprs->at(i)->accept(this);
			if (n->expr_list->exprs->at(i)->type == 1 && n->func->args->params->at(i)->type->type == 2)
				w("itof");
		}
	}
	string label = "";
	label += n->name->name;
	if (n->func->args)
	{
		for (int i = 0; i < (int)(n->func->args->params->size()); i++)
		{
			label += "__" + types[n->func->args->params->at(i)->type->type];
		}
	}
	w("pusha " + label);
	w("call");

	Symbol* functionSymbol = n->func->name->symbol;
	if (functionSymbol)
	{
		funcs->push_back(functionSymbol);
		if (n->expr_list != NULL && n->expr_list->exprs && n->expr_list->exprs->size() > 0)
			w("pop " + std::to_string(n->expr_list->exprs->size()));
		if (functionSymbol->type != 6) w("pushg " + std::to_string(g));
	}

}

void CodeGeneration::Visit(Ex_Expr *n)
{
	n->expr->accept(this);
	w("pushi 0");
	w("equal");
}
void CodeGeneration::Visit(MinusExpr *n)
{
	n->expr->accept(this);
	if (n->type == 1 || n->type == 3) {
		w("pushi -1");
		w("mul ");
	}
	else {
		w("pushf -1");
		w("fmul ");
	}
}
void CodeGeneration::Visit(PlusExpr *n)
{
	n->expr->accept(this);
}
void CodeGeneration::Visit(ParenthesesExpr *n)
{
	n->expr->accept(this);
	n->type = n->expr->type;
}

void CodeGeneration::Visit(Expr_op_Expr* n)
{
	int op = n->op;
	if (operators[op] == "+")
	{
		if (n->left != NULL) n->left->accept(this);
		if (n->right != NULL) n->right->accept(this);
		if (n->left->type == 1 && n->right->type == 1 ) w("add");
		else
			if (n->left->type == 1 && n->right->type == 2)
			{
				w("storeg " + std::to_string(g));
				w("itof");
				w("pushg " + std::to_string(g));
				w("fadd");
			}
			else
				if (n->right->type == 1 && n->left->type == 2)
				{
					w("itof");
					w("fadd");
				}
				else
					if (n->left->type == 2 && n->right->type == 2) w("fadd");
					else {
						if ((n->left->type == 4 && n->right->type == 4) || (n->left->type == 5 && n->right->type == 4) || (n->left->type == 4 && n->right->type == 5) || (n->left->type == 5 && n->right->type == 5)) {
							w("concat");
						}
					}
	}
	else {
		if (operators[op] == "-")
		{
			if (n->left != NULL) n->left->accept(this);
			if (n->right != NULL) n->right->accept(this);
			if (n->left->type == 1 && n->right->type == 1) w("sub");
			else
				if (n->left->type == 1)
				{
					w("storeg " + std::to_string(g));
					w("itof");
					w("pushg " + std::to_string(g));
					w("fsub");
				}
				else
					if (n->right->type == 1)
					{
						w("itof");
						w("fsub");
					}
					else
						if (n->left->type == 2 && n->right->type == 2) w("fsub");
		}
		else {
			if (operators[op] == "*")
			{
				if (n->left != NULL) n->left->accept(this);
				if (n->right != NULL) n->right->accept(this);
				if (n->left->type == 1 && n->right->type == 1) w("mul");
				else
					if (n->left->type == 1)
					{
						w("storeg " + std::to_string(g));
						w("itof");
						w("pushg " + std::to_string(g));
						w("fmul");
					}
					else
						if (n->right->type == 1)
						{
							w("itof");
							w("fmul");
						}
						else
							if (n->left->type == 2 && n->right->type == 2) w("fmul");
			}
			else {
				if (operators[op] == "/")
				{
					if (n->left != NULL) n->left->accept(this);
					if (n->right != NULL) n->right->accept(this);
					if (n->left->type == 1 && n->right->type == 1) w("div");
					else
						if (n->left->type == 1)
						{
							w("storeg " + std::to_string(g));
							w("itof");
							w("pushg " + std::to_string(g));
							w("fdiv");
						}
						else
							if (n->right->type == 1)
							{
								w("itof");
								w("fdiv");
							}
							else
								if (n->left->type == 2 && n->right->type == 2) w("fdiv");
				}
				else {
					if (operators[op] == "%")
					{
						if (n->left != NULL) n->left->accept(this);
						if (n->right != NULL) n->right->accept(this);
						if (n->left->type == 1 && n->right->type == 1) w("mod");
						else
							if (n->left->type == 1)
							{
								w("storeg " + std::to_string(g));
								w("itof");
								w("pushg " + std::to_string(g));
								w("fmod");
							}
							else
								if (n->right->type == 1)
								{
									w("itof");
									w("fmod");
								}
								else
									if (n->left->type == 2 && n->right->type == 2) w("fmod");
					}
					else {
						if (operators[op] == "&&")
						{
							if (n->left != NULL) n->left->accept(this);
							if (n->right != NULL) n->right->accept(this);
							w("add");
							w("pushi 2");
							w("equal");
						}
						else {
							if (operators[op] == "||")
							{
								if (n->left != NULL) n->left->accept(this);
								if (n->right != NULL) n->right->accept(this);
								w("add");
								w("pushi 0");
								w("equal");
								w("not");
							}
							else {
								if (operators[op] == "==")
								{
									if (n->left != NULL) n->left->accept(this);
									if (n->right != NULL) n->right->accept(this);
									if (n->left->type == 1 && n->right->type == 1) w("equal");
									else
										if (n->left->type == 1)
										{
											w("storeg " + std::to_string(c));
											w("itof");
											w("pushg " + std::to_string(c));
											w("equal");
										}
										else
											if (n->right->type == 1)
											{
												w("itof");
												w("equal");
											}
											else
												if (n->left->type == 2 && n->right->type == 2) w("equal");
								}
								else {
									if (operators[op] == "!=")
									{
										if (n->left != NULL) n->left->accept(this);
										if (n->right != NULL) n->right->accept(this);
										if (n->left->type == 1 && n->right->type == 1) w("equal");
										else
											if (n->left->type == 1)
											{
												w("storeg " + std::to_string(c));
												w("itof");
												w("pushg " + std::to_string(c));
												w("equal");
											}
											else
												if (n->right->type == 1)
												{
													w("itof");
													w("equal");
												}
												else
													if (n->left->type == 2 && n->right->type == 2) w("equal");
										w("not");
									}
									else {
										if (operators[op] == ">")
										{
											if (n->left != NULL) n->left->accept(this);
											if (n->right != NULL) n->right->accept(this);
											if (n->left->type == 1 && n->right->type == 1) w("sup");
											else
												if (n->left->type == 1)
												{
													w("storeg " + std::to_string(c));
													w("itof");
													w("pushg " + std::to_string(c));
													w("sup");
												}
												else
													if (n->right->type == 1)
													{
														w("itof");
														w("sup");
													}
													else
														if (n->left->type == 2 && n->right->type == 2) w("sup");
										}
										else {
											if (operators[op] == "<")
											{
												if (n->left != NULL) n->left->accept(this);
												if (n->right != NULL) n->right->accept(this);
												if (n->left->type == 1 && n->right->type == 1) w("inf");
												else
													if (n->left->type == 1)
													{
														w("storeg " + std::to_string(c));
														w("itof");
														w("pushg " + std::to_string(c));
														w("inf");
													}
													else
														if (n->right->type == 1)
														{
															w("itof");
															w("inf");
														}
														else
															if (n->left->type == 2 && n->right->type == 2) w("inf");
											}
										}

									}

								}
							}
						}
					}
				}
			}
		}
	}
}
void CodeGeneration::Visit(Stmt *n)
{
	///////////////////
}
void CodeGeneration::Visit(While_Stmt *n)
{
	whileLabel++;
	int label = whileLabel;
	w("WHILE_BEGIN" + std::to_string(label) + ":");
	if (n->expr != NULL)
	{
		n->expr->accept(this);
	}
	w("jz WHILE_END" + std::to_string(label));
	if (n->comp != NULL)
	{
		n->comp->accept(this);
	}
	w("jump WHILE_BEGIN" + std::to_string(label));
	w("WHILE_END" + std::to_string(label) + ":");
}
void CodeGeneration::Visit(cond_stmt *n)
{
	///////////////////
}
void CodeGeneration::Visit(If *n)
{
	ifLabel++;
	int label = ifLabel;
	w("IF_BEGIN" + std::to_string((label)) + ":");
	if (n->expr != NULL) n->expr->accept(this);
	w("jz IF_END" + std::to_string((label)));
	if (n->comp != NULL) n->comp->accept(this);
	w("IF_END" + std::to_string((label)) + ":");
}
void CodeGeneration::Visit(If_Else *n)
{
	ifElseLabel++;
	int label = ifElseLabel;
	w("IF_else_BEGIN" + std::to_string((label)) + ":");
	if (n->expr != NULL) n->expr->accept(this);
	w("jz ELSE_BEGIN" + std::to_string((label)));
	if (n->comp_if != NULL) n->comp_if->accept(this);
	w("IF_else_END" + std::to_string((label)) + ":");
	w("jump ELSE_END" + std::to_string((label)));
	w("ELSE_BEGIN" + std::to_string((label)) + ":");
	if (n->comp_else != NULL)n->comp_else->accept(this);
	w("ELSE_END" + std::to_string((label)) + ":");
}
void CodeGeneration::Visit(assignStmt *n)
{
	n->expr->accept(this);
	n->name->accept(this);
	if (n->name->symbol->type == 2 && n->expr->type == 1) w("itof");
	if (n->name->symbol->kind == 2)
	{
		w("storeg " + std::to_string(n->name->symbol->location));
		w("pushg " + std::to_string(n->name->symbol->location));
	}
	else if (n->name->symbol->kind == 3)
	{
		w("storel " + std::to_string(n->name->symbol->location));
		w("pushl " + std::to_string(n->name->symbol->location));
	}
}
void CodeGeneration::Visit(RT_expr *n)
{
	n->expr->accept(this);
	if (n->expr->type == 1 && n->return_type == 2) w("itof");
	w("storeg " + std::to_string(g));
	w("pushg " + std::to_string(g));
	w("return");

}
void CodeGeneration::Visit(Stmt_expr *n)
{
	n->expr->accept(this);

}
void CodeGeneration::Visit(Break *n)
{
	w("jump WHILE_END" + std::to_string(whileLabel));
}
void CodeGeneration::Visit(Continue *n)
{
	w("jump WHILE_BEGIN" + std::to_string(whileLabel));
}

void CodeGeneration::Visit(Class *n)
{


	w("start");
	n->small->accept(this);
	w("pusha main");
	w("call");
	w("stop");
	w("\n");
	symbolTable->current->hashTab->GetMember("Fmain")->function->accept(this);
	for (int i = 0; i < (int)(funcs->size()); i++)
	{
		funcs->at(i)->function->accept(this);
	}
	generateReadWriteFunction();

}

void CodeGeneration::generateReadWriteFunction()
{
	w("\n\n\n");
	w("\n\n\n");
	////writeline integer
	w("write__int:");
	w("pushl -1");
	w("storel 0");
	w("pushl 0");
	w("pushl 0");
	w("writei");
	w("return\n\n\n");

	////writeline real
	w("write__double:");
	w("pushl -1");
	w("storel 0");
	w("pushl 0");
	w("pushl 0");
	w("writef");
	w("return\n\n\n");

	////writeline string
	w("write__string:");
	w("pushl -1");
	w("storel 0");
	w("pushl 0");
	w("pushl 0");
	w("writes");
	w("return\n\n\n");

	////writeline string
	w("write__char:");
	w("pushl -1");
	w("storel 0");
	w("pushl 0");
	w("pushl 0");
	w("writes");
	w("return\n\n\n");



	////writeline boolean
	w("write__boolean:");
	w("pushl -1");
	w("storel 0");
	w("pushl 0");
	w("pushl 0");
	w("writei");
	w("return\n\n\n");

	////read integer
	w("readInt:");
	w("read");
	w("atoi");
	w("storeg " + std::to_string(g) + "");
	w("return\n\n\n");

	////read real
	w("readReal:");
	w("read");
	w("atof");
	w("storeg " + std::to_string(g) + "");
	w("return\n\n\n");

	////read string
	w("readString:");
	w("read");
	w("storeg " + std::to_string(g) + "");
	w("return\n\n\n");


	/////readkey
	w("readChar:");
	w("read");
	w("storeg " + std::to_string(g) + "");
	w("return\n\n\n");

	////read bool
	w("readBool:");
	w("read");
	w("atoi");
	w("storeg " + std::to_string(g) + "");
	w("return\n\n\n");

}


