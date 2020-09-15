//
// Created by jaime on 9/8/2020.
//

#ifndef COMMON_INTERCEPTOR_H
#define COMMON_INTERCEPTOR_H


#include <common/debug.h>
#include <dlfcn.h>

#define FILE_BUFFER_CAPACITY 4096
#define FORWARD_DECL(name, ret, args) typedef ret(*__real_t_##name)args;
#define MAP_OR_FAIL(func)                                                      \
    __real_t_##func __real_##func;                                         \
    __real_##func = (__real_t_##func)dlsym(RTLD_NEXT,#func);

#endif //COMMON_INTERCEPTOR_H
