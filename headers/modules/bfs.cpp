// implement BFS algorithm

#ifndef C_BFS
#define C_BFS
extern "C"
{
    #include "../bfs.h"
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

int execute_bfs(board *inicial_board)
{
    next_boards nexts;
    next_boards nexts2; //delete after it's working
    int i=0, test_contains;
    printf("inicial board  testing for randons\n");
    print_board(inicial_board);
    printf("-----------\n");
    print_queue();
    result res;
    board *currentBoard = NULL;
    board *succesorBoard = NULL;
    int expanded_nodes =0;
    int prev_expanded_nodes =0;
    std::unordered_set<std::string> mySet;
    mySet.clear();
    queue_reset();
    printf("BEGNING my set size %ld\n",mySet.size());
    char char_temp[17] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'};
    init_result(&res,calculate_manhathan(inicial_board,0));
    print_result(&res);
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
    printf("before expanded_nodes = %d \n",expanded_nodes);
    while(!queue_is_empty())
    {
        currentBoard = popQueue();
        expanded_nodes++;
        if((expanded_nodes -prev_expanded_nodes) !=1)
        {
            printf("THERES LEAKEA\n");
        }
        prev_expanded_nodes =expanded_nodes;
        nexts.number_of_moves=0;
        if(expanded_nodes == 5000){
            printf("the 5000 board\n");
            print_board(currentBoard);
            print_size();
            printf("my set size %ld\n",mySet.size());
        }
            
        board_to_string(currentBoard->state,char_temp);
        std::string str(char_temp);
        mySet.insert(str);
        add_node_to_result(&res,calculate_manhathan(currentBoard,0));       
        calculate_next_boards(&nexts,currentBoard);      
        calculate_next_boards(&nexts2,currentBoard);
        if(nexts.number_of_moves != nexts2.number_of_moves)
            printf("TA AQUI O PROBLEMA KRL \n");
        for(i=0;i<nexts.number_of_moves;i++)
        {
            if(compare_boards(nexts.next[i],nexts2.next[i]) ==0)
            {
                printf("AQUI TEM PROBLEMA\n");
            }
        }
        for(i=0;i<nexts.number_of_moves;i++){
            //printf("%d\n",nexts.number_of_moves);
            succesorBoard = nexts.next[i];
            if(expanded_nodes<9)
            {
                printf("sucessor expanded_nodes %d\n",expanded_nodes);
                print_board(succesorBoard);
                print_queue();
                printf("my set size %ld\n",mySet.size());
            }
            board_to_string(succesorBoard->state,char_temp);
            std::string str2(char_temp);
            cc=mySet.count(str2);
            if(isGoalstate(succesorBoard))
            {
                calculate_result(&res,succesorBoard->cost);
                print_result(&res);
                queue_reset();
                printf("my set size %ld\n",mySet.size());
                mySet.clear();
                printf("after my set size %ld\n",mySet.size());
                print_board(succesorBoard);
                printf("after expanded_nodes = %d \n",expanded_nodes);
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
    queue_reset();
    mySet.clear();
    printf("**********\n");
    return 1;
}
#endif