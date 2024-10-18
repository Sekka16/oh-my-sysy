%code requires {
  #include <memory>
  #include <string>
  #include "ast.hpp"
}

%{

#include <iostream>
#include <memory>
#include <string>
#include "ast.hpp"

int yylex();
void yyerror(std::unique_ptr<BaseAST> &ast, const char *s);

%}

// CompUnit    ::= FuncDef;
// 
// FuncDef     ::= FuncType IDENT "(" ")" Block;
// FuncType    ::= "int";
// 
// Block       ::= "{" Stmt "}";
// Stmt        ::= "return" Exp ";";
// 
// Exp         ::= UnaryExp;
// PrimaryExp  ::= "(" Exp ")" | Number;
// Number      ::= INT_CONST;
// UnaryExp    ::= PrimaryExp | UnaryOp UnaryExp;
// UnaryOp     ::= "+" | "-" | "!";

// 定义 parser 函数和错误处理函数的附加参数
%parse-param { std::unique_ptr<BaseAST> &ast }

%union {
  std::string *str_val;
  int int_val;
  BaseAST *ast_val;
  UnaryOpType unary_op_type;
}

// lexer 返回的所有 token 种类的声明
%token INT RETURN
%token <str_val> IDENT
%token <int_val> INT_CONST
%token <UnaryOpType> UNARY_OP

// 非终结符的类型定义
%type <ast_val> FuncDef FuncType Block Stmt Number

%%

CompUnit
  : FuncDef {
    auto func = std::unique_ptr<BaseAST>($1);
    ast = std::unique_ptr<BaseAST>(new CompUnitAST(func));
  }
  ;

FuncDef
  : FuncType IDENT '(' ')' Block {
    auto func_type = std::unique_ptr<BaseAST>($1);
    auto ident = std::unique_ptr<std::string>($2);
    auto block = std::unique_ptr<BaseAST>($5);
    $$ = new FuncDefAST(func_type, *ident, block);
  }
  ;

FuncType
  : INT {
    $$ = new FuncTypeAST("int");
  }
  ;

Block
  : '{' Stmt '}' {
    auto stmt = std::unique_ptr<BaseAST>($2);
    $$ = new BlockAST(stmt);
  }
  ;

Stmt
  : RETURN Number ';' {

  }
  ;

Exp
  : UnaryExp {

  }
  ;

PrimaryExp
  : '{' Exp '}' {

  } 
  | Number {

  }
  ;

Number
  : INT_CONST {
    $$ = new NumberAST($1);
  }
  ;

UnaryExp
  : PrimaryExp {

  }
  | UnaryOp UnaryExp {

  }

UnaryOp 
  : UNARY_OP {

  }

%%

void yyerror(std::unique_ptr<BaseAST> &ast, const char *s) {
  std::cerr << "error: " << s << std::endl;
}

