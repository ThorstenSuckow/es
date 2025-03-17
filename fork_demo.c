#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void main() {

    int child_p = fork();

    if (child_p == 0) {
        printf("I am the child process, thus my PID be %d\n", child_p);
        exit(0);
    }

    printf("I spawned the child process, which PID was %d\n", child_p);

}
