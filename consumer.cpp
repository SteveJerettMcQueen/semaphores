#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include <pthread.h>

#include "consumer.hpp"
#include "util.hpp"

char find_vowel(std::vector<char> range, std::vector<char> vowels){
    std::cout << "myvector contains: ";
    for(int i = 0; i < range.size(); i++){
        std::cout << range[i] << " ";
    }
    
    std::cout << std::endl;
}

void *con_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;

    // Consumer reads content from the buffer and finds
    // location of the letter in the alphabet
    char letter = arg_struct->buffer[0];
    int location = arg_struct->location_map.find(letter)->second + 1;
    bool is_even = (location % 2 == 0);
    
    if(is_even){
        
        std::cout << "Even" << std::endl;
        
        // Find closest vowel to left of the letter
        std::vector<char>::iterator b = arg_struct->letters.begin();
        std::vector<char>::iterator e = arg_struct->letters.begin() + (location - 1);
        std::vector<char> left_range(b, e);
        std::reverse(left_range.begin(), left_range.end());
        char left_vowel = find_vowel(left_range, arg_struct->vowels);

        // Find closest vowel to right of the letter
        std::vector<char>::iterator b2 = arg_struct->letters.begin() + location;
        std::vector<char>::iterator e2 = arg_struct->letters.end();
        std::vector<char> right_range(b2, e2);
        char right_vowel = find_vowel(right_range, arg_struct->vowels);

    } else {
        
        std::cout << "Consumer: " << letter << " Location: " << location << std::endl;
        
    }
    
    pthread_exit(0);
}
