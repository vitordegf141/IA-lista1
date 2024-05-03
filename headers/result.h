#ifndef H_RESULT
#define H_RESULT


#include <time.h>
#include <stdio.h>
typedef struct result_struct{
    clock_t inicial_time;
    clock_t final_time;
    double time_passed;
    int total_heuristic;
    int inicial_heurisctic;
    int nodes_expanded;
    double average_heurisctic;
    int otimal_cost;
} result;

void start_time_count(result *res);
void stop_time_count(result *res);
void init_result(result *res, int inicial_heuristic);
void add_node_to_result(result *res,int heurisctic);
void calculate_result(result *res, int otimal_cost);
void print_result(result *res);

#endif