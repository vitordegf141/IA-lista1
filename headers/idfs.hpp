#ifndef H_IDF
#define H_IDF

extern "C" {
    #include "board.h"
    #include "manhattan.h"
    #include "queue.h"
    #include "hash.h"
    #include "result.h"
}
    


int execute_idfs(board *inicial_board);

#endif