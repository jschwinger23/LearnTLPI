#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXSIZE 1024

int main(int argc, char *argv[]) {
    int fd, n, flags;
    mode_t mode;
    char buf[MAXSIZE];

    flags = O_CREAT | O_WRONLY;
    if (argc == 3 && argv[1] == "-a") {
        flags |= O_APPEND;
    } else {
        flags |= O_TRUNC;
    }

    mode = S_IRUSR | S_IWUSR;
    if ((fd = open(argv[argc-1], flags, mode)) == -1)
        exit(-1);

    while (1) {
        if ((n = read(STDIN_FILENO, buf, MAXSIZE)) == -1)
            exit(-1);

        if (n == 0)
            exit(0);

        if (write(fd, buf, n) == -1)
            exit(-1);
        if (write(STDOUT_FILENO, buf, n) == -1)
            exit(-1);
    }
}
