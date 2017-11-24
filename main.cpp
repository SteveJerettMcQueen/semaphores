#include <string>
#include <pthread.h>
#include <semaphore.h>

#include "consumer.hpp"
#include "producer.hpp"
#include "util.hpp"

int main(){
    
    struct content_struct cs;

    // Semaphores
    sem_t sem;
    sem_init(&sem, 0, 1);// Number of threads: binary
    cs.sem = sem;

    sem_t empty;
    sem_init(&empty, 0, cs.buffer.size());// Init to the size of the buffer
    cs.empty = empty;

    sem_t full;
    sem_init(&full, 0, 0);
    cs.full = full;

    // Producer thread
    pthread_t producer;
    pthread_attr_t prod_attr;
    pthread_attr_init(&prod_attr);
    pthread_create(&producer, &prod_attr, prod_runner, &cs);
            
    // Consumer thread
    pthread_t consumer;
    pthread_attr_t con_attr;
    pthread_attr_init(&con_attr);
    pthread_create(&consumer, &con_attr, con_runner, &cs);        
            
    // Suspend wait during execution
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    
    // Destroy semaphores
    sem_destroy(&sem);
    sem_destroy(&empty);
    sem_destroy(&full);

    
    return 0;
}