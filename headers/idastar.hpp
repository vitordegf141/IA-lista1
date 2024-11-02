#ifndef H_IDASTAR
#define H_IDASTAR

extern "C" {
    #include "board.h"
    #include "manhattan.h"
    #include "queue.h"
    #include "result.h"
}
    


int execute_idastar(board *inicial_board);
#endif