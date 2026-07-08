include compiler.mk

target-cpp-${CC_SUPPORT_STD_C++20} += compare
target-cpp-y += string

CXXFLAGS_compare += -std=c++20
