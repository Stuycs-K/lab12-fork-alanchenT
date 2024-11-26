#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void throw_error() {
    printf("[ERROR %d]: %s\n", errno, strerror(errno));
    exit(errno);
}

int get_random_int() {
    int handle = open("/dev/random", O_RDONLY, 0);

    if (handle == -1) {
        throw_error();
    }

    int random_value;
    read(handle, &random_value, sizeof(int));

    close(handle);

    return random_value;
}

int child_process() {
    int time_before_death = (unsigned int)get_random_int() % 5 + 1;

    printf("%d %dsec\n", getpid(), time_before_death);

    sleep(time_before_death);

    printf("%d finished after %dsec\n", getpid(), time_before_death);

    return time_before_death;
}

void parent_process() {
    int status = 0;
    pid_t child_pid = wait(&status);

    printf("Main Process %d is done. Child %d slept for _SEC_ sec\n",
        getpid(),
        child_pid
    );
}

int main() {
    pid_t child_a, child_b;

    child_a = fork();

    if (child_a > 0) {
        printf("%d about to create 2 child processes\n", getpid());
    }

    if (child_a == 0) {
        child_process();
    } else if (child_a > 0) {

        child_b = fork();

        if (child_b == 0) {
            child_process();
        } else if (child_b > 0) {
            parent_process();
        } else {
            perror("Failed to fork\n");
            throw_error();
        }

    } else {
        perror("Failed to fork\n");
        throw_error();
    }

    return 0;
}
