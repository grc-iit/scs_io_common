//
// Created by mani on 9/14/2020.
//

#include <common/class_loader.h>

void ClassLoader::Load() {
    // load the so file into memory
    m_job_handler = dlopen(COMMON_CONF->JOB_PATH.c_str(), RTLD_LAZY);
}

std::shared_ptr<Job> ClassLoader::LoadJob(uint32_t job_id_){
    dlerror(); // clear error code
    // find Job by job_id within the memory so
    std::string job_symbol = "create_job_" + std::to_string(job_id_);
    std::shared_ptr<Job> (*create_job_fun)();
    create_job_fun = (std::shared_ptr<Job> (*)())dlsym(m_job_handler, job_symbol.c_str());
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

std::shared_ptr<Task> ClassLoader::LoadTask(uint32_t job_id_, uint32_t task_id_){
    // find Job by job_id within the memory so
    std::shared_ptr<Job> job = LoadJob(job_id_);
    // find task by task_id
    std::shared_ptr<Task> task = job->GetTask(task_id_);
    return task;
}
