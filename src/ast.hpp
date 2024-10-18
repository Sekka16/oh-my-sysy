#pragma once
#include <memory>
#include <string>

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

enum class UnaryOpType { PLUS, MINUS, NOT };

class BaseAST {
public:
  virtual ~BaseAST() = default;
  virtual void Dump(int indent = 0) const = 0;
  virtual std::string KoopaIR() const = 0;
};

class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  CompUnitAST(std::unique_ptr<BaseAST> &func_def)
      : func_def(std::move(func_def)) {}

  void Dump(int indent = 0) const override;

  std::string KoopaIR() const override;
};

class FuncDefAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_type;
  std::string ident;
  std::unique_ptr<BaseAST> block;

  FuncDefAST(std::unique_ptr<BaseAST> &func_type, std::string &ident,
             std::unique_ptr<BaseAST> &block)
      : func_type(std::move(func_type)), ident(ident), block(std::move(block)) {
  }

  void Dump(int indent = 0) const override;

  std::string KoopaIR() const override;
};

class FuncTypeAST : public BaseAST {
public:
  std::string type;

  FuncTypeAST(std::string type) : type(type) {}

  void Dump(int indent = 0) const override;

  std::string KoopaIR() const override;
};

class BlockAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  BlockAST(std::unique_ptr<BaseAST> &stmt) : stmt(std::move(stmt)) {}

  void Dump(int indent = 0) const override;

  std::string KoopaIR() const override;
};

class StmtAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> number;

  StmtAST(std::unique_ptr<BaseAST> &number) : number(std::move(number)) {}

  void Dump(int indent = 0) const override;

  std::string KoopaIR() const override;
};

class ExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_exp;

  ExpAST(std::unique_ptr<BaseAST> &unary_exp)
      : unary_exp(std::move(unary_exp)) {}

  void Dump(int ident = 0) const override;

  std::string KoopaIR() const override;
};

class PrimaryExp : public BaseAST {
public:
  std::unique_ptr<BaseAST> expr;
};

class NumberAST : public BaseAST {
public:
  int val;

  NumberAST(int val) : val(val) {}

  void Dump(int indent = 0) const override;

  std::string KoopaIR() const override;
};
