#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>


void main() {

    int fds[2]; // file descriptors

    int status;

    pipe(fds);

    if (fork() == 0) {

        char *text = "Hello world!";
    
        dup2(fds[1], 1);
        close(fds[0]);

        write(1, text, strlen(text) + 1);
    
    } else if (fork() == 0) {

        char buffer[5];

        int count;

        dup2(fds[0], 0);
        close(fds[1]);

        while(count = read(0, buffer, 4)) {
            buffer[count] = 0;
            printf("%s", buffer);
        }
        printf("\n");

    } else {
        close(fds[0]);
        close(fds[1]);
        wait(&status);
        wait(&status);
    }

    exit(0);

}