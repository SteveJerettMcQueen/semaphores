#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
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
    
    // Randomly pick a letter from the alphabet
    srand((int)time(0));
    char letter = arg_struct->letters[(rand() % 26)];
    arg_struct->message = letter;
    
    // Producer writes content to the buffer 
    sprintf (arg_struct->buffer, "%c", arg_struct->message);
    std::cout << "Producer: " << arg_struct->buffer << std::endl;
    
    pthread_exit(0);
}