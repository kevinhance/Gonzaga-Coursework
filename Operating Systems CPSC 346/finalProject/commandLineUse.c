#include <stdio.h>
int main(int argc, char *argv[])
{
    argc = sizeof(argv);
    if(argc != 3)
        puts("Please enter 2 integers following program call to get sum");
    else
    {
        puts("Sum of ");
        puts(argv[1]);
        puts(" plus ");
        puts(argv[2]);
        puts(" equals ");
        puts(argv[1] + argv[2]);
    }
    return 0;
}