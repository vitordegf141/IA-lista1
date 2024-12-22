// implement BFS algorithm

#ifndef C_ASTAR
#define C_ASTAR
extern "C"
{    
    #include "../queue.h"
    #include "../board.h"
    #include "../manhattan.h"
    #include "../result.h"
}
#include "../astar.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>


// https://stackoverflow.com/questions/2574060/c-min-heap-with-user-defined-type
char goal_boardastar[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
struct node_greater_than {
    bool operator()(astar_node *a, astar_node *b) const {
        if(a->h != b->h)
            return a->h > b->h;
        if(a->f != b->f)
            return a->f > b->f;
        
        return a->order < b->order;
        
    }
};


int execute_astar(board *inicial_board)
{
    //printf("entrou execute_astar\n");
    int isfirst=1;
    int whileRunCounter=0,searchIsTrueCounter=0;
    if(inicial_board == NULL)
        return 0;
    next_boards nexts;
    result res;
    int i,count=0;   
    
    //add_node_to_result(&res,calculate_manhathan(inicial_board,0));
    if(memcmp(inicial_board->state, goal_boardastar, board_size) == 0)
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    char char_temp[23] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','\0'};
    //printf("size of board = %ld  size of long long int = %ld\n",sizeof(board));

    std::vector<astar_node*> open_v;
    inicial_board->cost=0;
    std::string str2;
    int state_in_int=0;
    std::priority_queue<astar_node*, std::vector<astar_node*>, node_greater_than> open (open_v.begin(), open_v.end(),node_greater_than()); //open := new MinHeap ordered by ⟨f , h⟩
    std::unordered_set< unsigned long long int> closed; //closed := new HashSet
    astar_node *root = (astar_node *) malloc(sizeof(astar_node));
    astar_node *current = NULL;
    board *succesorBoard = NULL;
    astar_node *new_node;
    root->f=calculate_manhathan(inicial_board);
    AddHeuristicToResult(&res,root->f);
    init_result(&res,root->f);
    root->h =0+root->f;
    root->hash=hashing_board(inicial_board);
    root->last_move=-3;
    open.push(root);

    
    while(open.empty()==false) //while not open.is empty():
    {
        current = open.top();
        open.pop(); //n := open.pop min()
        //printf("current->hash = %llu\n",current->hash);
        if(closed.find(current->hash)==closed.end()){ //if n.state ∈/ closed:
            closed.insert(closed.begin(),current->hash);//closed.insert(n)
            if(isGoalstateASTAR(current->hash)) //if is goal(n.state):
            {
                calculate_result(&res,current->h - current->f);
                print_result(&res);
                
                while(open.empty()==false)
                {
                    
                    astar_node *aux = open.top();
                    if(aux !=NULL)
                        free(aux);
                    
                    open.pop();
                }
                closed.clear();
                return 1;
            }
            IncreaseNodesExpanded(&res);
            calculate_next_boardsastar(&nexts,current);
            for(i=0;i<nexts.number_of_moves;i++){ //for each ⟨a,s′⟩ ∈ succ(n.state):
                //printf("interacton i = %d\n",i);
                succesorBoard = nexts.next[i];
                //print_board(succesorBoard);             
                new_node = (astar_node *) malloc(sizeof(astar_node));
                new_node->f = calculate_manhathan(succesorBoard);
                AddHeuristicToResult(&res,new_node->f);
                new_node->h= succesorBoard->cost + new_node->f;
                new_node->last_move=succesorBoard->last_move;
                count++;
                new_node->order=count+1;
                new_node->hash=hashing_board(succesorBoard); //n′:= make node(n, a,s′)
                //printf("new_node->hash = %llu\n",new_node->hash);
                open.push(new_node);//open.insert(n′)   
                //getchar();
                free(succesorBoard);
            }
        }
        free(current);
    }
    while(open.empty()==false)
    {
        free(open.top());
        open.pop();
    }
    return 1;
}

#endif