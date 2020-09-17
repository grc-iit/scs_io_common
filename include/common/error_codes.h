//
// Created by Jie on 8/28/20.
//

#ifndef COMMON_ERROR_CODES_H
#define COMMON_ERROR_CODES_H

#include <common/error_definition.h>

/*
 * Errorcodes used in COMMON
 */
const ErrorCode SUCCESSFUL = {0, "SUCCESSFUL"};

// io_clients module error code
const ErrorCode OPEN_FILE_FAILED = {1000, "Open file failed"};
const ErrorCode SEEK_FILE_FAILED = {1001, "Seek the position from file failed"};
const ErrorCode READ_DATA_FROM_FILE_FAILED = {1002, "Read data from file failed"};
const ErrorCode WRITE_DATA_TO_FILE_FAILED = {1003, "Write data to file failed"};
const ErrorCode REDIS_SERVER_SIDE_FAILED = {1004, "Redis server maybe failed"};
const ErrorCode READ_REDIS_POSITION_OR_SIZE_FAILED = {1005, "Error read position or data size when reading data from Redis Cluster"};
const ErrorCode READ_REDIS_DATA_FAILED = {1006, "Read data from Redis Cluster failed"};
const ErrorCode WRITE_REDIS_DATA_FAILED = {1007, "Write data to Redis Cluster failed"};
const ErrorCode READ_MONGODB_DATA_FAILED = {1008, "Read data from Mongodb failed"};
const ErrorCode WRITE_MONGODB_DATA_FAILED = {1009, "Write data to Mongodb failed"};
const ErrorCode READ_MONGO_POSITION_OR_SIZE_FAILED = {1010, "Error read position or data size when reading data from Mongodb"};
const ErrorCode MONGODB_SERVER_SIDE_FAILED = {1011, "Mongodb server maybe failed"};
const ErrorCode CONNECT_REDIS_SERVER_ERROR = {1012, "Connect Redis Cluster failed"};
const ErrorCode CONNECT_MONGO_SERVER_ERROR = {1013, "Connect Mongo Cluster failed"};
const ErrorCode CREATE_MONGO_CLIENT_ERROR = {1014, "Create Mongo Client failed"};
const ErrorCode CONNECT_MONGO_DATABASE_ERROR = {1015, "Cannot connect to mongo database"};
const ErrorCode CONNECT_MONGO_COLLECTION_ERROR = {1016, "Cannot connect to mongo collection"};
const ErrorCode FILE_PATH_NON_EXISTANCE = {1017, "The file io path is non existance"};
const ErrorCode INVALID_STORAGE_INDEX={1018, "Invalid storage index"};
const ErrorCode UNDEFINED_ENV_VARIABLE = {2011, "The environment variable is not defined %s"};
const ErrorCode NOT_FOUND_CLASS={3000, "Not found the requested class by class_id"};

#endif //COMMON_ERROR_CODES_H
