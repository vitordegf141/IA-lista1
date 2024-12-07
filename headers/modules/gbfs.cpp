// implement BFS algorithm

#ifndef C_GBFS
#define C_GBFS
extern "C"
{    
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
    #include "../result.h"
}
#include "../gbfs.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>


typedef struct node_s {
    int h;
    int g;
    int order;
    board *state;
} node;
// https://stackoverflow.com/questions/2574060/c-min-heap-with-user-defined-type

struct node_greater_than {
    bool operator()(node *a, node *b) const {
        if(a->h != b->h)
            return a->h > b->h;
        if(a->g != b->g)
            return a->g < b->g;
        
        return a->order < b->order;
        
    }
};



int execute_gbfs(board *inicial_board)
{
    next_boards nexts;
    result res;
    int i, cc,k;
    init_result(&res,calculate_manhathan(inicial_board,0));
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    char char_temp[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
    std::vector<node*> open;
    inicial_board->cost=0;
    std::unordered_set<std::string> explored;
    std::make_heap(open.begin(), open.end(),node_greater_than());
    node *root = (node *) malloc(sizeof(node));
    node *current = NULL;
    board *currentboard = NULL;
    board *succesorBoard = NULL;
    node *new_node;
    int count=0;
    root->h=0;
    root->state=inicial_board;
    open.push_back(root);
    std::push_heap(open.begin(), open.end(),node_greater_than());
    std::string str2;
    while(!open.empty())
    {
        std::pop_heap(open.begin(), open.end(),node_greater_than());
        current = open.back();
        open.pop_back();
        currentboard = current->state;
        //getchar();
        if(isGoalstate(currentboard))
        {
            calculate_result(&res,0);
            print_result(&res);
            return 0;
        }
        board_to_string(currentboard->state,char_temp);
        std::string str(char_temp);
        explored.insert(str);
        IncreaseNodesExpanded(&res);
        calculate_next_boards(&nexts,currentboard);
        
        for(i=0;i<nexts.number_of_moves;i++){
            
            succesorBoard = nexts.next[i];
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                for(k=0;k<open.size();k++) {
                    free(open[k]->state);
                    free(open[k]);
                }
                open.clear();
                explored.clear();
                return 1;
            }
            board_to_string(succesorBoard->state,char_temp);
            str2.assign(char_temp);
            if(explored.find(str2)==explored.end()){
                new_node = (node *) malloc(sizeof(node));
                new_node->h= calculate_manhathan(succesorBoard,0);
                AddHeuristicToResult(&res,new_node->h);
                new_node->g=succesorBoard->cost;
                new_node->state=succesorBoard;
                new_node->order=count++;
                open.push_back(new_node);
                std::push_heap(open.begin(), open.end(),node_greater_than());
            }
            else
            {
                free(succesorBoard);
            }
        }

    }
    explored.clear();
    for(k=0;k<open.size();k++) {
        free(open[k]->state);
        free(open[k]);
    }
    open.clear();
    return 1;
}

#endif