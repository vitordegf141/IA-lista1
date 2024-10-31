// implement BFS algorithm

#ifndef C_ASTAR
#define C_ASTAR
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
#include <algorithm>
#include <vector>

int dfs(board *currentboard,int depth, int maxdepth,result *res);

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

int execute_astar(board *inicial_board)
{
    next_boards nexts;
    result res;
    int i;
    init_result(&res,calculate_manhathan(inicial_board,0));
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    std::vector<node*> open;
    inicial_board->cost=0;
    std::unordered_set<std::string> explored;
    std::make_heap(open.begin(), open.end(),node_greater_than());
    node *root = (node *) malloc(sizeof(node));
    node *current = NULL;
    board *currentboard = NULL;
    board *succesorBoard = NULL;
    root->f=0;
    root->state=inicial_board;
    open.push_back(root);
    std::push_heap(open.begin(), open.end(),node_greater_than());
    while(!open.empty())
    {
        std::pop_heap(open.begin(), open.end());
        current = open.back();
        open.pop_back();
        currentboard = current->state;
        if(isGoalstate(currentboard))
        {
            calculate_result(&res,0);
            print_result(&res);
            return 0;
        }
        calculate_next_boards(&nexts,currentboard);
        for(i=0;i<nexts.number_of_moves;i++){
            succesorBoard = nexts.next[i];
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                return 1;
            }
            

        }

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