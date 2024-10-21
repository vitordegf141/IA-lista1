// main function,

extern "C" {
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "headers/inputreader.h"
    #include "headers/defines.h"
    #include "headers/board.h"
    #include "headers/manhattan.h"
    #include "headers/result.h"
    #include "headers/queue.h"
}
#include <unordered_set>
#include <queue>
#include <string>
#include <iostream>
/*BFS-Graph, Iterative Deepening, A∗, IDA∗, Greedy Best-first Search*/
/*-bfs, -idfs, -astar,-idastar, -gbfs,*/

int execute_bfs(board *inicial_board);

int main(int argc, char *argv[]){
    if (argc <11) 
    {
        printf("argc = %d\n",argc);
        printf("insuficient args\n");
        exit(1);
    }
    int algorithm = get_algorithm_from_input(argv[1]);
    all_boards matrixes;
    int number_of_boards = alt_method(argc,argv,&matrixes);
    int i;
    switch (algorithm)
    {
    case bfs:
        for(i=0;i<number_of_boards;i++)
            execute_bfs(&matrixes.boards[i]);
        break;
    
    default:
        break;
    }
    return 0;
}

void to_string(char *cin,char *out)
{
    int i=0;
    for(i=0;i<16;i++)
    {
        out[i] = cin[i]+48;
    }
    out[16]='\0';
}


int execute_bfs(board *inicial_board)
{
    next_boards nexts;
    int i, test_contains;
    result res;
    board *currentBoard;
    board *succesorBoard;
    int expanded_nodes =0;
    std::unordered_set<std::string> mySet;
    char char_temp[17];
    init_result(&res,calculate_manhathan(inicial_board,0));
    inicial_board->cost=0;
    if(!queue_is_empty())
        printf("QUEUE should be empty now");
    pushQueue(inicial_board);
    if(isGoalstate(inicial_board))
    {
        calculate_result(&res,0);
        print_result(&res);
        return 0;
    }
    int k=0;
    int cc;
    while(!queue_is_empty())
    {
        k++;
        currentBoard = popQueue();
        expanded_nodes++;
        nexts.number_of_moves=0;
        to_string(currentBoard->state,char_temp);
        std::string str(char_temp);
        mySet.insert(str);
        add_node_to_result(&res,0);
        calculate_next_boards(&nexts,currentBoard);      
        for(i=0;i<nexts.number_of_moves;i++){
            succesorBoard = nexts.next[i];
            to_string(succesorBoard->state,char_temp);
            std::string str2(char_temp);
            cc=mySet.count(str2);
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                queue_reset();
                break;
            }
            
            if(cc==0){
                pushQueue(succesorBoard);
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
    //print_colissions(1);
    return 1;
}