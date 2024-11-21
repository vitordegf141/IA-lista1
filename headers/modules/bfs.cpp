// implement BFS algorithm

#ifndef C_BFS
#define C_BFS
extern "C"
{
    
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
}
#include "../bfs.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <queue>
#include <string>
#include <iostream>

int execute_bfs(board *inicial_board)
{
    next_boards nexts;
    int i=0, test_contains;
    result res;
    board *currentBoard = NULL;
    board *succesorBoard = NULL;
    int expanded_nodes =0;
    int prev_expanded_nodes =0;
    std::unordered_set<std::string> mySet;
    std::queue<board *> nodesQueue;
    mySet.clear();
    char char_temp[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
    init_result(&res,calculate_manhathan(inicial_board,0));
    inicial_board->cost=0;
    nodesQueue.push(inicial_board);
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    int k=0;
    int cc;
    while(nodesQueue.empty()==false)
    {
        currentBoard = nodesQueue.front();
        nodesQueue.pop();
        expanded_nodes++;
        prev_expanded_nodes =expanded_nodes;
        nexts.number_of_moves=0;            
        board_to_string(currentBoard->state,char_temp);
        std::string str(char_temp);
        mySet.insert(str);
        add_node_to_result(&res,calculate_manhathan(currentBoard,0));       
        calculate_next_boards(&nexts,currentBoard);      
        for(i=0;i<nexts.number_of_moves;i++){
            //printf("%d\n",nexts.number_of_moves);
            succesorBoard = nexts.next[i];
            board_to_string(succesorBoard->state,char_temp);
            std::string str2(char_temp);
            cc=mySet.count(str2);
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                while(nodesQueue.empty()==false)
                {
                    currentBoard = nodesQueue.front();
                    free(currentBoard);
                    nodesQueue.pop();
                }
                mySet.clear();
                return 1;
            }
            
            if(cc==0){
                nodesQueue.push(succesorBoard);
            }
            else
            {
                free(succesorBoard);
            }
        }
        //free(currentBoard);
        //printf("post free currentBoard board\n");
        //fflush(stdout);
    }
    //print_hashtable(0);
    queue_reset();
    mySet.clear();
    return 1;
}
#endif