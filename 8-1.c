#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void catfd(int fd);

int main(int argc, char *argv[])
{
    int fd;

    if (argc == 1) {    /* read from stdin */
        catfd(0);
    } else {
        while (--argc >= 1) {
            if ((fd = open(*++argv, O_RDONLY, 0)) != -1) {
                catfd(fd);
            } else {
                fprintf(stderr, "Error: could not open %s\n", *argv);
            }
        }
    }
    return 0;
}

void catfd(int fd)
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        write(1, buf, n);
    }
}
