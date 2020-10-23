#include "base64.h"
#include <iostream>
#include <algorithm>
#include <cmath>

const std::string Base64::alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string Base64::encode(const std::string &inp)
{
    // empty string
    if (inp.size() == 0)
    {
        return "";
    }

    // work in blocks of 3

    // get number of blocks
    int inpSize = static_cast<int>(std::ceil(static_cast<double>(inp.size()) / 3.0));
    // std::cout << inpSize << '\n';
    std::string res{};

    for (int i = 0; i < inpSize; i++)
    {
        // this is always given
        int i1 = inp[i * 3];
        res += Base64::alphabet[i1 >> 2];

        // check if second octet is set
        if (1 + i * 3 < inp.size())
        {
            int i2 = inp[1 + i * 3];
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
            res += Base64::alphabet[0x3F & i1 << 4];
            res += Base64::padding;
            res += Base64::padding;
        }
    }

    return res;
}

std::string Base64::decode(const std::string &inp)
{
    if (inp.size() == 0 | inp.size() % 4 != 0)
    {
        return "";
    }

    std::string res;

    int inpBlockCnt = static_cast<int>(inp.size() / 4.0);
    for (int i = 0; i < inpBlockCnt; i++)
    {
        int c1 = Base64::alphabet.find(inp[i * 4]);
        int c2 = Base64::alphabet.find(inp[i * 4 + 1]);

        // std::cout << c1 << ", " << c2 << ", " <<((c1 << 2) + (c2>>4)) << '\n';
        res.push_back(static_cast<char>((c1 << 2) + (c2 >> 4)));

        int cntBuffer = std::count_if(
            inp.begin() + (4 * i), inp.begin() + (4 * i + 4),
            [](const char c) { return c == Base64::padding; });

        switch (cntBuffer)
        {
        case 1:
        {
            int c3 = Base64::alphabet.find(inp[i * 4 + 2]);
            res.push_back(static_cast<char>((0x0F & c2) << 4) + (c3 >> 2));
        }
        break;

        case 0:
        {
            int c3 = Base64::alphabet.find(inp[i * 4 + 2]);
            int c4 = Base64::alphabet.find(inp[i * 4 + 3]);
            res.push_back(static_cast<char>((0x0F & c2) << 4) + (c3 >> 2));
            res.push_back(static_cast<char>((c3<<6) + c4));
        }
        break;

        default:
            break;
        }
    }
    return res;
}