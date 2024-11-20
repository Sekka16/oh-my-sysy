#include "ast.hpp"
#include <cassert>
#include <iostream>
#include <memory>

std::unique_ptr<PrimaryExpAST>
PrimaryExpAST::CreateExpAST(std::unique_ptr<BaseAST> &exp) {
  auto node = std::make_unique<PrimaryExpAST>(Kind::EXP);
  node->exp = std::move(exp);
  return node;
}

std::unique_ptr<PrimaryExpAST>
PrimaryExpAST::CreateNumberAST(std::unique_ptr<BaseAST> &number) {
  auto node = std::make_unique<PrimaryExpAST>(Kind::NUMBER);
  node->number = std::move(number);
  return node;
}

std::unique_ptr<UnaryExpAST>
UnaryExpAST::CreatePrimaryAST(std::unique_ptr<BaseAST> &primary_exp) {
  auto node = std::make_unique<UnaryExpAST>(Kind::PRIMARY_EXP);
  node->primary_exp = std::move(primary_exp);
  return node;
}

std::unique_ptr<UnaryExpAST>
UnaryExpAST::CreateUnaryAST(std::unique_ptr<BaseAST> &unary_op,
                            std::unique_ptr<BaseAST> &unary_exp) {
  auto node = std::make_unique<UnaryExpAST>(Kind::UNARY_EXP);
  node->unary_op = std::move(unary_op);
  node->unary_exp = std::move(unary_exp);
  return node;
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

void CompUnitAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "CompUnit {" << std::endl;
  func_def->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

void FuncDefAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "FuncDef {" << std::endl;
  func_type->Dump(indent + 1);
  std::cout << std::string(indent + 1, '\t') << "IDENT: " << ident << std::endl;
  block->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

void FuncTypeAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "FuncType: " << type << std::endl;
}

void BlockAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Block {" << std::endl;
  stmt->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

void StmtAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Stmt {" << std::endl;
  std::cout << std::string(indent + 1, '\t') << "return " << std::endl;
  exp->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
}

void ExpAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "Exp {" << std::endl;
  unary_exp->Dump(indent + 1);
  std::cout << std::string(indent, '\t') << "}" << std::endl;
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

void NumberAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << val << ", " << std::endl;
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

void UnaryOpAST::Dump(int indent) const {
  std::cout << std::string(indent, '\t') << "UnaryOp: " << op << ", "
            << std::endl;
}
