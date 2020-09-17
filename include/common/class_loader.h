//
// Created by mani on 9/14/2020.
//

#ifndef COMMON_CLASS_LOADER_H
#define COMMON_CLASS_LOADER_H

#include <basket/common/singleton.h>
#include <common/data_structure.h>
#include <dlfcn.h>
#include <common/configuration_manager.h>
#include <common/error_codes.h>

class ClassLoader {
public:
    ClassLoader(){}

    template<typename T>
    std::shared_ptr<T> LoadClass(uint32_t class_id_);

private:
    void* m_job_handler;
};




#endif //COMMON_CLASS_LOADER_H
