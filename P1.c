#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main(int argc, char * argv[]) {
    int fd;
    int VALUE=1;
    sem_t *s;
    
	//If semaphore with name "s" does not exist, then create it with VALUE
    s = sem_open("s", O_CREAT, 0666, VALUE);
    
	//can I access the shared file?
    sem_wait(s);
    fd=open("data", O_CREAT|O_RDWR|O_APPEND, 0777);
    write(fd,"P1 prints 1 2 3 4 ",18);
    close(fd);
   
    //semSignal to signal that the shared resource (file) is available
    sem_post(s);
    
	//Before exit, you need to close semaphore and unlink it, when all  processes have
    //finished using the semaphore, it can be removed from the system using sem_unlink
    sem_close(s);
    sem_unlink("s");
    return 0;
}