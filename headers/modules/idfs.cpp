// implement BFS algorithm

#ifndef C_IDFS
#define C_IDFS
extern "C"
{
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
    #include "../result.h"
    
}
#include "../idfs.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <string>
#include <iostream>

int dfs(board *currentboard,int depth,result *res);

int execute_idfs(board *inicial_board)
{
    int i, maxdepth=1,found =0;
    result res;
    init_result(&res,calculate_manhathan(inicial_board));
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,inicial_board->cost);
        print_result(&res);
        return 1;
    }
    inicial_board->cost=0;
    while(found ==0 )
    {
        //printf("\n**depth limit: %d**\n",maxdepth);
        if(maxdepth == 100)
        {
            printf("maxdepth chegou a 100");
        }
        maxdepth++;
        found = dfs(inicial_board,maxdepth,&res);
        //printf("maxdepth: %d\n",maxdepth);
    }
    return 1;
}


int dfs(board *currentboard,int depth,result *res)
{
    if(currentboard == NULL)
    {
        printf("currentboard is NULL");
        return 0;
    }
    next_boards nexts;
    int i;
    int found=0;
    
    if(isGoalstate(currentboard))//if is goal(s):
    {
        //printf("achou goal  \n");
        //fflush(stdout);
        add_node_to_result(res,calculate_manhathan(currentboard));
        calculate_result(res,currentboard->cost);
        print_result(res);
        return 1;//return ()
    }
    if(depth>0)//if depth limit > 0
    {
        add_node_to_result(res,calculate_manhathan(currentboard));
        //printf("depth limit: %d\n",depth);
        //nexts.number_of_moves=0;
        //print_board(currentboard);
        //getchar();
        //add_node_to_result(res,calculate_manhathan(currentboard,0));
        calculate_next_boards(&nexts,currentboard);
        for(i=0;i<nexts.number_of_moves;i++) //for each ⟨a,s′⟩ ∈ succ(s):
        {
            
            found = dfs(nexts.next[i],depth-1,res); //solution := depth limited search(s′, depth limit − 1)
            //free(nexts.next[i]);
            if(found == 1)
            {
                //printf("found solution\n");
                return found;
            }
             //if solution ̸= none: return solution
        }
    }
    //printf("depth limit reached\n");
    
    return 0;
}

#endif