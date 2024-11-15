#include "ir_utils.hpp"

std::string to_string(FUNC_TYPE func_type) {
  switch (func_type) {
  case FUNC_TYPE::INT:
    return "i32";
  case FUNC_TYPE::VOID:
    return "void";
  default:
    return "Unknown";
  }
}
