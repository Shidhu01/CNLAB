#include<stdio.h>
#include<dirent.h>
#include<string.h>

int main()
{
    char msg[1000], buf[20];
    struct dirent *de;

    DIR *dr = opendir(".");
    if(dr == NULL)
    {
        printf("Could not open current directory");
        return 0;
    }

    while((de = readdir(dr))!= NULL)
    {
        strcpy(buf, de->d_name);
        printf("%s\n", buf);
    }
    closedir(dr);

    return 0;
}