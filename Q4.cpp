#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    printf("hello world (pid:%d)\n", (int) getpid());

    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child process
        printf("hello, I am child (pid:%d)\n", (int) getpid());

        // Close standard output
        close(STDOUT_FILENO);

        printf("This won't be printed!\n");
    } else { // parent process
        wait(NULL); 
        printf("I am parent (pid:%d)\n", (int) getpid());
    }

    return 0;
}
