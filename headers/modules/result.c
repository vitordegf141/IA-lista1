//implement resut struct to keep and show the results'

#ifndef C_RESULT
#define C_RESULT

#include "../result.h"

clock_t time_inicial;
clock_t time_final;

void start_time_count(result *res)
{
    res->inicial_time = clock();
}

void stop_time_count(result *res)
{
    res->final_time = clock();
}

void init_result(result *res, int inicial_heuristic){
    start_time_count(res);
    res->nodes_expanded=0;
    res->total_heuristic=0;
    res->average_heurisctic=0;
    res->inicial_heurisctic=inicial_heuristic;
}

void add_node_to_result(result *res,int heurisctic)
{
    res->total_heuristic +=heurisctic;
    res->nodes_expanded++;
}

void calculate_result(result *res, int otimal_cost)
{
    stop_time_count(res);
    res->time_passed = ((double)(res->final_time - res->inicial_time))/CLOCKS_PER_SEC;
    if(res->nodes_expanded != 0)
        res->average_heurisctic = res->total_heuristic/ res->nodes_expanded;
    res->otimal_cost=otimal_cost;
} 

void print_result(result *res)
{
    printf("%d,%d,%f,%f,%d\n",res->nodes_expanded,res->otimal_cost,res->time_passed,res->average_heurisctic,res->inicial_heurisctic);
}

#endif