// implement BFS algorithm

#ifndef C_IDASTAR
#define C_IDASTAR
extern "C"
{    
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
    #include "../result.h"
    
}
#include "../idastar.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>


typedef struct node_s {
    int f;
    board *state;
} node;
// https://stackoverflow.com/questions/2574060/c-min-heap-with-user-defined-type

struct node_greater_than {
    bool operator()(node *a, node *b) const {
        return a->f > b->f;
    }
};



int execute_astar_with_threshold(board *inicial_board,int threshold,result *res, int *found);

int execute_idastar(board *inicial_board)
{
    result res;
    int threshold=calculate_manhathan(inicial_board,0);
    int found =0;
    init_result(&res,calculate_manhathan(inicial_board,0));
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    while( threshold<INT_MAX && (threshold != -1 || found ==0)) //while f limit ̸= ∞:
    {
        threshold = execute_astar_with_threshold(inicial_board,threshold,&res,&found); //⟨f limit,solution⟩ := recursive search(n0, f limit)
        
    }
    return 1;
}

int f(board *state)
{
    return state->cost + state->heurisc_value;
}

int execute_astar_with_threshold(board *currentboard,int threshold,result *res, int *found)
{
    next_boards nexts;
    int i, cc, k;
    //if f (n) > f limit:
    int flimit = f(currentboard);
    if(flimit > threshold)
    {
        //printf("SAI\n");
        return flimit;
    }
    //printf("\n");
    if(isGoalstate(currentboard))//if is goal(n.state):
    {
        calculate_result(res,currentboard->cost);
        print_result(res);
        *found=1;
        return -1;
    }
    
    int next_threshold = INT_MAX; //next limit := ∞
    int new_threshold = INT_MAX;
    board *succesorBoard =NULL;
    
    calculate_next_boards(&nexts,currentboard);
    IncreaseNodesExpanded(res);
    for(i=0;i<nexts.number_of_moves;i++){ //for each ⟨a,s′⟩ ∈ succ(n.state):
        
        succesorBoard = nexts.next[i];
        succesorBoard->heurisc_value = calculate_manhathan(succesorBoard,0);
        AddHeuristicToResult(res,succesorBoard->heurisc_value);
        if(succesorBoard->heurisc_value<INT_MAX)
        {
            new_threshold = execute_astar_with_threshold(succesorBoard,threshold,res,found); //⟨rec limit,solution⟩ := recursive search(n′, f limit)
            if(new_threshold == -1)
            {
                return -1;
            }
            if(new_threshold < next_threshold) //next limit := min(next limit,rec limit)
                next_threshold = new_threshold;
        }
        
        free(succesorBoard);
    }

    return next_threshold; //return ⟨next limit, none⟩
}

#endif