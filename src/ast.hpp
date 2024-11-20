#pragma once
#include <cassert>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>

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
static int symbol_num = 0;
static std::vector<std::string> insts;

class BaseAST {
public:
  virtual ~BaseAST() = default;
  virtual void Dump(int indent = 0) const = 0;
};

class CompUnitAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> func_def;

  CompUnitAST(std::unique_ptr<BaseAST> &func_def)
      : func_def(std::move(func_def)) {}

  void Dump(int indent = 0) const override;
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
};

class FuncTypeAST : public BaseAST {
public:
  std::string type;

  FuncTypeAST(std::string type) : type(type) {}

  void Dump(int indent = 0) const override;
};

class BlockAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  BlockAST(std::unique_ptr<BaseAST> &stmt) : stmt(std::move(stmt)) {}

  void Dump(int indent = 0) const override;
};

class StmtAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> exp;

  StmtAST(std::unique_ptr<BaseAST> &exp) : exp(std::move(exp)) {}

  void Dump(int indent = 0) const override;
};

class ExpAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> unary_exp;

  ExpAST(std::unique_ptr<BaseAST> &unary_exp)
      : unary_exp(std::move(unary_exp)) {}

  void Dump(int ident = 0) const override;
};

class PrimaryExpAST : public BaseAST {
public:
  enum class Kind {
    EXP,
    NUMBER,
  };

  Kind kind;
  std::unique_ptr<BaseAST> exp;
  std::unique_ptr<BaseAST> number;

  explicit PrimaryExpAST(Kind kind) : kind(kind) {}

  static std::unique_ptr<PrimaryExpAST>
  CreateExpAST(std::unique_ptr<BaseAST> &exp);

  static std::unique_ptr<PrimaryExpAST>
  CreateNumberAST(std::unique_ptr<BaseAST> &number);

  void Dump(int indent = 0) const override;
};

class NumberAST : public BaseAST {
public:
  int val;

  NumberAST(int val) : val(val) {}

  void Dump(int indent = 0) const override;
};

class UnaryExpAST : public BaseAST {
public:
  enum class Kind {
    PRIMARY_EXP,
    UNARY_EXP,
  };

  Kind kind;
  std::unique_ptr<BaseAST> primary_exp;
  std::unique_ptr<BaseAST> unary_op;
  std::unique_ptr<BaseAST> unary_exp;

  explicit UnaryExpAST(Kind kind) : kind(kind) {}

  static std::unique_ptr<UnaryExpAST>
  CreatePrimaryAST(std::unique_ptr<BaseAST> &primary_exp);

  static std::unique_ptr<UnaryExpAST>
  CreateUnaryAST(std::unique_ptr<BaseAST> &unary_op,
                 std::unique_ptr<BaseAST> &unary_exp);

  void Dump(int indent = 0) const override;
};

class UnaryOpAST : public BaseAST {
public:
  UnaryOpType type;
  std::string op;

  UnaryOpAST(std::string op);

  void Dump(int indent = 0) const override;
};
