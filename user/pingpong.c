#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv []) {
    char data[1] = "a";
    int p_p[2], c_p[2];
    int pid = getpid();

    pipe(p_p);
    pipe(c_p);
    if (fork()) {
        write(p_p[1], data, 1);
        read(c_p[0], data, 1);
        printf("%d: received pong\n", pid);
    } else {
        pid = getpid();
        read(p_p[0], data, 1);
        printf("%d: received ping\n", pid);
        write(c_p[1], data, 1);
    }
    exit(0);
}