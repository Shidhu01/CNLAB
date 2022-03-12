#include<stdio.h>
#include<stdlib.h>

void main(int argc, char const *argv[])
{
    int i, sum =0;

    for ( i = 1; i < argc; i++)
    {
        sum = sum + atoi(argv[i]);
    }
    
    printf("\nSum is = %d", sum);
    
}
