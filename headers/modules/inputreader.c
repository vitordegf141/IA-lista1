// reads the input and transform it into structs
#ifndef C_INPUTREADER
#define C_INPUTREADER

#include "../inputreader.h"
#include "../defines.h"
#include "../board.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int get_algorithm_from_input(char *input)
{
    if(!strcmp(input,"-bfs"))
        return bfs;
    if(!strcmp(input,"-idfs"))
        return idfs;
    if(!strcmp(input,"-astar"))
        return astar;
    if(!strcmp(input,"-idastar"))
        return idastar;
    if(!strcmp(input,"-gbfs"))
        return gbfs;
    printf("unknow algorithm\n");
}


void get_value_from_string(value_read *res,char string[], int is_last)
{
    if(res==NULL || string==NULL)
    {
        printf("get_value_from_string res or string is NULL\n");
        exit(1);
    }
    int i=0;
    int end_of_string=-1;
    char aux_string[max_num_size];
    if(string == NULL)
    {
        printf("get_value_from_string string is NULL\n");
        exit(1);
    }
    while(string[i]>=0 && string[i]<='9' && end_of_string<0)
    {
        if(string[i]=='\0' || string[i]==',')
            end_of_string =i;
        if(string[i]==',')
            res->has_comma =1;
        i++;
    }
    if((string[i]<0 || string[i]>'9') && (string[i]!='\0' || string[i]!=',') && !is_last)
    {
        printf("BAD INPUT string[i]=%s is_last =%d\n",&string[i],is_last);
        exit(1);
    }
    strcpy(aux_string,string);
    aux_string[end_of_string]='\0';
    res->value= atoi(aux_string);
}

char alt_get_value_from_string(char string[], int is_last)
{
    if( string==NULL)
    {
        printf("alt_get_value_from_string res or string is NULL\n");
        exit(1);
    }
    int i=0;
    int end_of_string=-1;
    char aux_string[max_num_size];
    if(string == NULL)
    {
        printf("get_value_from_string string is NULL\n");
        exit(1);
    }
    while(string[i]>='0' && string[i]<='9' && end_of_string<0)
    {
        
        if(string[i]=='\0' || string[i]==',')
            end_of_string =i;
        i++;
    }
    if((string[i]<0 || string[i]>'9') && (string[i]!='\0' || string[i]!=',') && !is_last)
    {
        printf("BAD INPUT string[i]=%s is_last =%d\n",&string[i],is_last);
        exit(1);
    }
    strcpy(aux_string,string);
    aux_string[end_of_string]='\0';
    return atoi(aux_string);
}


int get_matrixes_from_input(int argc,char *argv[])
{
    int count_matrix=0;
    int i;
    int inicial_matrix[16];
    value_read value;
    value.value=-1;
    value.has_comma=-1;
    printf("argc size = %d\n", argc);
    printf("argv preastlast = %s ",argv[argc-1]);
    printf("argv last = %s\n",argv[argc]);
    if(argc<=10)
    {
        printf("insuficient args\n");
        exit(1);
    }
    int board_size=0;
    for(i=2;i<argc && argv[i]!=NULL && value.has_comma!=1;i++)
    {
        board_size++;
        if(board_size >16)
        {
            printf("BAD INPUT matrix size supported are only 9 and 16");
            exit(1);
        }
        get_value_from_string(&value,argv[i],argv[i+1]==NULL);
        //printf("board_size = %d, value found = %d\n",board_size,value.value);
        inicial_matrix[board_size-1]=value.value;
    }
    int j=0;
    if(value.has_comma)
        printf("matrix has ended in comma\n");
    while(value.has_comma)
    printf("inicial matrix found =\n");
    for(j=0;j<board_size;j++)
        printf("%d ",inicial_matrix[j]);
    
    return 0;
}

int alt_method(int argc,char *argv[], all_boards *boards)
{
    int input_lenght = argc -2;
    int is_nine= (input_lenght%9 ==0);
    int is_sixteen = (input_lenght%16 ==0);
    if(!is_nine && !is_sixteen){
        printf("BAD INPUT");
        exit(1);
    }

    if (is_nine && is_sixteen)
    {
        if(argv[9][2]==','){
            is_sixteen=0;
        }
        else
            is_nine=0;
    }

    int number_of_matrix;
    if(is_nine){
        number_of_matrix = input_lenght/9;
        board_size=9;
        board_side_size=3;
    }
        
    else if(is_sixteen){
        number_of_matrix = input_lenght/16;
        board_size=16;
        board_side_size=4;
    }
    boards->boards = (board*) malloc(sizeof(board)*number_of_matrix);
    int i,j; 
    int aux;
    for(i=0;i<number_of_matrix;i++){
        for(j=0;j<16;j++)
            if(j>=board_size)
                boards->boards[i].state[j] ='\0'; //Needed for hash function
            else
                boards->boards[i].state[j] =alt_get_value_from_string(argv[(i*board_size)+j+2],argv[(i*board_size)+j+2+1]==NULL);
        boards->boards[i].blankposition=findblankposition(&boards->boards[i]);
        boards->boards[i].heurisc_value=-1;
    }
    
    return number_of_matrix;
}

#endif