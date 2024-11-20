#pragma once
#include "ast.hpp"
#include "ir_utils.hpp"
#include "koopa.h"
#include <cassert>
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

class BaseIR {
public:
  virtual ~BaseIR() = default;
  virtual void to_koopa(std::string &str, const int tabs = 0) const = 0;
  // virtual void to_riscv(std::string &str, const int tabs = 0) const = 0;
};

class CompUnitIR : public BaseIR {
public:
  std::unique_ptr<BaseIR> func_def;

  void to_koopa(std::string &str, const int tabs = 0) const override;
};

class FuncDefIR : public BaseIR {
public:
  FUNC_KIND func_type;
  std::string ident;
  std::unique_ptr<BaseIR> block;

  void to_koopa(std::string &str, const int tabs = 0) const override;
};

class BasicBlockIR : public BaseIR {
public:
  std::vector<std::unique_ptr<BaseIR>> insts;

  void to_koopa(std::string &str, const int tabs = 0) const override;
};

std::string Visit(const koopa_raw_program_t &program);

std::string Visit(const koopa_raw_slice_t &slice);

std::string Visit(const koopa_raw_function_t &function);

std::string Visit(const koopa_raw_basic_block_t &basicblock);

std::string Visit(const koopa_raw_value_t &value);

std::string Visit(const koopa_raw_return_t &ret);

std::string Visit(const koopa_raw_integer_t &integer);
