#include<stdio.h>

int main(int argc, char* argv)
{
    int a[100];
    for(int i=0; i<argc; i++)
    {
        a[i]=atoi(argv[i]);
    }
    for(int i=argc; i>=0; i--)
    {
        printf("%d ",&a[i]);
    }
}