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
#include <deque>
#include <string>
#include <iostream>

int execute_bfs(board *inicial_board)
{
    
    next_boards nexts;
    int i=0, test_contains;
    result res;
    init_result(&res,calculate_manhathan(inicial_board,0));
    if(isGoalstate(inicial_board)) //if is goal(init()):
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    board *currentBoard = NULL;
    board *succesorBoard = NULL;
    int expanded_nodes =0;
    int prev_expanded_nodes =0;
    std::unordered_set<std::string> closed; //closed := new HashSet
    std::deque<board *> open;//open := new Deque
    closed.clear();
    char char_temp[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
    inicial_board->cost=0;
    open.push_back(inicial_board); //open.push back(make root node())
    board_to_string(inicial_board->state,char_temp);
    std::string str(char_temp);
    closed.insert(closed.begin(),str); //closed.insert(init())
    
    int k=0;
    int cc;
    while(open.empty()==false)//while not open.is empty():
    {
        currentBoard = open.front();
        open.pop_front(); //n := open.pop front()                 
        add_node_to_result(&res,calculate_manhathan(currentBoard,0));       
        calculate_next_boards(&nexts,currentBoard);      //succ(n.state):
        for(i=0;i<nexts.number_of_moves;i++){ //for each ⟨a,s′⟩ ∈ succ(n.state):
            succesorBoard = nexts.next[i];
            if(isGoalstate(succesorBoard)) //if is goal(s′):
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                while(open.empty()==false) // clear memory
                {
                    currentBoard = open.front();
                    free(currentBoard);
                    open.pop_front();
                }
                closed.clear();
                return 1;
            }
            board_to_string(succesorBoard->state,char_temp);// if s′ ∈/ closed:
            std::string str2(char_temp);            
            if(closed.find(str2)==closed.end()) //if s′ ∈/ closed:
            {
                board_to_string(succesorBoard->state,char_temp); 
                std::string str(char_temp);
                closed.insert(closed.begin(),str);// closed.insert(s′)
                open.push_back(succesorBoard); //open.push back(n′)
            }
            else
            {
                free(succesorBoard);// clear memory 
            }
        }
    }
    while(open.empty()==false) // clear memory
    {
        currentBoard = open.front();
        free(currentBoard);
        open.pop_front();
    }
    closed.clear();
    return 1;
}
#endif