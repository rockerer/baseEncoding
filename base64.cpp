#include "base64.h"
#include <iostream>
#include <cmath>

const std::string Base64::alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Base64::encode(const std::string &inp)
{
    // empty string
    if(inp.size() == 0) {
        return "";
    }

    // work in blocks of 3

    // get number of blocks
    int inpSize = static_cast<int>(std::ceil(static_cast<double>(inp.size()) / 3.0));
    // std::cout << inpSize << '\n';
    std::string res{};

    for(int i = 0; i < inpSize; i++) {
        // this is always given
        int i1 = inp[i * 3];
        res += Base64::alphabet[i1 >> 2];
        
        // check if second octet is set
        if (1 + i * 3 < inp.size())
        {
            int i2 =inp[1 + i * 3];
            res += Base64::alphabet[0x3F & ((i1 << 4) | (i2 >> 4))];

            // check if third octet is set
            if (2 + i * 3 < inp.size())
            {
                int i3 = inp[2 + i * 3];
                res += Base64::alphabet[0x3F & ((i2 << 2) | (i3 >> 6))];
                res += Base64::alphabet[0x3F & i3];
            }
            else
            {
                res += Base64::alphabet[0x3F & (i2 << 2)];
                res += Base64::padding;
            }
        }
        else
        {
            res += Base64::alphabet[0x3F &i1 << 4];
            res += Base64::padding;
            res += Base64::padding;
        }
    }

    return res;
}