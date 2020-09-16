//
// Created by yejie on 9/16/20.
//

#include <common/class_loader.h>
#include <common/error_codes.h>

int main(int argc, char* argv[]){
    ClassLoader class_loader;
    // load so file
    class_loader.Load();

    std::shared_ptr<Job> job = class_loader.LoadJob(2);
    job->test();
    std::shared_ptr<Task> task = class_loader.LoadTask(1, 2);
    task->execute();

}

