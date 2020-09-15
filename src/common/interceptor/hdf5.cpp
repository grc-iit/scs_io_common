//
// Created by anthony on 12/10/16.
//

#include <common/interceptor/hdf5.h>

hid_t H5Fopen(const char *name, unsigned flags, hid_t fapl_id) {
    MAP_OR_FAIL(H5Fopen);
    return __real_H5Fopen(name, flags, fapl_id);
}

hid_t H5Fcreate(const char *name, unsigned flags, hid_t fcpl_id, hid_t fapl_id) {
    MAP_OR_FAIL(H5Fcreate);
    return __real_H5Fcreate(name, flags, fcpl_id, fapl_id2);
}

hid_t H5Screate_simple(int rank, const hsize_t *current_dims, const hsize_t *maximum_dims) {
    MAP_OR_FAIL(H5Screate_simple);
    return __real_H5Screate_simple(rank, current_dims, maximum_dims);
}

hid_t H5Dcreate2(hid_t fileId, const char *name, hid_t dtype_id, hid_t space_id, hid_t lcpl_id, hid_t dcpl_id, hid_t dapl_id) {
    MAP_OR_FAIL(H5Dcreate2);
    return __real_H5Dcreate2(fileId, name, dtype_id, space_id, lcpl_id, dcpl_id, dapl_id);
}

herr_t H5Dwrite(hid_t dataset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t xfer_plist_id, void *buf) {
    MAP_OR_FAIL(H5Dwrite);
    return __real_H5Dwrite(dataset_id, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buf);
}

herr_t H5Dread(hid_t dataset_id, hid_t mem_type_id, hid_t mem_space_id, hid_t file_space_id, hid_t xfer_plist_id, void *buf) {
    MAP_OR_FAIL(H5Dread);
    return __real_H5Dread(dataset_id, mem_type_id, mem_space_id, file_space_id, xfer_plist_id, buf);
}

herr_t H5Dclose(hid_t dataset_id) {
    MAP_OR_FAIL(H5Dclose);
    return __real_H5Dclose(dataset_id);
}

herr_t H5Sclose(hid_t space_id) {
    MAP_OR_FAIL(H5Sclose);
    return __real_H5Sclose(space_id);
}

herr_t H5Fclose(hid_t file_id) {
    MAP_OR_FAIL(H5Fclose);
    return __real_H5Fclose(file_id);
}

hid_t H5Dopen2(hid_t loc_id, const char *name, hid_t dapl_id) {
    MAP_OR_FAIL(H5Dopen2);
    return __real_H5Dopen2(loc_id, name, dapl_id);
}

