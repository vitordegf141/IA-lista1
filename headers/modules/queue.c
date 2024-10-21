//implement a queue on array
#ifndef C_QUEUE
#define C_QUEUE

#define SIZE 10000000
#include "../queue.h"

typedef struct queue_s{
    int queue_number;
    struct queue_s *rear;
    board *object;
} queue;

queue *Last = NULL;
queue *First = NULL;

int queue_size =0;

void pushQueue(board *currentboard)
{
    //QUEUE is empty
    if(currentboard == NULL)
        printf("PUSHING STATE THAT IS NULL");
    if (First == NULL)
    {
        
        First = (queue *) malloc(sizeof(queue));
        Last = First;
        First->object = currentboard;
        First->rear=NULL;
        First->queue_number = queue_size;
        if (First->object == NULL)
            printf("WHY First IS IT NULL");
        if (Last->object == NULL)
            printf("WHY Last IS IT NULL");
        queue_size++;
        return;
    }
    // LAST SHOULD NEVER BE EMPTY IF FIRST IS NOT EMPTY TOO
    if(Last == NULL)
    {
        printf("ERROR HAS OCCURED in PUSHING INTO QUEUE");
        getchar();
        return;
    }
    //created new last
    queue *new_last = (queue *) malloc(sizeof(queue));
    if(currentboard == NULL)
        printf("pushing state that is NULL why\n");
    new_last->object = currentboard;
    new_last->rear=NULL;
    new_last->queue_number=queue_size+1;
    //puts new last into last's rear
    Last->rear = new_last;
    // switchs lasts
    Last = new_last;
    if(new_last->object == NULL)
        printf("how new_last-> object null\n");
    if(Last->object == NULL)
        printf("how Last-> object null\n");
    queue_size++;
    return;
} 

board * popQueue()
{
    //QUEUE is empty
    if (First == NULL)
    {
        return NULL;
    }
    board *state = First->object;
    if(state == NULL)
        printf("poping state that is NULL why\n");
    // in the case that there's only one element eg First's rear is empty or First is the same as Last
    if(First->rear == NULL || First == Last)
    {
        free(First);
        First = NULL;
        Last = NULL;
    }
    else
    {
        queue *new_first =First->rear;
        //frees First queue struct memory]
        if(First == First->rear)
        {
            printf("QUEUE is corrupt\n");
            fflush(stdout);
            getchar();
        }
            
        free(First);
        // new first is the rear of first
        First = new_first;
    }
    
    queue_size--;
    return state;

} 
 
int queue_is_empty()
{
    return First == NULL;
}

void free_all_queue(queue *queueS)
{
    if(queueS == NULL)
        return;
    free_all_queue(queueS->rear);
    free(queueS);
    return;
}

void queue_reset()
{
    free_all_queue(First);
    First=NULL;
    Last=NULL;
}

void print_queue_in(queue *node, int i)
{
    if(node == NULL)
        return;
    if(node->object == NULL)
        printf("%d queue[%d] node's object is NULL\n", i,node->queue_number);
    else
        printf("%d queue[%d] node's object is NOT NULL\n", i,node->queue_number);
    print_queue_in(node->rear,i+1);
}

void print_queue()
{
    printf("QUEUE size is = %d\n",queue_size);
    print_queue_in(First,1);
}



#endif
