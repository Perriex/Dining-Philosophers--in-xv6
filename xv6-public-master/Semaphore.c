#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "Semaphore.h"

#define NUMSEMAPHORE 5

struct Semaphore semaphore[NUMSEMAPHORE];

void sem_init(uint i, uint v)
{
    semaphore[i].index = i;
    semaphore[i].value = 0;
    semaphore[i].capacity = v;
<<<<<<< HEAD
=======
    initlock(&semaphore[i].lock, (char *)i); // unique name
    for (int j = 0; j < NPROC; j++)
        semaphore[i].procs[j] = 0;
>>>>>>> 97253ed3227b8270eea601ce00d560f25c6f05e6
    semaphore[i].first = semaphore[i].last = 0;
    return;
}

void sem_acquire(uint i)
{
    xchg(&semaphore[i].value, semaphore[i].value + 1);
    if (semaphore[i].value > semaphore[i].capacity)
    {
        semaphore[i].procs[semaphore[i].last] = myproc();
        semaphore[i].last = (semaphore[i].last + 1) % NPROC;
        sleepcurrent();
    }
}

void sem_release(uint i)
{
    xchg(&semaphore[i].value, semaphore[i].value - 1);
    if(semaphore[i].procs[semaphore[i].first])
    {
        wakeupprocess(semaphore[i].procs[semaphore[i].first]);
        semaphore[i].procs[semaphore[i].first] = 0;
        semaphore[i].first = (semaphore[i].first + 1) % NPROC;
    }
}