cmake_minimum_required(VERSION 3.10)
project(scs_io_common VERSION 1.0.0 DESCRIPTION "")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -g -DBASKET_ENABLE_RPCLIB")

include_directories(src)
include_directories(include)

set(COMMON_SRC include/common/arguments.h include/common/debug.h
        include/common/error.h include/common/rng.h include/common/configuration_manager.h include/common/constants.h
        src/common/data_structure.cpp include/common/data_structure.h include/common/enumerations.h include/common/error.h
        include/common/error_definition.h include/common/error_codes.h)
set(IO_CLIENTS_SRC src/common/io_clients/file_io.cpp src/common/io_clients/mongo_io.cpp src/common/io_clients/redis_io.cpp
        include/common/io_clients/file_io.h include/common/io_clients/io.h include/common/io_clients/io_factory.h
        include/common/io_clients/mongo_io.h include/common/io_clients/redis_io.h)
set(INTERCEPTOR_SRC src/common/interceptor/hdf5.cpp src/common/interceptor/mpi.cpp src/common/interceptor/posix.cpp
        include/common/interceptor/hdf5.h include/common/interceptor/interceptor.h include/common/interceptor/mpi.h
        include/common/interceptor/posix.h)

SET(CLASS_LOADER include/common/class_loader.h)

add_library(scs_io_common SHARED ${COMMON_SRC} ${IO_CLIENTS_SRC} ${INTERCEPTOR_SRC} ${CLASS_LOADER})
target_link_libraries(scs_io_common -lboost_system -lboost_filesystem -ldl -lbasket)

option(BUILD_TEST "Build the unit tests" ON)
if(BUILD_TEST)
    enable_testing()
    include(CTest)
    add_subdirectory(test/unit)
endif()
