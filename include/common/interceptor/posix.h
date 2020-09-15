//
// Created by jaime on 9/8/2020.
//

#ifndef COMMON_POSIX_H
#define COMMON_POSIX_H

#include <common/interceptor/interceptor.h>
#include <cstdio>

FORWARD_DECL(fopen,FILE *,(const char *filename, const char *mode));
FORWARD_DECL(fclose,int,(FILE *stream));
FORWARD_DECL(fseek,int,(FILE *stream, long int offset, int origin));
FORWARD_DECL(fread,size_t,(void *ptr, size_t size, size_t count, FILE *stream));
FORWARD_DECL(fwrite,size_t,(const void *ptr, size_t size, size_t count, FILE *stream));

FILE *fopen(const char *filename, const char *mode);
int fclose(FILE *stream);
int fseek(FILE *stream, long int offset, int origin);
size_t fread(void *ptr, std::size_t size, std::size_t count, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);

#endif //COMMON_POSIX_H
