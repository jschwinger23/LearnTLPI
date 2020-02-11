#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define SIZE 1024

int main(int argc, char *argv[]) {
    int from_fd, to_fd;
    size_t n;
    char buf[SIZE];


    if ((from_fd = open(argv[1], O_RDONLY)) == -1)
        exit(-1);

    if ((to_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
        exit(-1);


    while (1) {
        if ((n = read(from_fd, buf, SIZE)) == -1)
            exit(-1);

        if (n == 0)
            break;

        if ((n = write(to_fd, buf, n)) != n)
            exit(-1);
    }
}
