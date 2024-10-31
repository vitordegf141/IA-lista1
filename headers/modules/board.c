
//implements the board struct, calculate moves and gather state information
#ifndef C_BOARD
#define C_BOARD

#include "../board.h"
#include <stdio.h>
#include <stdlib.h>

int board_side_size;
int board_size;

typedef struct can_moves_s{
     int can_up;
     int can_left;
     int can_right;
     int can_down;
} can_moves;

int isGoalstate(board *state)
{
    int i;
    for (i = 0; i < board_size; i++)
        if (i != state->state[i])
            return 0;
    return 1;
}

void board_to_string(char *cin,char *out)
{
    int i=0;
    for(i=0;i<16;i++)
    {
        out[i] = cin[i]+48;
    }
    out[16]='\0';
}

int findblankposition(board *state)
{
    int i;
    for (i = 0; i < board_size; i++)
        if (state->state[i] == 0)
            break;
    state->blankposition = i;
    return i;
}

void calculate_next_boards_printf_possible(board *state)
{
    int x = (int)state->blankposition / board_side_size;
    int y = state->blankposition % board_side_size;
    int down_new = state->blankposition + board_side_size;
    int up_new = state->blankposition - board_side_size;
    int right_new = y + 1;
    int left_new = y - 1;
    printf("blankposition is = %d x = %d , y =%d\n", state->blankposition, x, y);
    if (down_new < board_size)
        printf("\tcan move down ");
    if (up_new >= 0)
        printf("\tcan move up ");
    if (right_new < board_side_size)
    {
        printf("\tcan move right right_new=%d ",right_new);
    }
        
    if (left_new >= 0)
        printf("\tcan move left ");
    printf("\n");
}

board *make_move(board *state, int next_blank_position)
{
    board *next_board = (board *)malloc(sizeof(board));
    int i;
    for (i = 0; i < board_size; i++)
        next_board->state[i] = state->state[i];
    int aux = next_board->state[next_blank_position];
    next_board->state[next_blank_position] = next_board->state[state->blankposition];
    next_board->state[state->blankposition] = aux;
    next_board->blankposition = next_blank_position;
    next_board->cost = state->cost +1;
    return next_board;
}

int compare_boards(board *state1,board *state2){
    int i;
    for (i = 0; i < board_size; i++)
        if (state1->state[i] != state2->state[i])
            return 0;
    return 1;
}

void add_at_next(next_boards *nexts, board *newstate)
{

    if (nexts == NULL || newstate == NULL || (nexts->number_of_moves<0 && nexts->number_of_moves>3))
    {
        printf("add_at_next nexts is NULL or newstate is NULL or nexts->number_of_moves is not between 0 and 3");
    }
    nexts->next[nexts->number_of_moves]=newstate;
    nexts->number_of_moves++;

}

can_moves *calculates_can_moves(board *state)
{// not used
    can_moves * moves = (can_moves *) malloc(sizeof(can_moves));
    moves->can_down,moves->can_left,moves->can_right,moves->can_up=0;
    int x = (int)state->blankposition / board_side_size;
    int y = state->blankposition % board_side_size;
    int down_new = state->blankposition + board_side_size;
    int up_new = state->blankposition - board_side_size;
    int right_new = y + 1;
    int left_new = y - 1;
    if (up_new >= 0)
        moves->can_up=1;
    if (left_new >= 0)
        moves->can_left=1;
    if (right_new < board_side_size)
        moves->can_right=1;
    if (down_new < board_size)
        moves->can_down=1;
}


void calculate_next_boards(next_boards *nexts, board *state)
{
    nexts->number_of_moves=0;
    int x = (int)state->blankposition / board_side_size;
    int y = state->blankposition % board_side_size;
    int down_new = state->blankposition + board_side_size;
    int up_new = state->blankposition - board_side_size;
    int right_new = y + 1;
    int left_new = y - 1;
    if (up_new >= 0)
        add_at_next(nexts,make_move(state,up_new));
    if (left_new >= 0)
        add_at_next(nexts,make_move(state,state->blankposition-1));
    if (right_new < board_side_size)
        add_at_next(nexts,make_move(state,state->blankposition+1));
    if (down_new < board_size)
        add_at_next(nexts,make_move(state,down_new));
    
}

void print_board(board *state)
{
    int i,j;
    for(i=0;i<board_side_size;i++)
    {
        for(j=0;j<board_side_size;j++)
        {
            printf("%d ",state->state[i*board_side_size+j]);
        }
        printf("\n");
    }
}

#endif