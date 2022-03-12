#include<stdio.h>
#include<stdlib.h>

void count(int mat[][4], int size)
{
    int z = 0;
    int j;
    int count = 1;
    while(z < size)    
    {
        count = 1;
        for (int i = 1; i < 4; ++i) {
            j = 0;
            for ( j = 0; j < i; ++j) {
                if(mat[z][i]==mat[z][j])
                {
                    break;
                }
            }
            if (i == j)
                count++;
        }
        printf("%d \n", count/2);
        z++;
    }
}

void main()
{
    int mat[10][4];
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 4; ++j) {
            scanf("%d", &mat[i][j]);
        }
    }
    count(mat, n);

    exit(0);
}