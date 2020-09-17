/*
 * Copyright (C) 2019  SCS Lab <scs-help@cs.iit.edu>, Hariharan
 * Devarajan <hdevarajan@hawk.iit.edu>, Luke Logan
 * <llogan@hawk.iit.edu>, Xian-He Sun <sun@iit.edu>
 *
 * This file is part of HCompress
 *
 * HCompress is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/*-------------------------------------------------------------------------
*
* Created: debug.h
* June 5 2018
* Hariharan Devarajan <hdevarajan@hdfgroup.org>
*
* Purpose: Defines debug macros for Hermes.
*
*-------------------------------------------------------------------------
*/


#ifndef COMMON_DEBUG_PROJECT_H
#define COMMON_DEBUG_PROJECT_H

#include <iostream>
#include <csignal>
#include <unistd.h>
#include <execinfo.h>
#include <sstream>
#include <stack>
#include <string>
#include <iostream>
#include <stdarg.h>
#include <chrono>
#include <mpi.h>
#include <string>
#include <tuple>

#if (defined(COMMON_DEBUG_TRACE) || defined(COMMON_DEBUG_TIMER) || defined(ENABLE_AUTO_TRACER)) && !defined(DISABLE_AUTO_TRACER)
#define AUTO_TRACER(...) common::debug::AutoTrace trace(__VA_ARGS__);
#else
#define AUTO_TRACER(...)
#endif

template <class Tup, class Func, std::size_t ...Is>
constexpr void static_for_impl(Tup&& t, Func &&f, std::index_sequence<Is...> )
{
    ( f(std::integral_constant<std::size_t, Is>{}, std::get<Is>(t)),... );
}

template <class ... T, class Func >
constexpr void static_for(std::tuple<T...>&t, Func &&f)
{
    static_for_impl(t, std::forward<Func>(f), std::make_index_sequence<sizeof...(T)>{});
}

namespace common::debug{
    /**
 * Handles signals and prints stack trace.
 *
 * @param sig
 */
    static void handler(int sig) {
        void *array[10];
        size_t size;
        // get void*'s for all entries on the stack
        size = backtrace(array, 300);
        int rank, comm_size;
        // print out all the frames to stderr
        fprintf(stderr, "Error: signal %d\n", sig);
        backtrace_symbols_fd(array, size, STDERR_FILENO);
        exit(0);
    }


/**
 * various macros to print variables and messages.
 */

#ifdef COMMON_DEBUG_MSG
    #define COMMON_DBGVAR(var) \
std::cout << "DBG: " << __FILE__ << "(" << __LINE__ << ") "\
       << #var << " = [" << (var) << "]" << std::endl

#define COMMON_DBGVAR2(var1, var2) \
  std::cout << "DBG: " << __FILE__ << "(" << __LINE__ << ") "\
       << #var1 << " = [" << (var1) << "]"\
       << #var2 << " = [" << (var2) << "]"  << std::endl
#define COMMON_DBGVAR3(var1, var2, var3) \
  std::cout << "DBG: " << __FILE__ << "(" << __LINE__ << ") "\
       << #var1 << " = [" << (var1) << "]"\
       << #var2 << " = [" << (var2) << "]"\
       << #var3 << " = [" << (var3) << "]"  << std::endl

#define COMMON_DBGMSG(msg) \
  std::cout << "DBG: " << __FILE__ << "(" << __LINE__ << ") " \
       << msg << std::endl
#else
#define COMMON_DBGVAR(var)
#define COMMON_DBGVAR2(var1, var2)
#define COMMON_DBGVAR3(var1, var2, var3)
#define COMMON_DBGMSG(msg)
#endif

/**
 * Time all functions and instrument it
 */

class Timer {
public:
    Timer():time_elapsed(0){}
    void startTime() {
        t1 = std::chrono::high_resolution_clock::now();
        time_elapsed=0;
    }
    __attribute__((always_inline)) void resumeTime() {
        t1 = std::chrono::high_resolution_clock::now();
    }
    __attribute__((always_inline)) void pauseTime() {
        auto t2 = std::chrono::high_resolution_clock::now();
        time_elapsed +=  std::chrono::duration_cast<std::chrono::nanoseconds>(
                t2 - t1).count();
    }
    double endTime(){
        auto t2 = std::chrono::high_resolution_clock::now();
        time_elapsed +=  std::chrono::duration_cast<std::chrono::nanoseconds>(
                t2 - t1).count();
        return time_elapsed/1000000.0;
    }

    double getTimeElapsed(){
        return time_elapsed/1000000.0;
    }
public:
    std::chrono::high_resolution_clock::time_point t1;
    double time_elapsed;
};
/**
 * Implement Auto tracing Mechanism.
 */
using namespace std;
class AutoTrace
{
    Timer timer;
    static int rank,item;

public:
    template <typename... Args>
    AutoTrace(std::string string,Args... args):m_line(string)
    {

        char thread_name[256];
        pthread_getname_np(pthread_self(), thread_name,256);
        std::stringstream stream;

        if(rank == -1) MPI_Comm_rank(MPI_COMM_WORLD, &rank);
#if defined(COMMON_DEBUG_TRACE) || defined(COMMON_DEBUG_TIMER)
        //stream << "\033[31m";
    stream <<++item<<";"<<thread_name<<";"<< rank << ";" <<m_line << ";";
#endif
#if  defined(COMMON_DEBUG_TIMER)
        stream <<";;";
#endif
#ifdef COMMON_DEBUG_TRACE
        auto args_obj = std::make_tuple(args...);
    const ulong args_size = std::tuple_size<decltype(args_obj)>::value;
    stream << "args(";
    if(args_size == 0) stream << "Void";
    else{
        static_for(args_obj, [&] (auto i, auto w) {
            stream << w << ", ";
        });
    }
    stream << ");";
#endif
#if defined(COMMON_DEBUG_TRACE) || defined(COMMON_DEBUG_TIMER)
        stream <<"start"<< endl;
    stream << "\033[00m";
    cout << stream.str();
#endif
#ifdef COMMON_DEBUG_TIMER
        timer.startTime();
#endif
    }

    ~AutoTrace()
    {
        std::stringstream stream;
        char thread_name[256];
        pthread_getname_np(pthread_self(), thread_name,256);
        //stream << "\033[31m";
#if defined(COMMON_DEBUG_TRACE) || defined(COMMON_DEBUG_TIMER)
        stream <<item-- <<";"<<std::string(thread_name)<<";"<< rank << ";" << m_line << ";";
#endif
#if defined(COMMON_DEBUG_TRACE)
        stream  <<";";
#endif
#ifdef COMMON_DEBUG_TIMER
        double end_time=timer.endTime();
    stream  <<end_time<<";msecs;";
#endif
#if defined(COMMON_DEBUG_TRACE) || defined(COMMON_DEBUG_TIMER)
        stream  <<"finish"<< endl;
    stream << "\033[00m";
    cout << stream.str();
#endif
    }
private:
    string m_line;
};
}


#endif //DEBUG_DEBUG_H
