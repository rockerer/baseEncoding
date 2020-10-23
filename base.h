#pragma once

#include <string>

class Base {
    Base() = delete;
    static std::string encode(const std::string &);
    static std::string decode(const std::string &);
};