
// implement a hashtable on array 

#include "../hash.h"
#include "../board.h"

int primes[]={7,11,13,17,19,23,29,31,37,41,43,47,53,59};
void print_name_board(char *name){
    for (int j=0;j<17;j++)
        {
            printf("%c",name[j]+48);
        }
}

unsigned long hash1(char *str)
{
    unsigned long hash = 538112;
    int c;

    int i;
    for(i=0;i<BOARD_SIZE;i++)
    {
        c=str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
        

    return hash%TABLE_SIZE;
}

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
unsigned long hash21(char* key) {
    unsigned long hash = FNV_OFFSET;
    int i;
    char p;
    for(i=0;i<BOARD_SIZE;i++) {
        hash ^= (key[i]);
        hash *= FNV_PRIME;
    }
    return hash%TABLE_SIZE;
}

unsigned long hash2(char *str)
{
    unsigned long hash = FNV_OFFSET;
    int c;

    int i;
    for(i=0;i<BOARD_SIZE;i++)
    {
        c=str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
        

    return hash%TABLE_SIZING;
}


int collisions=0;
int non_collisions=0;
int nexts_searchs=0;
int uniques_names=0;
void copy_name(char *dest,char *origin){
    int i;
    for(i=0;i<board_size;i++)
    {
        dest[i]=origin[i];
    }
}

int cmp_name( char *dest,char *origin){
    int i, value=0;
    for(i=0;i<board_size;i++)
    {
        value +=abs(dest[i]-origin[i]);
    }
    return value;
}

void initHashTable()
{
    collisions=0;
    non_collisions=0;
    nexts_searchs=0;
    int i,j;
    for(i=0;i<TABLE_SIZING;i++)
    {
        for(j=0;j<TABLE_SIZE;j++ )
            hashtable[i][j]=NULL;
    }
}

int next_has_simbol(Hash_node *simbol_root,char *name)
{
    if(simbol_root == NULL)
        return 0;
    else{
         if(cmp_name(simbol_root->name,name) == 0)
            return 1;
        else
        {
            return next_has_simbol(simbol_root->next,name);
        }
    }
}

 Hash_node *create_simbol(char *simbol_name)
{
    uniques_names++;
    if(simbol_name == NULL)
    {
        printf("SIMBOL IS NULL\n");
        return NULL;
    }    
    
    Hash_node *new = malloc(sizeof( Hash_node));
    int i;
    new->name = malloc(sizeof(char)*(board_size+1));
    copy_name(new->name,simbol_name);
    new->next=NULL;
    return new;
}

void insert_in_next( Hash_node *simbol_root,char *new_simbol){
    nexts_searchs++;
    if(simbol_root == NULL || new_simbol == NULL)
        return;
    else{
        if(cmp_name(simbol_root->name,new_simbol) != 0)
        {
            if(simbol_root->next == NULL)
            {
                simbol_root->next = create_simbol(new_simbol);
            }
            else
            {
                insert_in_next(simbol_root->next,new_simbol);
            }
        }
            
    }
}

void get_good_string(char *good_string,char *bad_string)
{
    int i;
    for(i=0;i<BOARD_SIZE;i++)
    {
        good_string[i] = bad_string[i] + 48;
    }
}

void print_board2(char *board)
{
    char good_string[BOARD_SIZE];
    get_good_string(good_string,board);
    printf("%s",good_string);
}

void print_next(Hash_node *next)
{
    if(next ==NULL)
        return;
    else
    {
        printf(" - ");
        print_board2(next->name);
        print_next(next->next);
    }
}
void print_hashtable(int do_print)
{
    if(do_print == 0)
        return;
    int i,j;
    

    printf("\nbegin\n");
    for(i=0;i<TABLE_SIZING;i++)
    {
        for(j=0;j<TABLE_SIZE;j++)
        {
            if(hashtable[i][j]!=NULL)
            {
                
                printf("\n\t%d\t%ld\t",i,hash1(hashtable[i][j]->name));
                print_board2(hashtable[i][j]->name);
                print_next(hashtable[i][j]->next);
            }
                
        }
        
    }
    printf("\nend\n");
}

int insert_simbol(char *name){
    if(name == NULL)
        return 0;
    unsigned long computed_hash = hash1(name);
    unsigned long computed_hash2 = hash2(name);
    if(hashtable[computed_hash2][computed_hash] != NULL){
        collisions++;
        if(cmp_name(hashtable[computed_hash2][computed_hash]->name,name) == 0)
        {
            return 1;
        }
        else{
            insert_in_next(hashtable[computed_hash2][computed_hash],name);
            return 1;
        }
    }
    else
    {
        non_collisions++;
        Hash_node *new_simbol=create_simbol(name);
        hashtable[computed_hash2][computed_hash]=new_simbol;
        return 1;
    }

    
    
}
int has_simbol(char *name){
    unsigned long computed_hash = hash1(name);
    unsigned long computed_hash2 = hash2(name);
    if(hashtable[computed_hash2][computed_hash] != NULL){
        if(cmp_name(hashtable[computed_hash2][computed_hash]->name,name) == 0)
            return 1;
        else 
            return next_has_simbol(hashtable[computed_hash2][computed_hash],name);
    }
    else
    {
        return 0;
    }
}

int last_number_of_collions_printed =1;
void print_bigcolissiongs(int do_print)
{
    int percentage_free;
    if(do_print!=0)
    {
        if(collisions >= last_number_of_collions_printed * 5000000)
        {
            printf("number of colissions = %d non colissions= %d searchs in nexts= %d unique names = %d\n",collisions,non_collisions,nexts_searchs, uniques_names);
            last_number_of_collions_printed++;
            int i,j;
            int count =0;
            for(i=0;i<TABLE_SIZING;i++)
            {
                for(j=0;j<TABLE_SIZE;j++)
                {
                    if(hashtable[i][j]==NULL)
                        count++;
                }
                
            }
            int free_space = count/3294912L;
            printf(" number of empty spaces = %d percetage free = %d \n",count, free_space);
        }
    }
    return;
}

void print_colissions(int do_print){
    if(do_print!=0)
    {
        printf("number of colissions = %d non colissions= %d searchs in nexts= %d\n",collisions,non_collisions,nexts_searchs);
        int i,j, count =0;
        for(i=0;i<TABLE_SIZING;i++)
        {
            for(j=0;j<TABLE_SIZE;j++)
            {
                if(hashtable[i][j]==NULL)
                    count++;
            }
            
        }
        printf(" number of empty spaces = %d\n",count);
    }   
    return;

    //106106387
    //106106327
}
