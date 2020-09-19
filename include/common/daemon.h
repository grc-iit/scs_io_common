//
// Created by jaime on 9/16/20.
//

#ifndef SENTINEL_COMMON_DAEMON_H
#define SENTINEL_COMMON_DAEMON_H

#include <fstream>
#include <csignal>
#include <execinfo.h>
#include <unistd.h>
#include <future>

#include <basket/common/singleton.h>
#include <mpi.h>
#include <thread>
#include <basket/common/data_structures.h>
#include <basket/common/macros.h>

namespace common {
    template<class T>
    class Daemon {
    public:
        static CharStruct main_log_file;
        std::promise<void> exitSignal;
        std::thread worker;
        std::shared_ptr<T> daemon_manager_;
        bool spawn_thread_;
        bool wait_;
        bool is_running_;

        Daemon(CharStruct main_log_file = "/tomp/tmp.BUKlhPiLxF/build/single_node_common_server.lg", bool spawn_thread=false, bool wait=true): wait_(wait),daemon_manager_(),spawn_thread_(spawn_thread) {

        }

        void Run(){
            main_log_file = Daemon<T>::main_log_file;
            std::future<void> futureObj = exitSignal.get_future();
            daemon_manager_ = basket::Singleton<T>::GetInstance();
            catchSignals();
            is_running_=true;
            if(spawn_thread_) {
                worker = std::thread(&T::Run, daemon_manager_.get(), std::move(futureObj), this);
                MPI_Barrier(MPI_COMM_WORLD);
                if(BASKET_CONF->MPI_RANK == 0){
                    printf("Running\n");
                }
                if(wait_) while(true) sleep(1);
            }
            else {
                MPI_Barrier(MPI_COMM_WORLD);
                if(BASKET_CONF->MPI_RANK == 0){
                    printf("Running\n");
                }
                daemon_manager_->Run(std::move(futureObj), this);
            }
        }

        void Stop(){
            if(is_running_){
                exitSignal.set_value();
                if(spawn_thread_){
                    worker.join();
                }
                is_running_=false;
            }
        }
        ~Daemon(){
            Stop();
        }

    private:
        static void signalHandler(int sig){
            auto instance = basket::Singleton<common::Daemon<T>>::GetInstance();
            switch (sig) {
                case SIGHUP: {
                    logMessage(instance->main_log_file.c_str(), "hangup signal caught");
                    break;
                }
                case SIGTERM: {
                    logMessage(instance->main_log_file.c_str(), "terminate signal caught");
                    //finalize(); Handle by the destructor
                    MPI_Finalize();
                    exit(0);
                }
                default: {
                    void *array[20];
                    size_t size;
                    // get void*'s for all entries on the stack
                    size = backtrace(array, 20);
                    // print out all the frames to stderr
                    fprintf(stderr, "Error: signal %d:\n", sig);
                    backtrace_symbols_fd(array, size, STDERR_FILENO);
                    ::raise(SIGTERM);
                }
            }
        }

        static void logMessage(const std::string &filename, const std::string &message){
            std::ofstream outfile;
            outfile.open(filename, std::ios_base::app); // append instead of overwrite
            outfile << message;
        }

        void catchSignals(){
            signal(SIGTERM, common::Daemon<T>::signalHandler); /* catch kill signal */
            signal(SIGHUP, common::Daemon<T>::signalHandler); /* catch hangup signal */
            signal(SIGABRT, common::Daemon<T>::signalHandler); /* catch hangup signal */
            signal(SIGSEGV, common::Daemon<T>::signalHandler); /* catch hangup signal */
            signal(SIGBUS, common::Daemon<T>::signalHandler); /* catch hangup signal */
            signal(SIGCHLD, SIG_IGN);              /* ignore child */
            signal(SIGTSTP, SIG_IGN);              /* ignore tty signals */
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
        }

    };

    template<typename T>
    CharStruct common::Daemon<T>::main_log_file = "";
}

#endif //SENTINEL_COMMON_DAEMON_H
