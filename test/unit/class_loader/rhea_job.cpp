//
// Created by yejie on 9/16/20.
//

#include <basket/common/singleton.h>
#include <common/data_structure.h>
#include <stdio.h>

extern "C" std::shared_ptr<Job> create_job_1() {
    printf("Begin to create object.....\n");
    return basket::Singleton<Job>::GetInstance();
}
extern "C" void free_job(Job* p) { delete p; }


