#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv [])
{
    int num = 0;

    if (argc < 2) {
        fprintf(2, "Usage: sleep NUM ticks\n");
        exit(1);
    }

    num = atoi(argv[1]);
    sleep(num);
    exit(0);
}