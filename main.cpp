#include <string>
#include <pthread.h>

#include "consumer.hpp"
#include "producer.hpp"
#include "util.hpp"

int main(){
    
    struct content_struct cs;

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
    
}