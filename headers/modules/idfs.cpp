// implement BFS algorithm

#ifndef C_IDFS
#define C_IDFS
extern "C"
{
    #include "../idfs.h"
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

int dfs(board *currentboard,int depth, int maxdepth,result *res);

int execute_idfs(board *inicial_board)
{
    int i, maxdepth=0,found =0;
    result res;
    init_result(&res,calculate_manhathan(inicial_board,0));
    inicial_board->cost=0;
    while(found ==0 && maxdepth <100)
    {
        maxdepth++;
        found = dfs(inicial_board,0,maxdepth,&res);
    }
    return 1;
}


int dfs(board *currentboard,int depth, int maxdepth,result *res)
{
    next_boards nexts;
    add_node_to_result(res,calculate_manhathan(currentboard,0));
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
    int found;
    nexts.number_of_moves=0;
    add_node_to_result(res,calculate_manhathan(currentboard,0));
    calculate_next_boards(&nexts,currentboard);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        found = dfs(nexts.next[i],depth+1,maxdepth,res);
        if(found == 1)
            return found;
        free(nexts.next[i]);
    }
    return 0;
}

#endif