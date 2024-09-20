%code requires {
  #include <memory>
  #include <string>
  #include "ast.h"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "ast.h"

int yylex();
void yyerror(std::unique_ptr<std::string> &ast, const char *s);

%}

%parse-param { std::unique_ptr<BaseAST> &ast }

%union {
  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
}

%token INT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST

%type <ast_val> FuncDef FuncType Block Stmt
%type <str_int> Number

%%

CompUnit
  : FuncDef {
    auto func = std::unique_ptr<BaseAST>($1);
    ast = std::unique_ptr<BaseAST>(new CompUnit(func));
  }
  ;

FuncDef
  : FuncType IDENT '(' ')' Block {
    auto func_type = std::unique_ptr<BaseAST>($1);
    auto ident = std::unique_ptr<std::string>($2);
    auto block = std::unique_ptr<BaseAST>($5);
    $$ = new FuncDefAST(func_type, ident->c_str(), block);
  }
  ;

FuncType
  : INT {
    $$ = new std::string("int");
  }
  ;

Block
  : '{' Stmt '}' {
    auto stmt = std::unique_ptr<std::string>($2);
    $$ = new std::string("{ " + *stmt + " }");
  }
  ;

Stmt
  : RETURN Number ';' {
    auto number = std::unique_ptr<std::string>($2);
    $$ = new std::string("return " + *number + ";");
  }
  ;

Number
  : INT_CONST {
    $$ = new std::string(std::to_string($1));
  }
  ;

%%

void yyerror(std::unique_ptr<std::string> &ast, const char *s) {
  std::cerr << "error: " << s << std::endl;
}

