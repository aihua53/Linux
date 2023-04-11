cmake_minimum_required(VERSION 3.1)
project(dhrystone)

if((CMAKE_C_COMPILER_ID STREQUAL "GNU") OR (CMAKE_C_COMPILER_ID MATCHES "Clang"))
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w -fno-inline")
endif()

set(CMAKE_EXE_LINKER_FLAGS"-static -static-libgcc -nostdlib")

add_executable(dhrystone
               dhry_1.c
               dhry_2.c)
target_compile_definitions(dhrystone PRIVATE -DMSC_CLOCK -DCLK_TCK=CLOCKS_PER_SEC)

