// implement manhathan distance
#ifndef C_MANHATHAN
#define C_MANHATHAN

#include "../manhattan.h"
#include <stdlib.h>
#include <stdio.h>

int calculate_manhathan(board *state,int print)
{
    int i,j;
    int right_line,right_column,aux,divde;
    int value=0;
    int now_line=0,now_column=0;
    for(i=0;i<board_size;i++)
    {
        if(state->state[i]!=0)
        {
            right_column=state->state[i]%board_side_size;
            right_line= state->state[i]/board_side_size;
            aux = abs(now_column-right_column) + abs(now_line-right_line);
            if(aux<0)
                printf("o mundo pirou\n");
            value+=aux;
        }
        
        if(print)
            printf("first value:%d right_line:%d now_line %d right_column %d now_column %d aux %d value %d\n",state->state[i],right_line,now_line,right_column,now_column,aux,value);
        now_column++;
        if(now_column>=board_side_size)
        {
            now_column=0;
            now_line++;
        }
    }
    return value;
}

#endif