//
// Created by jaime on 9/8/2020.
//

#ifndef COMMON_MPI_H
#define COMMON_MPI_H

#include <common/interceptor/interceptor.h>
#ifdef ENABLE_MPI_INTERCEPTION
#include <mpi.h>

FORWARD_DECL(PMPI_File_open, int, (MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh));
FORWARD_DECL(PMPI_File_read, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_write, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_read_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_write_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_read_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_write_all, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_read_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_write_at_all, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_read_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_write_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_read_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_write_ordered, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status));
FORWARD_DECL(PMPI_File_read_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
FORWARD_DECL(PMPI_File_write_all_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
FORWARD_DECL(PMPI_File_read_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
FORWARD_DECL(PMPI_File_write_at_all_begin, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype));
FORWARD_DECL(PMPI_File_read_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
FORWARD_DECL(PMPI_File_write_ordered_begin, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype));
FORWARD_DECL(PMPI_File_iread, int, (MPI_File fh, void  *buf, int  count, MPI_Datatype  datatype, __D_MPI_REQUEST  *request));
FORWARD_DECL(PMPI_File_iwrite, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
FORWARD_DECL(PMPI_File_iread_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
FORWARD_DECL(PMPI_File_iwrite_at, int, (MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
FORWARD_DECL(PMPI_File_iread_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
FORWARD_DECL(PMPI_File_iwrite_shared, int, (MPI_File fh, void *buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request));
FORWARD_DECL(PMPI_File_sync, int, (MPI_File fh));
FORWARD_DECL(PMPI_File_set_view, int, (MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info));
FORWARD_DECL(PMPI_File_close, int, (MPI_File *fh));

int MPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh);
int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf,int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_all(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_all(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status);
int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, MPI_Status * status);
int MPI_File_read_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_write_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status *status);
int MPI_File_read_ordered(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status);
int MPI_File_write_ordered(MPI_File fh, void * buf, int count, MPI_Datatype datatype, MPI_Status * status);
int MPI_File_read_all_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype);
int MPI_File_write_all_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype);
int MPI_File_read_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype);
int MPI_File_write_at_all_begin(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype);
int MPI_File_read_ordered_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype);
int MPI_File_write_ordered_begin(MPI_File fh, void * buf, int count, MPI_Datatype datatype);
int MPI_File_iread(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request);
int MPI_File_iwrite(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request);
int MPI_File_iread_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request);
int MPI_File_iwrite_at(MPI_File fh, MPI_Offset offset, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST *request);
int MPI_File_iread_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request);
int MPI_File_iwrite_shared(MPI_File fh, void * buf, int count, MPI_Datatype datatype, __D_MPI_REQUEST * request);
int MPI_File_sync(MPI_File fh);
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info);
int MPI_File_close(MPI_File *fh);
#endif
#endif //COMMON_MPI_H
