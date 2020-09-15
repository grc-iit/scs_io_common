cmake_minimum_required(VERSION 3.10)
project(symbios)
set(INSTALL_DIR $ENV{INSTALL_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${INCLUDE_DIRS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${INCLUDE_DIRS}")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/common/include)

# Executables
add_executable(arg_test args/test.cpp)

# Enable tests
option(BUILD_TEST "Build the unit tests" ON)
if(BUILD_TEST)
    enable_testing()
    include(CTest)
endif()

# Add tests

add_test(NAME args_conv COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/arg_test -test arg_conv -a hello -b 24245 -c 35k -d 2.0)
add_test(NAME args_list COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/arg_test -test arg_list -b 24245 -b 24245 -b 24245)
add_test(NAME args_default COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/arg_test -test default_args -e 24245 -e 24245 -e 24245)
add_test(NAME args_invalid COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/arg_test -test invalid_args -asdf)
add_test(NAME args_invalid2 COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/arg_test -test invalid_args -e -e 24245 -e 24245)
add_test(NAME args_no_params COMMAND
        ${CMAKE_CURRENT_BINARY_DIR}/arg_test -test no_param_args -g -h)