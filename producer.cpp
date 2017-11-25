#include <ctime>
#include <iostream>
#include <sstream>

#include <pthread.h>
#include <semaphore.h>

#include "producer.hpp"
#include "util.hpp"

void *prod_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;
    
    pthread_mutex_lock(&arg_struct->mutex);
    
    // Enter critical section of shared resource
    arg_struct->letters = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };

    arg_struct->vowels = {'A', 'E', 'I', 'O', 'U'};

    for(int i = 0; i < arg_struct->letters.size(); i++){
        arg_struct->location_map.insert(std::pair<char, int> (arg_struct->letters[i], i));
    }
    // Exit critical section of shared resource

    pthread_mutex_unlock(&arg_struct->mutex);

    // Producer writes content to the buffer 
    std::ostringstream os;
    
    srand((int)time(0));
    for(int i = 0; i < arg_struct->buffer.size(); i++){
        int rand_index = (rand() % arg_struct->letters.size());
        char letter = arg_struct->letters[rand_index];
        
        // Record information
        os << "Producer[" << i <<"]: " << letter << std::endl;
        
        // Writes status to shared variable
        pthread_mutex_lock(&arg_struct->mutex);
        arg_struct->status = os.str();
        pthread_mutex_unlock(&arg_struct->mutex);
        
        sem_wait(&arg_struct->empty);
        sem_wait(&arg_struct->sem);
        
        // Enter critical section on shared resource
        arg_struct->buffer.at(i) = letter;
        // Exit critical section on shared resource
        
        sem_post(&arg_struct->sem);
        sem_post(&arg_struct->full);

    }
    
    // Reads status to shared variable
    pthread_mutex_lock(&arg_struct->mutex);
    std::cout<< arg_struct->status;
    pthread_mutex_unlock(&arg_struct->mutex);
    
    std::cout<< "------------------------------------------------" << std::endl;

}