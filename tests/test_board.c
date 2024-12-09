// non part of the code, just for testing

#include <stdio.h>
#include "../headers/board.h"


int assert(int value, int expected)
{
    if(value==expected)
    {
        printf(" PASSED\n");
        return 1;
    }
        
    else
    {
        printf("FAILED\n");
        return 0;
    }
        
}

int test_goal_board()
{
    board_size=9;
    board_side_size=3;
    board goal_board;
    int i;
    for(i=0;i<board_size;i++)
        goal_board.state[i]=i;
    for(i=0;i<board_size;i++)
        printf("%d ",goal_board.state[i]);
    printf("testing goal board:\n");
    print_board(&goal_board);
    printf("\n ");
    int is_goal = isGoalstate(&goal_board);
    printf("testing isGoalState is goal:");
    if(assert(is_goal,1)==0)
    {
        print_board(&goal_board);
        return 1;
    }
}

int test_goal_board_fail()
{
    board_size=9;
    board goal_board;
    int i;
    int bad_vec[] = {3,2,1,5,6,7,4,8,0};
    for(i=0;i<board_size;i++)
        goal_board.state[i]=bad_vec[i];
    int is_goal = isGoalstate(&goal_board);
    printf("testing isGoalState is not goal:");
    assert(is_goal,0);
}

int test_findblank(){
    board_size=9;
    board test_board;
    int i;
    int sample_vec[] = {8, 3, 5, 7, 2, 6, 0, 4, 1};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    int blancPosition = findblankposition(&test_board);
    printf("testing findblankpositon :");
    assert(test_board.blankposition,6);
}

int test_next_boards_prints(){
    board_size=9;
    board_side_size=3;
    board test_board;
    int i;
    int sample_vec[] = {1, 0, 7, 2, 4, 3, 6, 8, 5};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards1 :\n");    
    calculate_next_boards_printf_possible(&test_board);
    //assert(test_board.blankposition,6);
}

int test_next_boards_prints2(){
    board_size=9;
    board_side_size=3;
    board_side_size=3;
    board test_board;
    int i;
    int sample_vec[] = {3, 5, 2, 0, 8, 1, 4, 6, 7};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards2 :\n");    
    calculate_next_boards_printf_possible(&test_board);
    //assert(test_board.blankposition,6);
}

int test_next_boards_prints3(){
    board_size=9;
    board_side_size=3;
    board_side_size=3;
    board test_board;
    int i;
    int sample_vec[] = {3, 5, 2, 8, 0, 1, 4, 6, 7};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards3 :\n");    
    calculate_next_boards_printf_possible(&test_board);
    //assert(test_board.blankposition,6);
}

int test_next_boards_prints4(){
    board_size=9;
    board_side_size=3;
    board_side_size=3;
    board test_board;
    int i;
    int sample_vec[] = {3, 5, 2, 8, 6, 1, 4, 0, 7};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards4 :\n");    
    calculate_next_boards_printf_possible(&test_board);
    //assert(test_board.blankposition,6);
}



int test_next_boards(){
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {3, 5, 2, 8, 6, 1, 4, 0, 7};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards :\n");    
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}

int test_next_boards2(){
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    test_board.last_move=moveDown;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {1, 8, 7, 5, 0, 4, 2, 3,6};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("****\ntesting next_boards2 :\n");    
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}

int test_next_boards3(){
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {1, 2, 5, 3, 4, 0, 6, 7, 8};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards3 :\n");    
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}
int test_next_boards4(){
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    test_board.last_move=moveRight;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {1, 2, 5, 3, 4, 8, 6, 7, 0};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards4 aqui  :\n");
    calculate_next_boards_printf_possible(&test_board);
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}


int test_next_boards5(){
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    test_board.last_move=moveLeft;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {3, 1, 2, 6, 4, 5, 7, 0, 8};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards5 aqui  :\n");
    calculate_next_boards_printf_possible(&test_board);
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}
int test_next_boards6(){
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    test_board.last_move=moveLeft;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {3, 1, 2, 6, 4, 5, 0, 7, 8};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards6 aqui  :\n");
    calculate_next_boards_printf_possible(&test_board);
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}
int test_next_boards7(){
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
    board_size=9;
    board_side_size=3;
    board test_board;
    next_boards nexts;
    test_board.last_move=moveUp;
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {3, 1, 2, 0, 4, 5, 6, 7, 8};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards7 aqui  :\n");
    calculate_next_boards_printf_possible(&test_board);
    calculate_next_boards(&nexts,&test_board);
    
    printf("printing before board:\n");
    print_board(&test_board);
    for(i=0;i<nexts.number_of_moves;i++)
    {
        printf("printing next board: %d\n",i);
        if(isGoalstate(nexts.next[i])==1)
            printf("eeeh goal state\n");
        print_board(nexts.next[i]);
    }
        
    //assert(test_board.blankposition,6);
}

void testhasing()
{
    printf("testing hashing\n");
    board_size=16;
    board_side_size=4;
    board test_board;
    int sample_vec[] ={3, 15, 2, 5, 11, 6, 4, 7, 12, 9, 1, 0, 13, 14, 10, 8};
    //./main -astar 3 15 2 5 11 6 4 7 12 9 1 0 13 14 10 8
    int i;
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];

    unsigned long long hash = hashing_board(&test_board);
    board *test_board2=unhash_board(hash);
    print_board(test_board2);
}

void printgoal16hash()
{
    printf("testing hashing\n");
    board_size=16;
    board_side_size=4;
    board test_board;
    int sample_vec[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //./main -astar 3 15 2 5 11 6 4 7 12 9 1 0 13 14 10 8
    int i;
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    unsigned long long hash = hashing_board(&test_board);
    printf("goal hash %lld\n",hash);
    board *test_board2=unhash_board(hash);
    print_board(test_board2);
}
void printgoal9hash()
{
    printf("testing hashing\n");
    board_size=9;
    board_side_size=3;
    board test_board;
    int sample_vec[] ={0, 1, 2, 3, 4, 5, 6, 7, 8};
    //./main -astar 3 15 2 5 11 6 4 7 12 9 1 0 13 14 10 8
    int i;
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    unsigned long long hash = hashing_board(&test_board);
    printf("goal hash %lld\n",hash);
    board *test_board2=unhash_board(hash);
    print_board(test_board2);
}

void testing_findinggoal16()
{
    printf("testing goal hitting\n");
    board_size=16;
    board_side_size=4;
    board test_board;
    int sample_vec[] ={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    //./main -astar 3 15 2 5 11 6 4 7 12 9 1 0 13 14 10 8
    int i;
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    unsigned long long hash = hashing_board(&test_board);
    printf("goal hash %lld\n",hash);
    board *test_board2=unhash_board(hash);
    print_board(test_board2);
    printf("goal hash %lld isgoal? %d\n",hash,isGoalstateASTAR(hash));
}

int main()
{
    //test_goal_board();
    //test_goal_board_fail();
    //test_findblank();
    //test_next_boards_prints();
    //test_next_boards_prints2();
    //test_next_boards_prints3();
    //test_next_boards_prints4();
    //test_next_boards();
    //test_next_boards2();
    //test_next_boards3();
    //test_next_boards4();
    //test_next_boards5();
    //test_next_boards6();
    //test_next_boards7();
    printf("PQP next_boards7\n");
    testhasing();
    printgoal16hash();
    printgoal9hash();
    testing_findinggoal16();
}