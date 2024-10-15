#include "ast.hpp"
#include <iostream>

void CompUnitAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "CompUnit {" << std::endl;
  func_def->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string CompUnitAST::KoopaIR() const {
  std::string result = "fun ";
  result += func_def->KoopaIR();
  return result;
}

void FuncDefAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "FuncDef {" << std::endl;
  func_type->Dump(indent + 1);
  std::cout << std::string(indent + 1, '\t') << "IDENT: " << ident << std::endl;
  block->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string FuncDefAST::KoopaIR() const {
  std::string result = "@" + ident + "():";
  result += func_type->KoopaIR();
  result += block->KoopaIR();
  return result;
}

void FuncTypeAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "FuncType: " << type << std::endl;
}

std::string FuncTypeAST::KoopaIR() const { return " i32 "; }

void BlockAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Block {" << std::endl;
  stmt->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string BlockAST::KoopaIR() const {
  std::string result = "{\n%entry:\n";
  result += stmt->KoopaIR();
  result += "}";
  return result;
}

void StmtAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Stmt {" << std::endl;
  number->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string StmtAST::KoopaIR() const {
  std::string result = " ret ";
  result += number->KoopaIR() + "\n";
  return result;
}

void NumberAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << val << ", " << std::endl;
}

std::string NumberAST::KoopaIR() const { return std::to_string(val); }
