//
// Created by mani on 9/14/2020.
//

#ifndef COMMON_CLASS_LOADER_H
#define COMMON_CLASS_LOADER_H

#include <basket/common/singleton.h>
#include <common/data_structure.h>

class ClassLoader {
public:
    ClassLoader(){}

    void Load();

    std::shared_ptr<Job> LoadJob(uint32_t job_id_);

    std::shared_ptr<Task> LoadTask(uint32_t job_id_, uint32_t task_id_);

private:
    void* m_job_handler;
};


#endif //COMMON_CLASS_LOADER_H
