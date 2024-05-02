#ifndef C_BFS
#define C_BFS

#include "../bfs.h"
#include "../queue.h"
#include "../board.h"
#include "../manhattan.h"
#include "../hash.h"
#include <stdlib.h>
#include <stdio.h>

int execute_bfs(board *inicial_board)
{
    if(isGoalstate(inicial_board))
        return 0;
    //SimpleSet visitedSet;

    next_boards nexts;
    int i, test_contains;
    //set_init(&visitedSet);
    initHashTable();

    inicial_board->cost=0;
    //inicial_board->heurisc_value=calculate_manhathan(inicial_board,0);
    //set_add(&openSet, inicial_board->state);
    pushQueue(inicial_board);
    print_board(inicial_board);
    printf("=====\n");
    board *currentBoard;
    board *succesorBoard;
    int expanded_nodes =0;
    while(!queue_is_empty())
    {
        currentBoard = popQueue();
        expanded_nodes++;
        nexts.number_of_moves=0;
        insert_simbol(currentBoard->state);
        calculate_next_boards(&nexts,currentBoard);
        //printf("******* cost-now=%d\n",currentBoard->cost);
        //print_board(currentBoard);
        //printf("*******");
        
        for(i=0;i<nexts.number_of_moves;i++){
            succesorBoard = nexts.next[i];
            
            if(isGoalstate(succesorBoard))
            {
                printf("PQP ACHOU KRL expanded node =%d cost %d\n",expanded_nodes,succesorBoard->cost);
                print_board(succesorBoard);
                getchar();
                return 0;
            }
            //succesorBoard->heurisc_value = calculate_manhathan(succesorBoard,0);
            //test_contains = set_contains(&visitedSet,succesorBoard->state);
            if(!has_simbol(succesorBoard->state)){
                //printf("\n---s--\n");
                pushQueue(succesorBoard);
                //print_board(succesorBoard);
                //getchar();
            }
            else
            {
                //printf("\n---f--\n");
                //print_board(succesorBoard);
                //getchar();
            }
        }
         //printf("is queue empty = %d\n",queue_is_empty());
         //getchar();
    }
    printf("expanded nodes = %d",expanded_nodes);
    print_hashtable();
    queue_reset();
    return 1;
}

#endif