//
// Created by lukemartinlogan on 9/1/20.
//

#ifndef COMMON_ERROR_H
#define COMMON_ERROR_H

#include <string>

namespace common::err {

class Error {
public:
    int code_ = 0;
    char msg_[2048] = {0};
    std::string fmt_;
    Error(int code, std::string fmt = "") : code_(code), fmt_(std::move(fmt)) {}
    template<typename ...Args>
    Error& format(Args ...args) {
        size_t length = 0;
        std::sprintf(msg_, fmt_.c_str(), args...);
        return *this;
    }
};

}

#endif //COMMON_ERROR_H
