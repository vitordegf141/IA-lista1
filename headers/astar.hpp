#ifndef H_ASTAR
#define H_ASTAR

extern "C" {
    #include "board.h"
    #include "manhattan.h"
    #include "queue.h"
    #include "hash.h"
    #include "result.h"
}
    


int execute_astar(board *inicial_board);

#endif