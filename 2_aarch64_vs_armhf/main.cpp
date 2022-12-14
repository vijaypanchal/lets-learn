#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "inc/inc.h"
#define DEBUG_PRINT 
#undef DEBUG_PRINT
#define STATIC_ALLOC
#undef STATIC_ALLOC
#define DATA_SIZE   10*1000
#define PROC_LOOP   10*1000 

#ifdef STATIC_ALLOC
float input[DATA_SIZE] = {0};
float output[DATA_SIZE] = {0};
float output_i[DATA_SIZE] = {0};
#endif

#define DATA_RANGE_MAX 1000.0f
#define DATA_RANGE_MIN -1000.0f

float random_int(float min, float max)
{
   return min + float(rand()/RAND_MAX) * (max-min);
}

int main(){
    srand( time(0));
    int size= DATA_SIZE;
#ifndef STATIC_ALLOC
    float *input = new float[size]{0};
    float *output = new float[size]{0};
    float *output_i = new float[size]{0};
#endif
    float slope = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);
    float constant = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);

    for(int i = 0; i < size; i++){
        input[i] = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);        
    }

    clock_t start = clock();
    for(int i = 0; i < PROC_LOOP ; i++){
        lib_process_api_c(input, &slope, &constant, output, size);
    }
    clock_t stop = clock();

    clock_t diff = (stop - start);
    double cpu_time_used = ((double) diff) / CLOCKS_PER_SEC; 
#ifdef DEBUG_PRINT
    printf("\nStart -> %u Stop-> %u Diff-> %u", start, stop, diff);
#endif
    printf("\nlib_process_api_f : Time taken %f seconds to execute \n", cpu_time_used);

#if ARM_NEON == 1
    clock_t start_i = clock();
    for(int i = 0; i < PROC_LOOP ; i++){
        lib_process_api_intrinsics(input, &slope, &constant, output_i, size);
    }
    clock_t stop_i = clock();

    clock_t diff_i = (stop_i - start_i);
    double cpu_time_used_i = ((double) diff_i) / CLOCKS_PER_SEC; 

    for(int i = 0; i < size; i++){
        if(output[i] != output_i[i])
            printf("ERROR: Observed for output[%d] = %f & output_i[%f] = %d \n",i, output[i], i, output_i[i]);
    }

#ifdef DEBUG_PRINT    
    printf("\nStart -> %u Stop-> %u Diff-> %u", start_i, stop_i, diff_i);
#endif
    printf("\nlib_process_api_intrinsics -> Time taken %f seconds to execute \n", cpu_time_used_i);
    double improvement = (100.0*(cpu_time_used-cpu_time_used_i))/float(cpu_time_used);
    
    printf("Intrinsics Performance improvement : %f %c\n",improvement, '%');

#endif

#ifndef STATIC_ALLOC    
    delete [] input;
    delete [] output;
#endif
    return 0;
};