// non part of the code, just for testing

#include <stdio.h>
#include "../headers/board.h"

// gcc test_board.c "../objects/board.o" -o test
void assert(int value, int expected)
{
    if(value==expected)
        printf(" PASSED");
    else
        printf("FAILED");
    printf("\n");
}

int test_goal_board()
{
    board_size=9;
    board goal_board;
    int i;
    for(i=0;i<board_size;i++)
        goal_board.state[i]=i;
    int is_goal = isGoalstate(&goal_board);
    printf("testing isGoalState is goal:");
    assert(is_goal,1);
}

int test_goal_board_for15()
{
    board_size=16;
    board goal_board;
    int i;
    for(i=0;i<board_size;i++)
        goal_board.state[i]=i;
    int is_goal = isGoalstate(&goal_board);
    printf("testing isGoalState for 15 is goal:");
    assert(is_goal,1);
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
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {1, 8, 7, 5, 0, 4, 2, 3,6};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards2 :\n");    
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
    nexts.number_of_moves=0;
    int i;
    int sample_vec[] = {1, 2, 5, 3, 4, 8, 6, 7, 0};
    for(i=0;i<board_size;i++)
        test_board.state[i]=sample_vec[i];
    findblankposition(&test_board);
    printf("testing next_boards4 :\n");
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


int main()
{
    test_goal_board();
    test_goal_board_fail();
    test_findblank();
    test_next_boards_prints();
    test_next_boards_prints2();
    test_next_boards_prints3();
    test_next_boards_prints4();
    test_next_boards();
    test_next_boards2();
    test_next_boards3();
    test_next_boards4();
    test_goal_board_for15();
}