#pragma once
#ifndef MY_EXCEPTION_H_
#define MY_EXCEPTION_H_
#include <string>
#include <stdexcept>
/* 异常类，用于捕获wstring类型的异常消息 */
class MyException : public std::runtime_error {
public:
    MyException(const std::wstring& msg)
        : runtime_error("Error"), message_(msg) {
    }
    ~MyException() throw() {}
    std::wstring message() { return message_; }
private:
    std::wstring message_;
};

#endif