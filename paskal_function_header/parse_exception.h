//
// Created by kirant on 10.10.17.
//

#ifndef LAB2_PARSE_EXCEPTION_H
#define LAB2_PARSE_EXCEPTION_H


#include <exception>
#include <string>

struct parse_exception : public std::exception {
    const std::string message;

    const char *what() const throw() override {
        return message.c_str();
    }

    explicit parse_exception(std::string s) noexcept : message(std::move(s)) {}

    parse_exception(const std::string &s, int x) noexcept : message(s + " at position " + std::to_string(x)) {}

};


#endif //LAB2_PARSE_EXCEPTION_H
