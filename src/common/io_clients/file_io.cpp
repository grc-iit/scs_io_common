//
// Created by mani on 8/24/2020.
//

#include <common/debug.h>
#include <fcntl.h>
#include <string>
#include <common/error_codes.h>
#include <common/io_clients/file_io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void FileIOClient::Read(Data &source, Data &destination) {
    AUTO_TRACER("FileIOClient::Read", source, destination);
    const char *file_name = source.id_.c_str();
    int fileFd = open(file_name, O_RDONLY);
    if (fileFd == -1) {
        throw ErrorException(OPEN_FILE_FAILED);
    } else {
        auto file_size = lseek(fileFd, 0L, SEEK_END);
        if (lseek(fileFd, source.position_, SEEK_SET) == -1) {
            close(fileFd);
            throw ErrorException(SEEK_FILE_FAILED);
        } else {
            auto source_data_size = source.data_size_;
            if (source.data_size_ == 0) {
                source_data_size = file_size - source.position_;
            }
            destination.buffer_= static_cast<char *>(malloc(source_data_size));
            size_t data_size = read(fileFd, destination.buffer_ + destination.position_, source_data_size);
            if (data_size == source_data_size) {
                destination.data_size_=data_size;
                // read data from file successful
                close(fileFd);
            } else {
                // read data from file failed.
                close(fileFd);
                throw ErrorException(READ_DATA_FROM_FILE_FAILED);
            }
        }
    }
    COMMON_DBGVAR(destination);
}

void FileIOClient::Write(Data &source, Data &destination) {
    AUTO_TRACER("FileIOClient::Write", source, destination);
    const char *dest_file_name = destination.id_.c_str();
    int fileFd = open(dest_file_name, O_RDWR | O_CREAT, 0644);
    if (fileFd == -1) {
        throw ErrorException(OPEN_FILE_FAILED);
    } else {
        if (lseek(fileFd, destination.position_, SEEK_SET) == -1) {
            close(fileFd);
            throw ErrorException(SEEK_FILE_FAILED);
        } else {
            ssize_t size = write(fileFd, source.buffer_ + source.position_,
                                 source.data_size_ - source.position_);
            COMMON_DBGVAR(size);
            if (size < source.data_size_ - source.position_) {
                // write data to file failed
                close(fileFd);
                throw ErrorException(WRITE_DATA_TO_FILE_FAILED);
            }
            close(fileFd);
        }
    }
}

bool FileIOClient::Remove(Data &source) {
    AUTO_TRACER("FileIOClient::Remove", source);
    remove(source.id_.c_str());
    return true;
}

size_t FileIOClient::Size(Data &source) {
    if(boost::filesystem::exists(source.id_.c_str())){
        return boost::filesystem::file_size(source.id_.c_str());
    }
    return 0;
}
