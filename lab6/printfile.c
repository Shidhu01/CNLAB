#include<stdio.h>

int main()
{
    char c;

    FILE *fptr;
    fptr = (fopen("file1.txt", "r+"));
    c = fgetc(fptr);

    while( c != EOF)
    {
        printf("%c", c);
        c = fgetc(fptr);
    }
    fclose(fptr);
    return 0;
} 


    