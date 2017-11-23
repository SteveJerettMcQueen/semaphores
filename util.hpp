#ifndef _Util_H
#define _Util_H

#include <map>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

// Structure for producer and consumer threads
struct content_struct{
    char vowel;
    char vowel2;
    char message;
    char buffer[3];
    std::vector<char> letters;
    std::vector<char> vowels;
    std::map<char, int> location_map;
};

#endif