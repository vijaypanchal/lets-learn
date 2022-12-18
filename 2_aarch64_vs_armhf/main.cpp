#include <iostream>
#include <sys/time.h>
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "inc/inc.h"

long int GetMicrosecondCount()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

#define DATA_SIZE 32768
#define PROC_LOOP 10 * 1000

#define DATA_RANGE_MAX 1000.0f
#define DATA_RANGE_MIN -1000.0f

float random_int(float min, float max)
{
    return min + float(rand() / RAND_MAX) * (max - min);
}

int main()
{
    srand(time(0));
    int size = DATA_SIZE;
    for (size = 2; size <= DATA_SIZE; size = size * 2)
    {
        float *input = new float[size]{0};
        float *output = new float[size]{0};
        float *output_i = new float[size]{0};

        float slope = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);
        float constant = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);

        for (int i = 0; i < size; i++)
        {
            input[i] = random_int(DATA_RANGE_MIN, DATA_RANGE_MAX);
        }

        clock_t start = clock();
        for (int i = 0; i < PROC_LOOP; i++)
        {
            lib_process_api_c(input, &slope, &constant, output, size);
        }
        clock_t stop = clock();

        clock_t diff = (stop - start);
        double cpu_time_used = ((double)diff) / CLOCKS_PER_SEC;

#if ARM_NEON == 1
        clock_t start_i = clock();
        for (int i = 0; i < PROC_LOOP; i++)
        {
            lib_process_api_intrinsics(input, &slope, &constant, output_i, size);
        }
        clock_t stop_i = clock();

        clock_t diff_i = (stop_i - start_i);
        double cpu_time_used_i = ((double)diff_i) / CLOCKS_PER_SEC;

        for (int i = 0; i < size; i++)
        {
            if (output[i] != output_i[i])
                printf("ERROR: Observed for output[%d] = %f & output_i[%f] = %d \n", i, output[i], i, output_i[i]);
        }
        double improvement = (100.0 * (cpu_time_used - cpu_time_used_i)) / float(cpu_time_used);
#endif
        printf("--------------------------------------------------------\n");
        printf("lib_process_api_f()     Size : %5d   Time : %f sec \n", size, cpu_time_used);
#if ARM_NEON == 1
        printf("lib_process_api_i()     Size : %5d   Time : %f sec \n", size, cpu_time_used_i);
        printf("--------------------------------------------------------\n");
        printf("Improvement :   %.3f %c\n", improvement, '%');
        printf("--------------------------------------------------------\n");
#endif
        delete[] input;
        delete[] output;
        delete[] output_i;
    }
    return 0;
};