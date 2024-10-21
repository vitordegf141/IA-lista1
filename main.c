// main function,

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "headers/inputreader.h"
#include "headers/defines.h"
#include "headers/board.h"
#include "headers/manhattan.h"
#include "headers/bfs.h"

/*BFS-Graph, Iterative Deepening, A∗, IDA∗, Greedy Best-first Search*/
/*-bfs, -idfs, -astar,-idastar, -gbfs,*/



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
    //for(i=0;i<number_of_boards;i++)
    //{
    //    print_board(&matrixes.boards[i]);
    //    getchar();
    //}
    
    switch (algorithm)
    {
    case bfs:
        for(i=0;i<number_of_boards;i++)
            execute_bfs(&matrixes.boards[i]);
        break;
    case idfs:
        for(i=0;i<number_of_boards;i++)
            execute_bfs(&matrixes.boards[i]);
        break;
    
    default:
        break;
    }
    return 0;
}
