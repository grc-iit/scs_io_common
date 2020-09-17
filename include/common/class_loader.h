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
#include <boost/filesystem.hpp>

class ClassLoader {
public:
    ClassLoader(){}

    template<typename T>
    std::shared_ptr<T> LoadClass(uint32_t class_id_) {
        boost::filesystem::recursive_directory_iterator iter(COMMON_CONF->JOB_PATH);
        boost::filesystem::recursive_directory_iterator end;
        while (iter != end)
        {
            error_code ec;
            // Increment the iterator to point to next entry in recursive iteration
            iter.increment(ec);
            if (ec) {
                m_job_handler = dlopen(iter->path().string().c_str(), RTLD_LAZY);
                dlerror(); // clear error code
                // find Job by job_id within the memory so
                std::string job_symbol = "create_job_" + std::to_string(class_id_);
                std::shared_ptr<T> (*create_job_fun)();
                create_job_fun = (std::shared_ptr<T> (*)())dlsym(m_job_handler, job_symbol.c_str());
                const char *dlsym_error = NULL;
                if ((dlsym_error = dlerror()) != NULL){
                    continue
                } else {
                    // create Job instance
                    return create_job_fun();
                }
            }
        }
        //TODO:throw exception
        return NULL;

    }

private:
    void* m_job_handler;
};




#endif //COMMON_CLASS_LOADER_H
