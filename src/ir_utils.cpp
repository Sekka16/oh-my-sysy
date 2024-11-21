#include "ir_utils.hpp"

std::string to_string(TYPE_KIND func_type) {
  switch (func_type) {
  case TYPE_KIND::INT32:
    return "i32";
  case TYPE_KIND::UNIT:
    return "void";
  default:
    return "Unknown";
  }
}
