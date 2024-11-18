#include "ir_utils.hpp"

std::string to_string(FUNC_KIND func_type) {
  switch (func_type) {
  case FUNC_KIND::INT:
    return "i32";
  case FUNC_KIND::VOID:
    return "void";
  default:
    return "Unknown";
  }
}
