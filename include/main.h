#pragma once

#include "SharedPtr.hpp"
#include <gtest/gtest.h>

#define EXPECT_TRUE(x) if (!(x)) { throw std::logic_error(#x); }
#define EXPECT_FALSE(x) if ((x)) { throw std::logic_error(#x); }
#define EXPECT_EXCEPTION(x) try {(x); throw std::logic_error(#x);} catch(const std::runtime_error&) {}


