#include <ctime>
#include <iostream>

#include <pthread.h>

#include "producer.hpp"
#include "util.hpp"

void *prod_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;
    
    // Producer produces content
    arg_struct->letters = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    arg_struct->vowels = {'A', 'E', 'I', 'O', 'U'};

    // Store corresponding letters in a map
    for(int i = 0; i < arg_struct->letters.size(); i++){
        arg_struct->location_map.insert(std::pair<char, int> (arg_struct->letters[i], i));
    }
    
    srand((int)time(0));
    for(int i = 0; i < arg_struct->buffer.size(); i++){
        // Randomly pick a letter from the alphabet
        int rand_index = (rand() % arg_struct->letters.size());
        char letter = arg_struct->letters[rand_index];

        // Producer writes content to the buffer 
        arg_struct->buffer.at(i) = letter;
        std::cout << "Producer: " << arg_struct->buffer.at(i) << std::endl;
    }

    pthread_exit(0);
}