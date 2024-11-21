#pragma once
#include <string>

using var = std::string;

enum class TYPE_KIND {
  INT32,
  UNIT,
};

enum class VALUE_KIND {
  RET,
  INTEGER,
  UNARY,
};

enum class UNARY_OP {
  POS,
  NEG,
  NOT,
};

std::string to_string(TYPE_KIND func_type);
