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

typedef struct node_s {
    int f;
    int h;
    long order;
    board *state;
} node;
// https://stackoverflow.com/questions/2574060/c-min-heap-with-user-defined-type

struct node_greater_than {
    bool operator()(node *a, node *b) const {
        if(a->h != b->h)
            return a->h > b->h;
        if(a->f != b->f)
            return a->f > b->f;
        
        return a->order < b->order;
        
    }
};


int execute_astar(board *inicial_board)
{
    int isfirst=1;
    int whileRunCounter=0,searchIsTrueCounter=0;
    if(inicial_board == NULL)
        return 0;
    next_boards nexts;
    result res;
    int i,count=0;   
    init_result(&res,calculate_manhathan(inicial_board,0));
    //add_node_to_result(&res,calculate_manhathan(inicial_board,0));
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    char char_temp[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
    std::vector<node*> open_v;
    inicial_board->cost=0;
    std::string str2;
    std::priority_queue<node*, std::vector<node*>, node_greater_than> open (open_v.begin(), open_v.end(),node_greater_than()); //open := new MinHeap ordered by ⟨f , h⟩
    std::unordered_set<std::string> closed; //closed := new HashSet
    node *root = (node *) malloc(sizeof(node));
    node *current = NULL;
    board *currentboard = NULL;
    board *succesorBoard = NULL;
    node *new_node;
    root->f=calculate_manhathan(inicial_board,0);
    AddHeuristicToResult(&res,root->f);
    root->h =0+calculate_manhathan(inicial_board,0);
    root->state=inicial_board;
    open.push(root);
    board_to_string(inicial_board->state,char_temp);
    std::string str(char_temp);
    //distances[str]=0;
    
    while(open.empty()==false) //while not open.is empty():
    {
        current = open.top();
        open.pop(); //n := open.pop min()
        currentboard = current->state;
        if(current == NULL)
        {
            printf("current is null\n");
            fflush(stdout);
            break;
        }
        
        board_to_string(currentboard->state,char_temp);
        str2 = std::string(char_temp);        

        if(closed.find(str2)==closed.end()){ //if n.state ∈/ closed:
            closed.insert(closed.begin(),str2);//closed.insert(n)
            
            searchIsTrueCounter++;
            if(isGoalstate(currentboard)) //if is goal(n.state):
            {
                calculate_result(&res,currentboard->cost);
                print_result(&res);
                while(open.empty()==false)
                {
                    if(open.top()->state !=NULL)
                        free(open.top()->state);
                    open.top()->state =NULL;
                    node *aux = open.top();
                    if(aux !=NULL)
                        free(aux);
                    
                    open.pop();
                }
                return 1;
            }
            IncreaseNodesExpanded(&res);
            calculate_next_boards(&nexts,currentboard);
            for(i=0;i<nexts.number_of_moves;i++){ //for each ⟨a,s′⟩ ∈ succ(n.state):
                succesorBoard = nexts.next[i];               
                new_node = (node *) malloc(sizeof(node));
                new_node->f = calculate_manhathan(succesorBoard,0);
                AddHeuristicToResult(&res,new_node->f);
                new_node->h= succesorBoard->cost + new_node->f;
                count++;
                new_node->order=count+1;
                new_node->state=succesorBoard; //n′:= make node(n, a,s′)
                open.push(new_node);//open.insert(n′)   
            }
        }
        //free(current);
        current =NULL;
        if(isfirst==1)
            isfirst=0;
        else
            free(currentboard);
        //printf("whileRunCounter = %d\n",whileRunCounter++);
        currentboard=NULL;
    }
    while(open.empty()==false)
    {
        free(open.top()->state);
        free(open.top());
        open.pop();
    }
    return 1;
}

#endif