#include "ast.hpp"
#include <cassert>
#include <iostream>
#include <memory>

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
  result += "}\n";
  return result;
}

void StmtAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Stmt {" << std::endl;
  std::cout << std::string(indent + 1, '\t') << "return " << std::endl;
  exp->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string StmtAST::KoopaIR() const {
  // TODO:
}

void ExpAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Exp {" << std::endl;
  unary_exp->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string ExpAST::KoopaIR() const {
  std::string result;
  result += unary_exp->KoopaIR();
  return result;
}

PrimaryExpAST *PrimaryExpAST::CreateExpAST(std::unique_ptr<BaseAST> &exp) {
  auto node = new PrimaryExpAST(Kind::EXP);
  node->exp = std::move(exp);
  return node;
}

PrimaryExpAST *
PrimaryExpAST::CreateNumberAST(std::unique_ptr<BaseAST> &number) {
  auto node = new PrimaryExpAST(Kind::NUMBER);
  node->number = std::move(number);
  return node;
}

void PrimaryExpAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "PrimaryExp {" << std::endl;
  if (kind == Kind::EXP) {
    assert(exp != nullptr && "exp is nullptr");
    exp->Dump(indent + 1);
  } else if (kind == Kind::NUMBER) {
    assert(number != nullptr && "number is nullptr");
    number->Dump(indent + 1);
  }
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string PrimaryExpAST::KoopaIR() const {
  // TODO:
}

void NumberAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << val << ", " << std::endl;
}

std::string NumberAST::KoopaIR() const { return std::to_string(val); }

UnaryExpAST *
UnaryExpAST::MakeFromPrimary(std::unique_ptr<BaseAST> &primary_exp) {
  auto node = new UnaryExpAST(Kind::PRIMARY_EXP);
  node->primary_exp = std::move(primary_exp);
  return node;
}

UnaryExpAST *UnaryExpAST::CreateUnaryAST(std::unique_ptr<BaseAST> &unary_op,
                                         std::unique_ptr<BaseAST> &unary_exp) {
  auto node = new UnaryExpAST(Kind::UNARY_EXP);
  node->unary_op = std::move(unary_op);
  node->unary_exp = std::move(unary_exp);
  return node;
}

void UnaryExpAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "UnaryExp {" << std::endl;
  if (kind == Kind::PRIMARY_EXP) {
    primary_exp->Dump(indent + 1);
  } else if (kind == Kind::UNARY_EXP) {
    unary_op->Dump(indent + 1);
    unary_exp->Dump(indent + 1);
  }
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

std::string UnaryExpAST::KoopaIR() const {
  // TODO:
  std::string result;
  if (kind == Kind::PRIMARY_EXP) {
    result = primary_exp->KoopaIR();
  } else if (kind == Kind::UNARY_EXP) {
    std::string result_exp = unary_exp->KoopaIR();
    result += result_exp;
    std::string old_symbol;
    if (result_exp.front() == '%') {
      old_symbol = result_exp.substr(0, 2);
    }
    if (unary_op->KoopaIR() == "+") {
    } else if (unary_op->KoopaIR() == "-") {
      result +=
          "\n\t%" + std::to_string(symbol_num++) + " = sub 0, " + result_exp;
    } else if (unary_op->KoopaIR() == "!") {
      result += "\n\t%" + std::to_string(symbol_num++) + " = eq " + result_exp +
                ", 0";
    }
  } else {
    assert(false && "UnaryExp to unknown!");
  }
  return result;
}

UnaryOpAST::UnaryOpAST(std::string op) : op(op) {
  if (op == "+") {
    type = UnaryOpType::PLUS;
  } else if (op == "-") {
    type = UnaryOpType::MINUS;
  } else if (op == "!") {
    type = UnaryOpType::NOT;
  } else {
    assert(false && "Unknown unary op!!!");
  }
}

void UnaryOpAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "UnaryOp: " << op << ", "
            << std::endl;
}

std::string UnaryOpAST::KoopaIR() const { return op; }
