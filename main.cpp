#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "base64.h"

// TODO: finish me
static std::string helpText{"Usage:\n"};

void test1() {
    std::cout << Base64::encode("") << '\n';
    std::cout << Base64::encode("f") << '\n';
    std::cout << Base64::encode("fo") << '\n';
    std::cout << Base64::encode("foo") << '\n';
    std::cout << Base64::encode("foob") << '\n';
    std::cout << Base64::encode("fooba") << '\n';
    std::cout << Base64::encode("foobar") << '\n';
    // Base64::encode("abcde");
}

int main(int argc, char **argv) {
    // parse arguments, w/o filename
    std::vector<std::string> args;
    for(int i = 1; i < argc; i++)
        args.push_back(argv[i]);
    

    // print help text if no args given or -h
    if(argc == 1 | std::find(args.begin(), args.end(), "-h") != args.end()) {
        std::cout << helpText << '\n';
        return 0;
    }


    test1();
}