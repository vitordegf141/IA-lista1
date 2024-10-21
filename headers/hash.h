#ifndef HEADER_HASH
#define HEADER_HASH

#define TABLE_SIZE 3294912
#define TABLE_SIZING 10
#define BOARD_SIZE 16
#define EH_IDENTIFICADOR 1
#define EH_LITERAL 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
typedef struct Hnode
{
    char *name;
    int appearences;
    struct Hnode *next;
} Hash_node;

Hash_node * hashtable[TABLE_SIZING][TABLE_SIZE];

unsigned long hash1(char *str);
int next_has_simbol(Hash_node *simbol_root,char *name);
int has_simbol(char *name);
Hash_node *create_simbol(char *simbol_name);
void insert_in_next( Hash_node *simbol_root,char *new_simbol);
void print_hashtable(int do_print);
int insert_simbol(char *name);
void print_colissions(int do_print);
void initHashTable();
void print_bigcolissiongs(int do_print);

#endif