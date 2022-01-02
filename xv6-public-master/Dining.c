#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM 5
#define INFINITE 5000
#define EATING 1
#define THINKING 2
#define HUNGRY 3

int waiting[NUM] = {100, 100, 100, 100, 100};

void return_chops(int id)
{
    int left = id;
    int right = (id + 1) % NUM;
    sem_release(left);
    sem_release(right);
}
void eat(int id)
{
    int eating = waiting[id];
    printf(1, "%d \n", id + 1);
    sleep(eating);
    return;
}

void pickup_chops(int id)
{
    int left = id;
    int right = (id + 1) % NUM;
 
    if(left < right)
    {
        sem_acquire(left);
        sem_acquire(right);
    }
    else
    {
        sem_acquire(right);
        sem_acquire(left);
    }
    return;
}

void think(int id)
{
    int think = waiting[id];
    //printf(1, "Philosopher %d is thinking for %d seconds\n", id, think);
    sleep(think);
    //printf(1, "Philosopher %d finish thinking\n", id);
    return;
}

void philosopher(int id)
{
    while (1)
    {
        think(id);
        pickup_chops(id);
        eat(id);
        return_chops(id);
    }
    return;
}

int main(void)
{
    for (int i = 0; i < NUM; i++)
    {
        sem_init(i, 1);
    }

    // fork 5 childs and execute
    int pid;
    for (int i = 0; i < 5; i++)
    {
        if ((pid = fork()) == 0)
        {
            philosopher(i);
        }
    }
    wait();
    return 0;
}