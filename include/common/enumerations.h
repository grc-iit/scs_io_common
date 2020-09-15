//
// Created by Jie on 8/27/20.
//

#ifndef COMMON_ENUMERATIONS_H
#define COMMON_ENUMERATIONS_H

/*
 *  Enumerate IO Client Error Status, just for test
 */
typedef enum IOClientErrorStatus{
    IO_CLIENT_SUCCESS = 0,
    IO_CLIENT_FAILED = 1
} IOClientErrorStatus;

/**
 * IOClientType defines various types of IO Clients supported by COMMON
 */
typedef enum IOClientType{
    FILE_IO = 0,
    REDIS_IO = 1,
    MONGO_IO = 2
} IOClientType;

#endif //COMMON_ENUMERATIONS_H

