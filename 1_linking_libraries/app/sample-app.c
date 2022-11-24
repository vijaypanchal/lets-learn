#include <stdio.h>
#include <stdlib.h>
#include <lib-header.h>

int main (int argc, char *argv[])
{
    int N = 10;	
    int result = find_squre(N);
    printf("Square of %d is %d !\n", N, result);
	return 0;
}
