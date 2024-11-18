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
%token <str_val> IDENT UNARY_OP
%token <int_val> INT_CONST

// 非终结符的类型定义
%type <ast_val> FuncDef FuncType Block Stmt Exp PrimaryExp Number UnaryExp UnaryOp

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
  : RETURN Exp ';' {
    auto exp = std::unique_ptr<BaseAST>($2);
    $$ = new StmtAST(exp);
  }
  ;

Exp
  : UnaryExp {
    auto unary_exp = std::unique_ptr<BaseAST>($1);
    $$ = new ExpAST(unary_exp);
  }
  ;

PrimaryExp
  : '(' Exp ')' {
    auto exp = std::unique_ptr<BaseAST>($2);
    $$ = PrimaryExpAST::CreateExpAST(exp);
  } 
  | Number {
    auto number = std::unique_ptr<BaseAST>($1);
    $$ = PrimaryExpAST::CreateNumberAST(number);
  }
  ;

Number
  : INT_CONST {
    $$ = new NumberAST($1);
  }
  ;

UnaryExp
  : PrimaryExp {
    auto primary_exp = std::unique_ptr<BaseAST>($1);
    $$ = UnaryExpAST::CreatePrimaryAST(primary_exp);
  }
  | UnaryOp UnaryExp {
    auto unary_op = std::unique_ptr<BaseAST>($1);
    auto unary_exp = std::unique_ptr<BaseAST>($2);
    $$ = UnaryExpAST::CreateUnaryAST(unary_op, unary_exp);
  }

UnaryOp 
  : UNARY_OP {
    auto op = std::unique_ptr<std::string>($1);
    $$ = new UnaryOpAST(*op);
  }

%%

void yyerror(std::unique_ptr<BaseAST> &ast, const char *s) {
  std::cerr << "error: " << s << std::endl;
}

