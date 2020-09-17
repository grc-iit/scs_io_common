//
// Created by mani on 9/14/2020.
//

#include <common/class_loader.h>

template<typename T>
std::shared_ptr<T> ClassLoader::LoadClass(uint32_t class_id_) {
    m_job_handler = dlopen(COMMON_CONF->JOB_PATH.c_str(), RTLD_LAZY);
    dlerror(); // clear error code
    // find Job by job_id within the memory so
    std::string job_symbol = "create_job_" + std::to_string(class_id_);
    std::shared_ptr<T> (*create_job_fun)();
    create_job_fun = (std::shared_ptr<T> (*)())dlsym(m_job_handler, job_symbol.c_str());
    const char *dlsym_error = NULL;
    if ((dlsym_error = dlerror()) != NULL){
        //throw exception
        return NULL;
        //throw ErrorException(UNDEFINED_ENV_VARIABLE);
    } else {
        // create Job instance
        return create_job_fun();
    }
}