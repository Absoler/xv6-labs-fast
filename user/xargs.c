#include "kernel/types.h"
#include "user/user.h"

#define ARG_MAX_NUM 32
#define ARG_MAX_LEN 32
#define MAX_BUF 512
/*
 *  standard input > xargs cmd arg1 arg2
 */
int main(int argc, char *argv [])
{
    char new_args[ARG_MAX_NUM][ARG_MAX_LEN];
    char buf[MAX_BUF + 1];
    char *args[ARG_MAX_NUM];
    int n;
    for (int i = 1; i < argc; i++) {
        args[i-1] = argv[i];
    }

    int n_newarg = 0, col = 0;
    int in_ws = 1;  // in white space status
    while ((n = read(0, buf, MAX_BUF)) > 0) {
        for (int i = 0; i < n; i++) {
            if (buf[i] == ' ' || buf[i] == '\t' || buf[i] == '\n') {
                if (in_ws == 0) {
                    new_args[n_newarg][col] = 0;
                    n_newarg++;
                    col = 0;
                    in_ws = 1;
                }
            }
            if (buf[i] == '\n') {
                int j;
                for (j = 0; j < n_newarg; j++) {
                    args[argc - 1 + j] = new_args[j];
                }
                args[argc - 1 + j] = 0;
                if (fork()) {
                    // parent
                    int status;
                    wait(&status);
                } else {
                    // for (int i = 0; args[i] != 0; i++) {
                    //     printf(" %s", args[i]);
                    // }
                    printf("\n");
                    exec(args[0], args);
                    exit(0);
                }

                // reset
                n_newarg = 0;
                col = 0;
            } else {
                new_args[n_newarg][col] = buf[i];
                col++;
                in_ws = 0;
            }
        }
    }
    exit(0);
}