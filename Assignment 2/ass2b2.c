#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc, char* argv)
{
    int a[100];
    for(int i=0; i<argc; i++)
    {
        a[i]=atoi(argv[i]);
    }
    for(int i=argc-1; i>=0; i--)
    {
        printf("%d ",a[i]);
    }
}