////
//// Created by jaime on 8/28/2020.
////
#include <common/interceptor/posix.h>


FILE *fopen(const char *filename, const char *mode) {
    COMMON_DBGVAR(filename);
    MAP_OR_FAIL(fopen);
    return __real_fopen(filename, mode);;
}

int fclose(FILE *stream) {
    MAP_OR_FAIL(fclose);
    return __real_fclose(stream);
}

int fseek(FILE *stream, long int offset, int origin) {
    MAP_OR_FAIL(fseek);
    return __real_fseek(stream, offset, origin);
}

size_t fread(void *ptr, std::size_t size, std::size_t count, FILE *stream) {
    MAP_OR_FAIL(fread);
    return __real_fread(ptr, size, count, stream);
}

size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream) {
    MAP_OR_FAIL(fwrite);
    return __real_fwrite(ptr, size, count, stream);
}
