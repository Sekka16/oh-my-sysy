#pragma once
#include <iostream>
#include <memory>
#include <string>

// CompUnit  ::= FuncDef;
//
// FuncDef   ::= FuncType IDENT "(" ")" Block;
// FuncType  ::= "int";
//
// Block     ::= "{" Stmt "}";
// Stmt      ::= "return" Number ";";
// Number    ::= INT_CONST;

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

  void Dump(int indent = 0) const override {
    std::cout << std::string(indent, '\t') << "CompUnit {" << std::endl;
    func_def->Dump(indent + 1);
    std::cout << std::string(indent, '\t') << "}" << std::endl;
  }
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

  void Dump(int indent = 0) const override {
    std::cout << std::string(indent, '\t') << "FuncDef {" << std::endl;
    func_type->Dump(indent + 1);
    std::cout << std::string(indent + 1, '\t') << "IDENT: " << ident
              << std::endl;
    block->Dump(indent + 1);
    std::cout << std::string(indent, '\t') << "}" << std::endl;
  }
};

class FuncTypeAST : public BaseAST {
public:
  std::string type;

  FuncTypeAST(std::string type) : type(type) {}

  void Dump(int indent = 0) const override {
    std::cout << std::string(indent, '\t') << "FuncType: " << type << std::endl;
  }
};

class BlockAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> stmt;

  BlockAST(std::unique_ptr<BaseAST> &stmt) : stmt(std::move(stmt)) {}

  void Dump(int indent = 0) const override {
    std::cout << std::string(indent, '\t') << "Block {" << std::endl;
    stmt->Dump(indent + 1);
    std::cout << std::string(indent, '\t') << "}" << std::endl;
  }
};

class StmtAST : public BaseAST {
public:
  std::unique_ptr<BaseAST> number;

  StmtAST(std::unique_ptr<BaseAST> &number) : number(std::move(number)) {}

  void Dump(int indent = 0) const override {
    std::cout << std::string(indent, '\t') << "Stmt {" << std::endl;
    number->Dump(indent + 1);
    std::cout << std::string(indent, '\t') << "}" << std::endl;
  }
};

class NumberAST : public BaseAST {
public:
  int val;

  NumberAST(int val) : val(val) {}

  void Dump(int indent = 0) const override {
    std::cout << std::string(indent, '\t') << val << ", " << std::endl;
  }
};
