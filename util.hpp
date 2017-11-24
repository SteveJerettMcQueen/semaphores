#ifndef _Util_H
#define _Util_H

#include <array>
#include <map>
#include <vector>

// Structure for producer and consumer threads
struct content_struct{
    std::array<char,3> buffer;
    std::vector<char> letters, vowels;
    std::map<char, int> location_map;
};

#endif