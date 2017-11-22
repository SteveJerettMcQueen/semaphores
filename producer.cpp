#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>

#include "producer.hpp"
#include "util.hpp"

void *prod_runner(void *arg){
    struct content_struct *arg_struct = (struct content_struct*) arg;
    
    // Producer produces content
    char message = 'A';// Generated Randomly
    arg_struct->message = message;
    
    // Producer writes to buffer the 
    sprintf (arg_struct->buffer, "%c", arg_struct->message);
    std::cout << "Producer: " << arg_struct->buffer << std::endl;
}