#include <stdio.h>
int main(int argc, char *argv[])
{
    int dynamicArray[];
    argc = sizeof(argv);
    if(argc != 2)
        puts("Please enter 1 integer following program call to see array of that size");
    else
    {
        dynamicArray = new int[argv[1]];
        for(int i = 0; i < argv[1]; i++) {
            dynamicArray[i] = 0;
        }
        puts(dynamicArray);
    }
    return 0;
}