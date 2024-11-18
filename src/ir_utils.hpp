#pragma once
#include <string>

enum class FUNC_KIND {
  INT,
  VOID,
};

std::string to_string(FUNC_KIND func_type);
