// implement BFS algorithm

#ifndef C_GBFS
#define C_GBFS
extern "C"
{    
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
    #include "../hash.h"
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
    int f;
    board *state;
} node;
// https://stackoverflow.com/questions/2574060/c-min-heap-with-user-defined-type

struct node_greater_than {
    bool operator()(node *a, node *b) const {
        return a->f > b->f;
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
    int hull=0;
    root->f=0;
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
        add_node_to_result(&res,calculate_manhathan(currentboard,0));
        calculate_next_boards(&nexts,currentboard);
        hull++;
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
            cc=explored.count(str2);
            if(cc==0){
                new_node = (node *) malloc(sizeof(node));
                new_node->f== calculate_manhathan(succesorBoard,0);
                new_node->state=succesorBoard;
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