//
// Created by mani on 8/24/2020.
// It is the implementation of File IO Client.
//

#ifndef COMMON_FILE_IO_H
#define COMMON_FILE_IO_H

#include <common/io_clients/io.h>

class FileIOClient: public IOClient  {
public:
    /**
     * Constructor
     */
    FileIOClient(uint16_t storage_index):IOClient(storage_index){
        auto file_solution = std::static_pointer_cast<FileSS>(solution);
        if(!boost::filesystem::exists(file_solution->end_point_.c_str())){
            throw ErrorException(FILE_PATH_NON_EXISTANCE);
        }
    }

    /*
     * Methods
     */

    /*
     * Reads data from source into destination buffer while respecting the position_
     */
    void Read(Data &source, Data &destination) override;

    /*
     * Writes data from source into destination buffer while respecting the position_
     */
    void Write(Data &source, Data &destination) override;

    bool Remove(Data &source) override;

    size_t Size(Data &source) override;

};


#endif //COMMON_FILE_IO_H
