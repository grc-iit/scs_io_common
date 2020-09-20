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
    ClassLoader(){ m_job_handler = nullptr; }

    template<typename T>
    std::shared_ptr<T> LoadClass(uint32_t class_id_) {
        /**
         * TODO: please test this logic. we want JOB_PATH to be a dir and we will check for the symbol in each so present in the directory.
         * Also please calculate the cost of finding symbol in such a case.
         */
        using namespace boost::filesystem;
        std::string path = COMMON_CONF->JOB_PATH.string();
        recursive_directory_iterator dir( path.c_str()), end;
        while (dir != end)
        {
            m_job_handler = dlopen(dir->path().string().c_str(), RTLD_LAZY);
            if(!m_job_handler){
                printf("Could not open so");
            }
            dlerror(); // clear error code
            // find Job by job_id within the memory so
            std::string job_symbol = "create_job_" + std::to_string(class_id_);
            std::shared_ptr<T> (*create_job_fun)();
            create_job_fun = (std::shared_ptr<T> (*)())dlsym(m_job_handler, job_symbol.c_str());
            const char *dlsym_error = NULL;
            if ((dlsym_error = dlerror()) != NULL){
                ++dir;
                continue;
            } else {
                // create Job instance
                return create_job_fun();
            }
            ++dir;

        }
        throw ErrorException(NOT_FOUND_CLASS);

    }

private:
    void* m_job_handler;
};
#endif //COMMON_CLASS_LOADER_H
