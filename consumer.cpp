#include <iostream>
#include <string>
#include <pthread.h>

#include "consumer.hpp"
#include "util.hpp"

void *con_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;

    std::cout << "Consumer: " << arg_struct->buffer << std::endl;
    
    pthread_exit(0);
}
