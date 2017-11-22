#ifndef _Util_H
#define _Util_H

#include <stdio.h>
#include <stdlib.h>

// Structure for producer and consumer threads
struct content_struct{
    char message;
    char buffer[3];
};

#endif