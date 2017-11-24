#include <ctime>
#include <iostream>

#include <pthread.h>
#include <semaphore.h>

#include "producer.hpp"
#include "util.hpp"

void *prod_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;
    
    arg_struct->mutex = PTHREAD_MUTEX_INITIALIZER;
    
    // Producer produces content
    pthread_mutex_lock(&arg_struct->mutex);
    
    // Enter critical section of shared resource
    arg_struct->letters = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    arg_struct->vowels = {'A', 'E', 'I', 'O', 'U'};
    // Exit critical section of shared resource
    
    pthread_mutex_unlock(&arg_struct->mutex);

    // Store corresponding letters in a map
    for(int i = 0; i < arg_struct->letters.size(); i++){
        arg_struct->location_map.insert(std::pair<char, int> (arg_struct->letters[i], i));
    }
    
    // Producer writes content to the buffer 
    srand((int)time(0));
    for(int i = 0; i < arg_struct->buffer.size(); i++){
        int rand_index = (rand() % arg_struct->letters.size());
        char letter = arg_struct->letters[rand_index];
        
        std::cout << "Producer: " << letter << std::endl;
        
        sem_wait(&arg_struct->empty);
        sem_wait(&arg_struct->sem);
        
        // Enter critical section on shared resource
        arg_struct->buffer.at(i) = letter;
        // Exit critical section on shared resource
        
        sem_post(&arg_struct->sem);
        sem_post(&arg_struct->full);

        std::cout << "-------------------------------------------" << std::endl;

    }
    
    pthread_exit(0);
}