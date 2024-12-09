


#ifndef H_BOARD
#define H_BOARD


#define STATE_SIZE 16
#define moveUp 1
#define moveDown 2
#define moveRight 3
#define moveLeft 4
#define initial -1


typedef struct board_struct{
    char state[STATE_SIZE];
    unsigned char blankposition;
    unsigned char heurisc_value;
    unsigned char cost;
    unsigned char last_move;
} board;

typedef struct boardstar_struct{
    unsigned long long int state;
    unsigned char blankposition;
    unsigned char heurisc_value;
    unsigned char cost;
    unsigned char last_move;
} boardstar;
typedef struct all_boards_struct
{
    board *boards;
    int num_of_boards;
} all_boards;

typedef struct next_boards_struct{
    board *next[4];
    int number_of_moves;
} next_boards;

typedef struct node_s_astar {
    unsigned char f;
    unsigned char h;
    unsigned int order;
    unsigned long long int hash;
    unsigned char last_move;
} astar_node;

extern int board_size;
extern int board_side_size;

int isGoalstate(board *state);
int findblankposition(board *state);
void board_to_string(char *state,char *outstring);
void print_board(board *state);
void calculate_next_boards_printf_possible(board *state);
int compare_boards(board *state1,board *state2);
void calculate_next_boards(next_boards *nexts, board *state);
unsigned long long int hashing_board(board *state);
board* unhash_board(unsigned long long int hash);
int isGoalstateASTAR(unsigned long long int state);
void calculate_next_boardsastar(next_boards *nexts, astar_node *node);
#endif