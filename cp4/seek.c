#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAXSIZE 1024

int main(int argc, char *argv[]) {
    int fd, offset, count, n;
    char buf[MAXSIZE];
    char *format;

    if ((fd = open(argv[1], O_RDWR)) == -1)
        exit(-1);

    for (int i = 2; i < argc; i++) {

        if (argv[i][0] == 's') {
            offset = atoi(&argv[i][1]);
            lseek(fd, offset, SEEK_SET);

        } else if (argv[i][0] == 'w') {
            if (write(fd, &argv[i][1], strlen(&argv[i][1])) == -1)
                exit(-1);

        } else if (argv[i][0] == 'r' || argv[i][0] == 'R') {
            count = atoi(&argv[i][1]);
                if ((n = read(fd, buf, count)) == -1) {
                    exit(-1);
                } else if (n == 0) {
                    printf("EOF\n");
                    continue;
                }

            format = argv[i][0] == 'r' ? "%c" : "%x";
            for (int j = 0; j < n; j++) {
                printf(format, buf[j]);
            }
            printf("\n");
        }
    }
}
