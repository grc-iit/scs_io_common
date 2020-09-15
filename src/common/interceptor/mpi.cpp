//
// Created by jaime on 9/8/2020.
//

#include <common/interceptor/mpi.h>

#define _XOPEN_SOURCE 500
#define _GNU_SOURCE


int MPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh){
    MAP_OR_FAIL(PMPI_File_open);
    return __real_PMPI_File_open(comm, filename, amode, info, fh);
}

int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_read);
    return __real_PMPI_File_read(fh, buf, count, datatype, status);
}

int MPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_write);
    return __real_PMPI_File_write(fh, buf, count, datatype, status);
}

int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_read_at);
    return __real_PMPI_File_read_at(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_write_at);
    return __real_PMPI_File_write_at(fh, offset, buf, count, datatype, status);

}

int MPI_File_read_all(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_read_all);
    return __real_PMPI_File_read_all(fh, buf, count, datatype, status);
}

int MPI_File_write_all(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_write_all);
    return __real_PMPI_File_write_all(fh, buf, count, datatype, status);
}

int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status){
    MAP_OR_FAIL(PMPI_File_read_at_all);
    return __real_PMPI_File_read_at_all(fh, offset, buf, count, datatype, status);
}

int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status){
    MAP_OR_FAIL(PMPI_File_write_at_all);
    return __real_PMPI_File_write_at_all(fh, offset, buf,count, datatype, status);
}

int MPI_File_read_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_read_shared);
    return __real_PMPI_File_read_shared(fh, buf, count, datatype, status);
}

int MPI_File_write_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status){
    MAP_OR_FAIL(PMPI_File_write_shared);
    return __real_PMPI_File_write_shared(fh, buf, count, datatype, status);
}

int MPI_File_read_ordered(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status){
    MAP_OR_FAIL(PMPI_File_read_ordered);
    return __real_PMPI_File_read_ordered(fh, buf, count, datatype, status);
}

int MPI_File_write_ordered(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status){
    MAP_OR_FAIL(PMPI_File_write_ordered);
    return __real_PMPI_File_write_ordered(fh, buf, count, datatype, status);
}

int MPI_File_read_all_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype){
    MAP_OR_FAIL(PMPI_File_read_all_begin);
    return __real_PMPI_File_read_all_begin(fh, buf, count, datatype);
}

int MPI_File_write_all_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype){
    MAP_OR_FAIL(PMPI_File_write_all_begin);
    return __real_PMPI_File_write_all_begin(fh, buf, count, datatype);
}

int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype){
    MAP_OR_FAIL(PMPI_File_read_at_all_begin);
    return __real_PMPI_File_read_at_all_begin(fh, offset, buf, count, datatype);
}

int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype){
    MAP_OR_FAIL(PMPI_File_write_at_all_begin);
    return __real_PMPI_File_write_at_all_begin(fh, offset, buf, count, datatype);
}

int MPI_File_read_ordered_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype){
    MAP_OR_FAIL(PMPI_File_read_ordered_begin);
    return __real_PMPI_File_read_ordered_begin(fh, buf, count, datatype);
}

int MPI_File_write_ordered_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype){
    MAP_OR_FAIL(PMPI_File_write_ordered_begin);
    return __real_PMPI_File_write_ordered_begin(fh, buf, count, datatype);
}

int MPI_File_iread(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request){
    MAP_OR_FAIL(PMPI_File_iread);
    return __real_PMPI_File_iread(fh, buf, count, datatype, request);
}

int MPI_File_iwrite(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request){
    MPI_File_get_position(fh, &offset);
    return __real_PMPI_File_iwrite(fh, buf, count, datatype, request);
}

int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request){
    MAP_OR_FAIL(PMPI_File_iread_at);
    return __real_PMPI_File_iread_at(fh, offset, buf, count, datatype, request);
}

int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request){
    MAP_OR_FAIL(PMPI_File_iwrite_at);
    return __real_PMPI_File_iwrite_at(fh, offset, buf, count, datatype, request);
}

int MPI_File_iread_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request) {
    MAP_OR_FAIL(PMPI_File_iread_shared);
    return __real_PMPI_File_iread_shared(fh, buf, count, datatype, request);
}

int MPI_File_iwrite_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request){
    MPI_File_get_position_shared(fh, &offset);
    return __real_PMPI_File_iwrite_shared(fh, buf, count, datatype, request);
}

int MPI_File_sync(MPI_File fh){
    MAP_OR_FAIL(PMPI_File_sync);
    return __real_PMPI_File_sync(fh);
}

int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info){
    MAP_OR_FAIL(PMPI_File_set_view);
    return __real_PMPI_File_set_view(fh, disp, etype, filetype, datarep, info);
}

int MPI_File_close(MPI_File *fh){
    MAP_OR_FAIL(PMPI_File_close);
    return __real_PMPI_File_close(fh);
}
