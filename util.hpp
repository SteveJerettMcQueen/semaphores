#ifndef _Util_H
#define _Util_H

#include <array>
#include <map>
#include <string>
#include <vector>

#include <pthread.h>
#include <semaphore.h>

// Structure for producer and consumer thread shared resources
struct content_struct{
    pthread_mutex_t mutex;
    sem_t sem, empty, full;
    std::array<char,3> buffer;
    std::vector<char> letters, vowels;
    std::map<char, int> location_map;
    std::string status;
};

#endif