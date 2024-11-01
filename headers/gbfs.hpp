#ifndef H_GBFS
#define H_GBFS

extern "C" {
    #include "board.h"
    #include "manhattan.h"
    #include "queue.h"
    #include "hash.h"
    #include "result.h"
}
    


int execute_gbfs(board *inicial_board);

#endif