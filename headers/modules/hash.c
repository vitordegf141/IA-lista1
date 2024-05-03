#include "../hash.h"
#include "../board.h"

int primes[]={7,11,13,17,19,23,29,31,37,41,43,47,53,59};
unsigned long hash(char *name)
{
    unsigned long sum =0;
    for (int j=0;name[j]!='\0';j++)
    {
        sum += name[j]*primes[j];
        sum = sum << 5;
    }
    return sum % TABLE_SIZE;
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
    int i;
    for(i=0;i<TABLE_SIZE;i++)
    {
        hashtable[i]=NULL;
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
    int i;
    printf("\nbegin\n");
    for(i=0;i<TABLE_SIZE;i++)
    {
        if(hashtable[i]!=NULL)
            printf("\n\t%d\t%s",i,hashtable[i]->name);
    }
    printf("\nend\n");
}

int insert_simbol(char *name){
    if(name == NULL)
        return 0;
    unsigned long computed_hash = hash(name);
    if(hashtable[computed_hash] != NULL){
        collisions++;
        if(cmp_name(hashtable[computed_hash]->name,name) == 0)
        {
            return 1;
        }
        else{
            insert_in_next(hashtable[computed_hash],name);
            return 1;
        }
    }
    else
    {
        non_collisions++;
        Hash_node *new_simbol=create_simbol(name);
        hashtable[computed_hash]=new_simbol;
        return 1;
    }

    
    
}
int has_simbol(char *name){
    unsigned long computed_hash = hash(name);
    if(hashtable[computed_hash] != NULL){
        if(cmp_name(hashtable[computed_hash]->name,name) == 0)
            return 1;
        else 
            return next_has_simbol(hashtable[computed_hash],name);
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
