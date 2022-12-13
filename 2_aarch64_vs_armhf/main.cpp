#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "inc/inc.h"
#define STATIC_ALLOC
#undef STATIC_ALLOC
#define DATA_SIZE   10*1000
#define PROC_LOOP   10*1000 

#ifdef STATIC_ALLOC
int input[DATA_SIZE] = {0};
int output[DATA_SIZE] = {0};
#endif

#define DATA_RANGE_MAX 100
#define DATA_RANGE_MIN -100


int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

int main(){
    srand( time(0));
    int size= DATA_SIZE;
#ifndef STATIC_ALLOC
    int *input = new int[size]{0};
    int *output = new int[size]{0};
#endif
    int slope = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);
    int constant = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);

    for(int i = 0; i < size; i++){
        input[i] = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);
        output[i] = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);
    }

    clock_t start = clock();
    for(int i = 0; i < PROC_LOOP ; i++){
        lib_api_process_data_c(input, &slope, &constant, output, size);
    }
    clock_t stop = clock();

    clock_t diff = (stop - start);
    double cpu_time_used = ((double) diff) / CLOCKS_PER_SEC; 
    printf("\nStart -> %u Stop-> %u Diff-> %u", start, stop, diff);
    printf("\nlib_api_process_data_f : Time taken %f seconds to execute \n", cpu_time_used);

#if ARM_NEON == 1
    clock_t start_i = clock();
    for(int i = 0; i < PROC_LOOP ; i++){
        lib_api_process_data_intrinsics(input, &slope, &constant, output, size);
    }
    clock_t stop_i = clock();

    clock_t diff_i = (stop_i - start_i);
    double cpu_time_used_i = ((double) diff_i) / CLOCKS_PER_SEC; 
    printf("\nStart -> %u Stop-> %u Diff-> %u", start_i, stop_i, diff_i);
    printf("\nlib_api_process_data_intrinsics -> Time taken %f seconds to execute \n", cpu_time_used_i);
#endif

#ifndef STATIC_ALLOC    
    delete [] input;
    delete [] output;
#endif
    return 0;
};