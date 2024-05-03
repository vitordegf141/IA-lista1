// non part of the code, just for testing

#include <stdio.h>
#include "../headers/manhattan.h"
#include "../headers/board.h"

void assert(int value, int expected)
{
    if(value==expected)
        printf(" PASSED");
    else
        printf("FAILED");
    printf("\n");
}


void test_goal()
{
    board_size=9;
    board_side_size=3;
    board test_board;
    int i;
    int vec[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int vec1[] = {0, 6, 1, 7, 4, 2, 3, 8, 5};
    for(i=0;i<board_size;i++)
        test_board.state[i]=vec[i];    
    int value =calculate_manhathan(&test_board,0);
    printf("testing test_goal: result %d\n",value);
    assert(value,0);
}

void test_example1()
{
    board_size=9;
    board_side_size=3;
    board test_board;
    int i;
    int vec[] = {0, 6, 1, 7, 4, 2, 3, 8, 5};
    for(i=0;i<board_size;i++)
        test_board.state[i]=vec[i];    
    int value =calculate_manhathan(&test_board,0);
    printf("testing calculate_manhathan: result %d\n",value);
    assert(value,10);
}

void test_example2()
{
    board_size=9;
    board_side_size=3;
    board test_board;
    int i;
    int vec[] = {5, 0, 2, 6, 4, 8, 1, 7, 3};
    for(i=0;i<board_size;i++)
        test_board.state[i]=vec[i];    
    int value =calculate_manhathan(&test_board,1);
    printf("testing calculate_manhathan: result %d\n",value);
    assert(value,11);   
}

void test_example3()
{
    board_size=9;
    board_side_size=3;
    board test_board;
    int i;
    int vec[] = {2, 4, 7, 0, 3, 6, 8, 1, 5};
    for(i=0;i<board_size;i++)
        test_board.state[i]=vec[i];    
    int value =calculate_manhathan(&test_board,1);
    printf("testing calculate_manhathan: result %d\n",value);
    assert(value,11);   
}

int main()
{
    test_goal();
    test_example1();
    test_example2();
    test_example3();
}