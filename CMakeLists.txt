cmake_minimum_required(VERSION 2.8)

project (RSA_MODULE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(HEADERS ${PROJECT_SOURCE_DIR}/include/rsa.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/catch.hpp)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmath.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathbig.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathdec.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathint.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathmisc.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathobjects.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathparser.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmaththreads.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathtypes.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathuint.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathuint_noasm.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathuint_x86.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathuint_x86_64.h)
set(HEADERS ${PROJECT_SOURCE_DIR}/include/ttmathuint_x86_64_msvc.asm)
set(SOURCES ${PROJECT_SOURCE_DIR}/sources/rsa.cpp)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)


add_library (${PROJECT_NAME} STATIC ${SOURCES})

add_subdirectory(example)
add_subdirectory(tests)
