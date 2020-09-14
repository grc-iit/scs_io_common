cmake_minimum_required(VERSION 3.10)
project(scs_io_common VERSION 1.0.0 DESCRIPTION "")
set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(include)

set(COMMON_SRC src/common/class_loader.cpp include/common/class_loader.h)

add_library(scs_io_common SHARED ${COMMON_SRC})