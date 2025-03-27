#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

void main() {

    int status;
    int ret = fork();

    if (ret == 0) {
        printf("K: Meine PID ist %d\n", getpid());
        printf("   Meine Parent-PID ist %d\n", getppid());
        exit(0);
    } else {
        wait(&status);
        printf("E: Meine PID ist %d\n", getpid());
        printf("   Die PID meines Kindprozesses ist %d\n", ret);
        exit(0);
    }

}