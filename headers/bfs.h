#ifndef H_BFS
#define H_BFS

extern "C"
{
    #include "board.h"
    #include "manhattan.h"
    #include "queue.h"
    #include "hash.h"
    #include "result.h"
}

int execute_bfs(board *inicial_board);

#endif