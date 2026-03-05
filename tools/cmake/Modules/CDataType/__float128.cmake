include(CheckCXXSourceCompiles)
include(CMakePushCheckState)

cmake_push_check_state(RESET)
set(CMAKE_REQUIRED_LIBRARIES quadmath)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_REQUIRED_FLAGS "-fext-numeric-literals")
endif()

check_cxx_source_compiles("
  #include <quadmath.h>
  int main() {
    __float128 x = 1.0q;
    x = strtoflt128(\"1.2345678\", NULL);
    return 0;
  }
" SUPPORT___float128)

cmake_pop_check_state()

if(SUPPORT___float128)
  message(STATUS "Compiler supports __float128")
  add_compile_definitions(SUPPORT___float128)
else()
  message(STATUS "Compiler does NOT support __float128")
endif()
