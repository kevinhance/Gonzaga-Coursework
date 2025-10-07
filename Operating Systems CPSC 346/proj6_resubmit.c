/*
Class: CPSC 346-02
Team Member 1: Kevin Hance
Team Member 2: N/A 
GU Username of project lead: khance
Pgm Name: proj6.c 
Pgm Desc: 	implementation of semaphores so manage interprocess communication
			with a dual-process producer/consumer model.
Usage: 1):  ./a.out 
*/

// to Dr. DePalma: I used some of your Synchronize - exercise 21 code in my solution, I assumed
// that this was fine since you asked us to use that to understand semaphores.

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_MUTEX 1 
#define INIT_EMPTY 100 
#define INIT_FULL  0 
#define EMPTY_ARG  0 //used when argument is optional 

#define PROD 0
#define CONS 1

typedef struct sembuf sem_buffer;  //give it a more reasonable name

void set_sem_values(int,int,int);
void get_sem_values(int,int,int);
void set_sem_buffer(sem_buffer[],int);
int create_semaphore(int);
void fatal_error(char[]);
void cleanup(int,int,int);
void critSec(int);
void producer(int, int, int, sem_buffer[], sem_buffer[]);
void consumer(int, int, int, sem_buffer[], sem_buffer[]);



int main(int argc, char* argv[])
{
	sem_buffer s_wait[1], s_signal[1]; //create semaphore structs
	int mutex, empty, full; // semaphore IDs
	int value, status, ch_stat, i; // value of fork, status of parent & child, forloop counter
	int upper = 100; //initialize upper and lower bound for delays
	int lower = 1;
	//set wait/signal structs used in semop 
	set_sem_buffer(s_wait,-1);
	set_sem_buffer(s_signal,1);

	//create semaphore sets, pass in arbitrary int 
	mutex = create_semaphore(0);
	empty = create_semaphore(1);
	full = create_semaphore(2);
	
	//set semaphores to initial values (defined above)
	set_sem_values(mutex, empty, full);

	// print initial semaphore values to console
	printf("Intial semaphore values\n");
	get_sem_values(mutex, empty, full);
	
	//fork off a process
	if ((value = fork()) < 0){
	printf("fork");
	}
	else{
		if (value == 0)	//consumer
		  { 
			// child process is consumption
			consumer(mutex, empty, full, s_wait, s_signal);
		  }
		else    		//producer
		  { 
			// parent process is production
			producer(mutex, empty, full, s_wait, s_signal);
		   	status = wait(&ch_stat); //wait for child to exit after parent finishes
		  }
	}

	if (value == 0)
	 {
		//
		  sleep(1);
		  printf("Final semaphore values\n");
		  get_sem_values(mutex, empty, full);
	}
	return 0;
}


//create a semaphore set of 1 semaphore specified by key 
int create_semaphore(int key)
{
 int new_sem;
 if ((new_sem = semget(key, 1, 0777 | IPC_CREAT)) == -1)
   {
    perror("semget failed");
    exit(1);
   }
 return new_sem;
}

//set struct values for down/up ops to be used in semop
//By design, we will always refer to the 0th semaphore in the set
void set_sem_buffer(sem_buffer sem[], int op_val)
{
 sem[0].sem_num = 0;
 sem[0].sem_op = op_val;
 sem[0].sem_flg = SEM_UNDO;
} 

//set mutex, empty, full to initial values
//these semaphore sets consist of a single semaphore, the 0th 
void set_sem_values(int mutex, int empty, int full)
{
 semctl(mutex, 0, SETVAL, INIT_MUTEX);
 semctl(empty, 0, SETVAL, INIT_EMPTY);
 semctl(full, 0, SETVAL, INIT_FULL);
}

//retrieve value held by the 0th semaphore, which is the second arg.
//0 in the final argument indicates that it is not used 
void get_sem_values(int mutex, int empty, int full)
{
 int m, e, f; 
 m = semctl(mutex, 0, GETVAL, 0);
 e = semctl(empty, 0, GETVAL, 0);
 f = semctl(full, 0, GETVAL, 0);
 printf("mutex: %d empty: %d full: %d\n", m,e,f);
}

// simulates creation of/consumption of items
void critSec(int whom){
	if(whom == PROD){
		printf("Producer making an item\n");
	} else if(whom == CONS) {
		printf("Consumer consuming an item\n");
	} else {
		printf("invalid critSec input\n");
	}
}

// producer function with cmds to change semaphores
void producer(int mutex, int empty, int full, sem_buffer s_wait[], sem_buffer s_signal[]){
	int i = 0;
	for(int i = 0; i < 5; i++){
		semop(empty, s_wait, 1);
		semop(mutex, s_wait, 1);
		critSec(PROD);
		semop(mutex, s_signal, 1);
		semop(full, s_signal, 1);
		usleep(100); // sleep for 100 microseconds 
	}
	return;
}

// consumer function with cmds to change semaphores
void consumer(int mutex, int empty, int full, sem_buffer s_wait[], sem_buffer s_signal[]){
	int i = 0;
	for(int i = 0; i < 5; i++){
		semop(full, s_wait, 1);
		semop(mutex, s_wait, 1);
		critSec(CONS);
		semop(mutex, s_signal, 1);
		semop(empty, s_signal, 1);
		usleep(21000); // sleep for 2.1 milliseconds
	}
	return;
}
	



