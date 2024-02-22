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
    s = sem_open("s", O_CREAT, 0666, VALUE);	//create the semaphore if it doe snot exist; init to 1
    
	//can I access the shared file?
    sem_wait(s);
    fd=open("data", O_CREAT|O_RDWR|O_APPEND, 0777);
    write(fd,"P2 prints 5 6 7 8 ",18);
    close(fd);
	
	//semSignal to indicate the shared file is available
    sem_post(s);
    sem_close(s);
    sem_unlink("s");
    return 0;
}