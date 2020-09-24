//
// Created by mani on 8/24/2020.
// It is the interface for all IO clients defined
//

#ifndef COMMON_IO_H
#define COMMON_IO_H

#include <common/data_structure.h>
#include <common/configuration_manager.h>

class IOClient {
protected:
    std::shared_ptr<StorageSolution> solution;
public:
    IOClient(uint16_t storage_index){
        auto iter = COMMON_CONF->STORAGE_SOLUTIONS.find(storage_index);
        if(iter != COMMON_CONF->STORAGE_SOLUTIONS.end()) solution = iter->second;
        else{
            //TODO: throw exception
            throw ErrorException(INVALID_STORAGE_INDEX);
        }
    }
    /**
     * Virtual Methods
     */
     /**
      * Reads data from source into destination buffer while respecting the position_
      */
     virtual void Read(Data &source, Data &destination){}

     /**
      * Writes data from source into destination buffer while respecting the position_
      *
      */
     virtual void Write(Data &source, Data &destination){}
    /**
     * Remove
     *
     */
    virtual bool Remove(Data &source){}
    /**
     * Size
     *
     */
    virtual size_t Size(Data &source){}
};


#endif //COMMON_IO_H
