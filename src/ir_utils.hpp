#pragma once
#include <string>

enum class FUNC_TYPE {
  INT,
  VOID,
};

std::string to_string(FUNC_TYPE func_type);
