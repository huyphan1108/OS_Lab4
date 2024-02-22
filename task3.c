#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <time.h>
#include <stdlib.h>

sem_t s; 		//a semaphore s


//function prototype
void* threadFunction(void* param); 

int main() 
{ 
    srand(time(NULL));
    
	//initialize the unnamed semaphore s using: sem_init(&s, 0, 1);
	//&s is the pointer to the semaphore
	//0 means that this semaphore is shared by threads created by this process
	//1 sets the initial value of the semaphore to 1
	sem_init(&s, 0, 1); 
	
	//pthread_t t0,t1; 
	pthread_t student[7];
	int tnumber = 1;
	
	for (int i = 0; i < 7; i++){
	    pthread_create(&student[i], NULL, threadFunction, &tnumber);
	    sleep(2);
	    tnumber++;
	}
	
	for (int i = 0; i < 7; i++){
	    pthread_join(student[i], NULL);
	}
	
	sem_destroy(&s);
	
	return 0; 
} 

void* threadFunction(void* param) 
{ 
	int tnum;
	tnum = *((int *)param);
	
	
	sem_wait(&s); 			//can I access my critical section? (semWait())
	
	//critical section 
	printf("\nStudent %d  wants to use the software\n", tnum); 
	printf("\nStudent %d  has checked out a license...\n", tnum);
	
	sem_post(&s); 		//signal that the thread is leaving and the CS is free (semSignal())
	
	int r = (rand() % 5) + 1;
	sleep(r); 
	
	printf("\nStudent %d  has finished using the software and is checking in their license...\n", tnum);
	
	pthread_exit(0);
}