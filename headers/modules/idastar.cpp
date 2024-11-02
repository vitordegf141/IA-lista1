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
    int threshold=1, lesser_threshold;
    int found =0;
    init_result(&res,calculate_manhathan(inicial_board,0));
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    while( threshold>0 || found ==1)
    {
        threshold = execute_astar_with_threshold(inicial_board,threshold,&res,&found);
        
    }
    return 1;
}


int execute_astar_with_threshold(board *inicial_board,int threshold,result *res, int *found)
{
    next_boards nexts;
    int i, cc, k;
    int lesser_threshold = INT_MAX;
    if(isGoalstate(inicial_board))
    {
        calculate_result(res,0);
        print_result(res);
        fflush(stdout);
        

        return -1;
    }
    char char_temp[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
    std::vector<node*> open;
    inicial_board->cost=0;
    std::unordered_set<std::string> explored;
    explored.clear();
    std::make_heap(open.begin(), open.end(),node_greater_than());
    node *root = (node *) malloc(sizeof(node));
    node *current = NULL;
    board *currentboard = NULL;
    board *succesorBoard = NULL;
    node *new_node;
    root->f=0;
    root->state=inicial_board;
    open.push_back(root);
    std::push_heap(open.begin(), open.end(),node_greater_than());
    while(!open.empty())
    {
        std::pop_heap(open.begin(), open.end(),node_greater_than());
        current = open.back();
        open.pop_back();
        currentboard = current->state;
        //getchar();
        if(isGoalstate(currentboard))
        {
            calculate_result(res,0);
            print_result(res);
            return 0;
        }
        board_to_string(currentboard->state,char_temp);
        std::string str(char_temp);
        explored.insert(str);
        add_node_to_result(res,calculate_manhathan(currentboard,0));
        calculate_next_boards(&nexts,currentboard);
        for(i=0;i<nexts.number_of_moves;i++){
            
            succesorBoard = nexts.next[i];
            if(isGoalstate(succesorBoard))
            {
                printf("ACHOU GOAL\n");
                fflush(stdout);
                calculate_result(res,succesorBoard->cost);
                print_result(res);
                for(k=0;k<open.size();k++) {
                    free(open[k]->state);
                    free(open[k]);
                }
                fflush(stdout);
                getchar();
                return -1;
            }
            
            board_to_string(succesorBoard->state,char_temp);
            std::string str2(char_temp);
            cc=explored.count(str2);
            if(cc==0){
                new_node = (node *) malloc(sizeof(node));
                new_node->f=succesorBoard->cost + calculate_manhathan(succesorBoard,0);
                
                if(new_node->f <= threshold)
                {
                    new_node->state=succesorBoard;
                    open.push_back(new_node);
                    std::push_heap(open.begin(), open.end(),node_greater_than());
                }
                if(new_node->f < lesser_threshold && new_node->f >threshold)
                {
                    lesser_threshold = new_node->f;
                }
            }
            else
            {
                //printf("is this it?\n");
                //fflush(stdout);
                free(succesorBoard);
                //printf("it was not\n");
                //fflush(stdout);
            }
        }

    }
    explored.clear();
    for(k=0;k<open.size();k++) {
        free(open[k]->state);
        free(open[k]);
    }

    open.clear();
    return lesser_threshold;
}

#endif