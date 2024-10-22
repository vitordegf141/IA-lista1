// implement BFS algorithm

#ifndef C_BFS
#define C_BFS
extern "C"
{
    #include "../bfs.h"
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
    #include "../hash.h"
}

#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <string>
#include <iostream>

int execute_idfs(board *inicial_board)
{
    next_boards nexts;
    int i, test_contains;
    result res;
    board *currentBoard;
    board *succesorBoard;
    int expanded_nodes =0;
    std::unordered_set<std::string> mySet;
    char char_temp[17];
    init_result(&res,calculate_manhathan(inicial_board,0));
    inicial_board->cost=0;
    if(!queue_is_empty())
        printf("QUEUE should be empty now");
    pushQueue(inicial_board);
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    int k=0;
    int cc;
    while(!queue_is_empty())
    {
        k++;
        currentBoard = popQueue();
        expanded_nodes++;
        nexts.number_of_moves=0;
        board_to_string(currentBoard->state,char_temp);
        std::string str(char_temp);
        mySet.insert(str);
        add_node_to_result(&res,0);
        calculate_next_boards(&nexts,currentBoard);      
        for(i=0;i<nexts.number_of_moves;i++){
            succesorBoard = nexts.next[i];
            board_to_string(succesorBoard->state,char_temp);
            std::string str2(char_temp);
            cc=mySet.count(str2);
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                queue_reset();
                break;
            }
            
            if(cc==0){
                pushQueue(succesorBoard);
            }
            else
            {
                free(succesorBoard);
            }
        }
    }
    return 1;
}


int dfs(board *currentboard,int depth, int maxdepth,result *res)
{
    next_boards nexts;
    if(isGoalstate(currentboard))
    {
        calculate_result(res,currentboard->cost);
        print_result(res);
        queue_reset();
        return 1;
    }
    if(depth>=maxdepth)
    {
        return 0;
    }
    int i;
    nexts.number_of_moves=0;
    calculate_next_boards(&nexts,currentboard);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        
    }
}

#endif