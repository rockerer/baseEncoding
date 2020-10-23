#pragma once

#include "base.h"

struct Base64 : Base {
    static std::string decode(const std::string &);
    static std::string encode(const std::string &);
    private:
        static const std::string alphabet;// = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        static const char padding{'='};
};