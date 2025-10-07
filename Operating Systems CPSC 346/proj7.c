/*
Class: CPSC 346-02
Team Member 1: Kevin Hance
Team Member 2: N/A 
GU Username of project lead: khance
Pgm Name: proj7.c 
Pgm Desc: C program to illustrate pipe system call in C 
Usage: 1) standard:  ./a.out <integer>
<integer> is the parameter for how many random numbers the user wishes to write & read
*/

// NOTE: Needs to be compiled with "gcc proj7.c -pthread"
// Without this, there will be a handful of undefined reference errors.

#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#define MSGSIZE 16 

void* writeThreads(void*);
void* readThreads(void*);
int is_prime(int);

struct params
{
 int* pipeParam;
 int maxNums;
};

typedef struct params param;

int main(int argc, char* argv[])
{ 
    // input validation to ensure exactly 2 arguments were entered
    if(argc != 2){
        printf("Usage: ./a.out <integer>\nPlease try executing again with correct parameters\n");
        exit(-1);
    }
    
    // init threads, ints and parameters for thread creation
    pthread_t writeThread,readThread1,readThread2,readThread3;
    param writeP,readP1,readP2,readP3;
    int p[2], max_nums, current_rand, status;

    // convert user argument (String) into an int
    max_nums = atoi(argv[1]);

    // CREATE PIPE
    if (pipe(p) < 0) 
        exit(1); 

    // SETTING PARAMETERS FOR THREAD CREATION
    writeP.pipeParam = p;
    writeP.maxNums = max_nums;

    readP1.pipeParam = p;
    readP1.maxNums = 1;

    readP2.pipeParam = p;
    readP2.maxNums = 2;

    readP3.pipeParam = p;
    readP3.maxNums = 3;

    // CREATING THREADS
    status = pthread_create(&writeThread, NULL, writeThreads, (void*)&writeP);
    if (status != 0)
    {
        printf("Error in thread 1:  %d\n",status);
        exit(-1);
    }

    status = pthread_create(&readThread1, NULL, readThreads, (void*)&readP1);
    if (status != 0)
    {
        printf("Error in thread 2:  %d\n",status);
        exit(-1);
    }

    status = pthread_create(&readThread2, NULL, readThreads, (void*)&readP2);
    if (status != 0)
    {
        printf("Error in thread 3:  %d\n",status);
        exit(-1);
    }

    status = pthread_create(&readThread3, NULL, readThreads, (void*)&readP3);
    if (status != 0)
    {
        printf("Error in thread 4:  %d\n",status);
        exit(-1);
    }

    // JOIN THREADS
    pthread_join(writeThread,NULL);
    pthread_join(readThread1,NULL);
    pthread_join(readThread2,NULL);
    pthread_join(readThread2,NULL);

    return 0;
}

void* writeThreads(void *vargp)
{
    // init param struct, pipe array, and ints
    param* p = (param*) vargp;
    int* pipe = p->pipeParam;
    int max_nums = p->maxNums;
    int nums_generated = 0;
    int current_rand;
    // set seed to the time for rand()
    srand(time(0));
    // write to pipe 'max_nums' number of times
    while(nums_generated < max_nums)
    {
        // get a random number
        current_rand = rand();
        // write char array to pipe
        write(pipe[1], &current_rand, sizeof(int));
        // display generated number
        printf("Generated:\t%d\n", current_rand);
        // increment counter
        nums_generated++;
    }
    // newline, close writing-end of pipe, exit thread
    printf("\n");
    close(pipe[1]);
    pthread_exit(NULL);
}



void* readThreads(void *vargp)
{   
    //init thread parameter
    param* p = (param*)vargp;
    // init pipe array
    int* pipe = p->pipeParam;
    // init int to hold ID of thread
    int threadNum = p->maxNums;
    // init int to hold values after being read
    int num;
    // read pipe into char array 'inbuf'
    while(read(pipe[0], &num, sizeof(int))){
        // sleep for 10 milliseconds (10 * 1000 microseconds)
        usleep(10000);
        // if num is prime, print it (along with the ID of the thread that calculated it) to the console
        if(is_prime(num))
            printf("Reader %d\t%d is prime\n", threadNum, num);
    }
    // exit thread
    pthread_exit(NULL);
}

// I took this function directly from ex18.c
int is_prime(int num)
{
 int i = 2;
 while (i < num)
 {
  if (num % i == 0)
     return 0;
  ++i;
 }
 return 1;
}