#include "kernel/types.h"
#include "user/user.h"

int
main (int argc, char *argv [])
{
    int f_p[2], c_p[2];
    int buffer[64];
    int cnt = 34;
    
    buffer[0] = cnt;
    for (int i = 1; i <= cnt; i++) {
        buffer[i] = i + 1;
    }
    
    pipe(f_p);
    pipe(c_p);
    while (cnt > 0) {
        int prime;
        int p;
        if (fork()) {
            // parent
            int status;
            printf("prime %d\n", buffer[1]);
            // for (int i = 0; i < cnt; i++) { printf(" %d", buffer[i+1]);}
            // printf("\n");
            write(f_p[1], buffer, (cnt + 1) * sizeof(int));
            wait(&status);
            read(c_p[0], (void *)&buffer, sizeof(int));
            cnt = buffer[0];
            if (cnt > 0) {
                read(c_p[0], (void *)&buffer[1], buffer[0] * sizeof(int));
            }
            // for (int i = 0; i < cnt; i++) { printf(" %d", buffer[i+1]);}
            // printf("\n");
        } else {
            // child
            read(f_p[0], (void *)buffer, sizeof(int));
            read(f_p[0], (void *)&buffer[1], buffer[0] * sizeof(int));
            cnt = buffer[0];
            prime = buffer[1];
            for (int i = 1; i <= cnt; i++) {
                if (buffer[i] % prime == 0) {
                    buffer[i] = -1;
                }
            }
            p = 0;
            for (int i = 1; i <= cnt; i++) {
                if (buffer[i] != -1) {
                    buffer[++p] = buffer[i];
                }
            }
            buffer[0] = p;
            write(c_p[1], buffer, (p + 1)*sizeof(int));
            exit(0);
        }
    }
    exit(0);
}