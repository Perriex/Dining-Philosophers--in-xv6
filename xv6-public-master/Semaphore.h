#include "param.h"
#include "spinlock.h"

typedef struct Semaphore
{
    unsigned int index; // for debug
    struct spinlock lock;
    void *procs[NPROC];
    unsigned int first;
    unsigned int last;
    unsigned int capacity;
} semaphore;