#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void main() {

    int child_p = fork();
    int status = 0;

    if (child_p == 0) {
        printf("I am the child process, thus my PID be %d (%d)\n", child_p, getpid());
        exit(0);
    }
    wait(&status);
    printf("I spawned the child process, which PID was %d\n", child_p);
    printf("The child processed ended, raw status holds %d (WEXITSTATUS: %d)\n", status, WEXITSTATUS(status));	
    
       
}
