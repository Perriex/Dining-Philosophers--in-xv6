#include <time.h>
#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM 5
#define INFINITE 5000
#define EATING 1
#define THINKING 2
#define HUNGRY 3

int chops[NUM] = {-1, -1, -1, -1, -1};
int waiting[NUM] = {2, 3, 1, 3, 2};
int states[NUM] = {0};

void return_chops(int id)
{
    int left = ((id - 1) + NUM) % NUM;
    int right = (id + 1) % NUM;
    chops[left] = -1;
    chops[right] = -1;

    // lock
    states[id] = THINKING;
    printf(1, "Philosopher id has put down forks\n", id);
    // release
    sem_release(left);
    sem_release(right);
}
void eat(int id)
{
    int eating = waiting[id];
    printf(1, "Philosopher %d is eating for %d seconds\n", id, eating);
    sleep(eating);
    printf(1, "Philosopher %d finished %d\n", id);
    return;
}

void pickup_chops(int id)
{
    int left = ((id - 1) + NUM) % NUM;
    int right = (id + 1) % NUM;
    states[id] = HUNGRY;
    // lock semaphore
    sem_acquire(left);
    sem_acquire(right);
    states[id] = EATING;
    chops[left] = id;
    chops[right] = id;
    printf(1, "Philosopher %d is eating now \n", id);
    // release lock
    return;
}

void think(int id)
{
    int think = waiting[id];
    printf(1, "Philosopher %d is thinking for %d seconds\n", id, think);
    sleep(think);
    printf(1, "Philosopher %d finish thinking\n", id);
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
        sem_init(i, 5);
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