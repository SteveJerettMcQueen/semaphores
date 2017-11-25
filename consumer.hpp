#ifndef _Consumer_H
#define _Consumer_H

#include <algorithm>
#include <vector>

bool is_vowel_pred(char a, char b);

char find_nearest_vowel(std::vector<char> range, std::vector<char> vowels);

int find_largest_distance(int d, int d2);

// Consumer consumes product
void *con_runner(void *arg);

#endif