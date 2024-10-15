#pragma once
#include "koopa.h"
#include <cassert>
#include <string>

std::string Visit(const koopa_raw_program_t &program);

std::string Visit(const koopa_raw_slice_t &slice);

std::string Visit(const koopa_raw_function_t &function);

std::string Visit(const koopa_raw_basic_block_t &basicblock);

std::string Visit(const koopa_raw_value_t &value);

std::string Visit(const koopa_raw_return_t &ret);

std::string Visit(const koopa_raw_integer_t &integer);
