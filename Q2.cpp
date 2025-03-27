#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { // Child process
        write(fd, "Child writing...\n", 17);
        close(fd);
    } else { // Parent process
        write(fd, "Parent writing...\n", 18);
        close(fd);
        wait(NULL);
    }

    return 0;
}
