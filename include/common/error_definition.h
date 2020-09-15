//
// Created by Jie on 8/27/20.
//

#ifndef COMMON_ERROR_CODE_H
#define COMMON_ERROR_CODE_H

#include <string>
#include <exception>
#include <common/debug.h>

typedef struct ErrorCode{
private:
    int code_;
    std::string message_;

public:
    ErrorCode(int code, std::string message): code_(code), message_(message){}

    int getCode() const {return code_;}
    std::string getMessage() const {return message_;}
    void setMessage(std::string message) {message_=message;}
} ErrorCode;

class ErrorException: public std::exception{
private:
    bool replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos)
            return false;
        str.replace(start_pos, from.length(), to);
        return true;
    }
public:
    template <typename... Args>
    ErrorException(ErrorCode errorcode,Args... args): errorCode_(errorcode){

        std:: string error_message_ = std::to_string(errorCode_.getCode());
        error_message_ += "\t";
        error_message_ += errorCode_.getMessage();
        auto args_obj = std::make_tuple(args...);
        const ulong args_size = std::tuple_size<decltype(args_obj)>::value;

        if(args_size != 0) {
            static_for(args_obj, [&] (auto i, auto w) {
                replace(error_message_,"%s",w);
            });
            errorCode_.setMessage(error_message_);
        }

    }

    const char* what() const throw() {
        perror(errorCode_.getMessage().c_str());
        return errorCode_.getMessage().c_str();
    }

private:
    ErrorCode errorCode_;
};

#endif //COMMON_ERROR_CODE_H

