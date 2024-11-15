#include "ir.hpp"
#include <iostream>
#include <koopa.h>

void CompUnitIR::to_koopa(std::string &str, const int tabs) const {
  func_def->to_koopa(str);
}

void FuncDefIR::to_koopa(std::string &str, const int tabs) const {
  str += "fun @" + ident + "(): " + to_string(func_type) + " {";
  block->to_koopa(str);
  str += "\n}";
}

void BasicBlockIR::to_koopa(std::string &str, const int tabs) const {
  str += "%entry: \n";
  stmt->to_koopa(str, tabs + 1);
}

// 访问 raw program
std::string Visit(const koopa_raw_program_t &program) {
  std::string result = "\t.text\n";
  result += "\t.globl main\n";

  std::string valuesString = Visit(program.values);
  result += valuesString;

  std::string funcsString = Visit(program.funcs);
  result += funcsString;

  return result;
}

std::string Visit(const koopa_raw_slice_t &slice) {
  std::string result;
  for (size_t i = 0; i < slice.len; ++i) {
    auto ptr = slice.buffer[i];
    // 根据 slice 的 kind 决定将 ptr 视为何种元素
    switch (slice.kind) {
    case KOOPA_RSIK_FUNCTION:
      result += Visit(reinterpret_cast<koopa_raw_function_t>(ptr));
      break;
    case KOOPA_RSIK_BASIC_BLOCK:
      result += Visit(reinterpret_cast<koopa_raw_basic_block_t>(ptr));
      break;
    case KOOPA_RSIK_VALUE:
      result += Visit(reinterpret_cast<koopa_raw_value_t>(ptr));
      break;
    default:
      assert(false);
    }
  }
  return result;
}

std::string Visit(const koopa_raw_function_t &function) {
  assert(function->ty->tag == KOOPA_RTT_FUNCTION);
  std::string result = std::string(function->name).substr(1) + ":\n";
  result += Visit(function->params);
  result += Visit(function->bbs);
  return result;
}

std::string Visit(const koopa_raw_basic_block_t &basicblock) {
  std::string result;
  result += Visit(basicblock->params);
  result += Visit(basicblock->used_by);
  result += Visit(basicblock->insts);
  return result;
}

std::string Visit(const koopa_raw_value_t &value) {
  std::string result = "";
  const auto &kind = value->kind;
  switch (kind.tag) {
  case KOOPA_RVT_RETURN:
    result += Visit(kind.data.ret);
    break;
  case KOOPA_RVT_INTEGER:
    result += Visit(kind.data.integer);
    break;
  default:
    assert(false);
  }
  return result;
}

std::string Visit(const koopa_raw_return_t &ret) {
  std::string result = "\tli a0, ";
  result += Visit(ret.value);
  result += "\n\tret\n";
  return result;
}

std::string Visit(const koopa_raw_integer_t &integer) {
  return std::to_string(integer.value);
}
