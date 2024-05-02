#ifndef H_QUEUE
#define H_QUEUE

#include "board.h"
#include <stdio.h>
#include <stdlib.h>
void pushQueue(board *state);
board *popQueue();
int queue_is_empty();
void queue_reset();
#endif