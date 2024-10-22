
// implement a hashtable on array 

#include "../hash.h"
#include "../board.h"

Hash_node * hashtable[BOARD_SIZE][TABLE_SIZE];

int primes[]={7,11,13,17,19,23,29,31,37,41,43,47,53,59};
void print_name_board(char *name){
    for (int j=0;j<17;j++)
        {
            printf("%c",name[j]+48);
        }
}
unsigned long hash(char *name)
{
    unsigned long sum =0;
    for (int j=0;j<17;j++)
    {
        sum += name[j]*primes[j]+1;
        sum = sum << 5;
    }
    unsigned long result=sum % TABLE_SIZE;
    //printf("name = ");
    //print_name_board(name);
    //printf(" hash = %ld\n ",result);./
    return result;
}



int collisions=0;
int non_collisions=0;
int nexts_searchs=0;
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
    int i,j;
    for(i=0;i<BOARD_SIZE;i++)
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
    if(simbol_name == NULL)
    {
        printf("SIMBOL IS NULL\n");
        return NULL;
    }    
    
    Hash_node *newe = (Hash_node *) malloc(sizeof( Hash_node));
    int i;
    newe->name = (char *) malloc(sizeof(char)*(board_size+1));
    copy_name(newe->name,simbol_name);
    newe->next=NULL;
    return newe;
}

void insert_in_next( Hash_node *simbol_root,char *new_simbol){
    nexts_searchs++;
    if(simbol_root == NULL || new_simbol == NULL)
        return;
    else{
        if(cmp_name(simbol_root->name,new_simbol) != 0)
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

void print_hashtable(int do_print)
{
    if(do_print == 0)
        return;
    int i,j;
    printf("\nbegin\n");
    for(i=0;i<BOARD_SIZE;i++)
    {
        for(j=0;j<TABLE_SIZE;j++)
        {
            if(hashtable[i][j]!=NULL)
                printf("\n\t%d\t%s",i,hashtable[i][j]->name);
        }
        
    }
    printf("\nend\n");
}

int insert_simbol(char *name){
    if(name == NULL)
        return 0;
    unsigned long computed_hash = hash(name);
    if(hashtable[name[0]][computed_hash] != NULL){
        collisions++;
        if(cmp_name(hashtable[name[0]][computed_hash]->name,name) == 0)
        {
            return 1;
        }
        else{
            insert_in_next(hashtable[name[0]][computed_hash],name);
            return 1;
        }
    }
    else
    {
        non_collisions++;
        Hash_node *new_simbol=create_simbol(name);
        hashtable[name[0]][computed_hash]=new_simbol;
        return 1;
    }

    
    
}
int has_simbol(char *name){
    unsigned long computed_hash = hash(name);
    if(hashtable[name[0]][computed_hash] != NULL){
        if(cmp_name(hashtable[name[0]][computed_hash]->name,name) == 0)
            return 1;
        else 
            return next_has_simbol(hashtable[name[0]][computed_hash],name);
    }
    else
    {
        return 0;
    }
}
void print_colissions(int do_print){
    if(do_print!=0)
        printf("number of colissions = %d non colissions= %d searchs in nexts= %d\n",collisions,non_collisions,nexts_searchs);
    //106106387
    //106106327
}
