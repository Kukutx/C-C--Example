#pragma once
#ifndef MY_EXCEPTION_H_
#define MY_EXCEPTION_H_
#include <string>
#include <stdexcept>
/* �쳣�࣬���ڲ���wstring���͵��쳣��Ϣ */
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