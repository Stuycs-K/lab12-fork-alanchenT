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

int main() {
    printf("%d\n", get_random_int());
    return 0;
}
