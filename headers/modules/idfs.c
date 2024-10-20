// implement IDFS algorithm

#ifndef C_IDFS
#define C_IDFS

#include "../bfs.h"
#include "../queue.h"
#include "../board.h"
#include "../manhattan.h"
#include "../hash.h"
#include <stdlib.h>
#include <stdio.h>

int execute_idfs(board *inicial_board)
{
    next_boards nexts;
    int i, test_contains;
    result res;
    board *currentBoard;
    board *succesorBoard;
    int expanded_nodes =0;
    initHashTable();
    init_result(&res,calculate_manhathan(inicial_board,0));
    inicial_board->cost=0;
    pushQueue(inicial_board);
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
        
    while(!queue_is_empty())
    {
        currentBoard = popQueue();
        expanded_nodes++;
        nexts.number_of_moves=0;
        insert_simbol(currentBoard->state);
        add_node_to_result(&res,0);
        calculate_next_boards(&nexts,currentBoard);        
        for(i=0;i<nexts.number_of_moves;i++){
            succesorBoard = nexts.next[i];
            
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                queue_reset();
                break;
            }
            if(!has_simbol(succesorBoard->state)){
                pushQueue(succesorBoard);
            }
        }
    }
    print_hashtable(0);
    print_colissions(1);
    queue_reset();
    return 1;
}


int DLS(board *currentBoard, int depth, int maxdepth, result *res){
    if(isGoalstate(currentBoard))
    {
        calculate_result(res,currentBoard->cost);
        print_result(&res);
        queue_reset();
        return 1;
    }
    if(depth == maxdepth)
        return 0;
    next_boards nexts;
    board *nextBoard;
    int i;
    calculate_next_boards(&nexts,currentBoard);
    for(i=0;i<nexts.number_of_moves;i++){
        nextBoard = nexts.next[i];
        DLS(nextBoard,depth+1,maxdepth,res);
    }
    
}
#endif