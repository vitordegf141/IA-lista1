


#ifndef H_BOARD
#define H_BOARD


#define STATE_SIZE 17

typedef struct board_struct{
    char state[STATE_SIZE];
    int blankposition;
    int heurisc_value;
    int cost;
} board;

typedef struct all_boards_struct
{
    board *boards;
    int num_of_boards;
} all_boards;

typedef struct next_boards_struct{
    board *next[4];
    int number_of_moves;
} next_boards;

int board_size;
int board_side_size;
int isGoalstate(board *state);
int findblankposition(board *state);
void print_board(board *state);
next_boards *calculate_next_boards_printf_possible(board *state);
next_boards *calculate_next_boards(next_boards *nexts, board *state);
#endif