#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

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

void child_process() {
    int time_before_death = (unsigned int)get_random_int() % 5 + 1;

    printf("%d %dsec\n", getpid(), time_before_death);
}

void parent_process() {

}

int main() {
    pid_t child_a, child_b;

    child_a = fork();

    if (child_a < 0) {
        perror("FORK FAIL (A) !!!\n");
        throw_error();
    } else if (child_a == 0) {
        printf("Hi from A\n");
        child_process();
    } else {
        child_b = fork();

        if (child_b < 0) {
            perror("FORK FAIL (B) !!!\n");
            throw_error();
        } else if (child_b == 0) {
            printf("Hi from B\n");
            child_process();
        } else {
            printf("Hi from parent\n");
        }
    }
    return 0;
}
