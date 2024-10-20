//implement a queue on array
#ifndef C_QUEUE
#define C_QUEUE

#define SIZE 10000000
#include "../queue.h"
board *inp_arr[SIZE];
int Rear = - 1;
int Front = - 1;
d
void pushQueue(board *state)
{
    if (Rear == SIZE - 1)
    {
        printf("Queue Overflow \n");
        return;
    }
       
    else
    {
        if (Front == - 1)
            Front = 0;
        Rear = Rear + 1;
        inp_arr[Rear] = state;
    }
} 
 
board * popQueue()
{
    board *aux;
    if (Front == - 1 || Front > Rear)
    {
        aux = NULL;
    }
    else
    {
        aux = inp_arr[Front];
        if(Front == Rear)
            Front=Rear=-1;
        else
            Front = Front + 1;
    }
    return aux;
} 
 
int queue_is_empty()
{
    return Front == -1;
}

void queue_reset()
{
    Front=-1;
    Rear=-1;
}

#endif
