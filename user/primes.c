//
// Created by tuyu on 2022/7/8.
//

#include "kernel/types.h"
#include "user/user.h"


// the first process feed the number 2 through 35 into the pipeline
// Once the first process reaches 35, it should wait until the entire pipeline terminates, including all children, grandchildren
// Thus the main primes process should only exit after all the output has been printed, and after all the other processes have exited
// Hint: read returns zero when the write 32-bit(4-byte) int to the pipes, rather than using formatted ASCII I/O
// You Should create the processes in the pipeline only as they are needed

void
process(int p[]){
    int prime;
    close(p[1]);
    if (read(p[0], &prime, 4) > 0) {
        int fd[2];
        pipe(fd);
        fprintf(1, "prime %d\n", prime);
        if (fork() > 0) {
            close(fd[0]);
            int i;
            while (read(p[0], &i, 4) > 0) {
                if (i % prime != 0) {
                    write(fd[1], &i, 4);
                }
            }
            close(fd[1]);
        } else {
            close(p[0]);
            process(fd);
        }
    }
}

int
main()
{
    int fd[2];
    pipe(fd);
    int pid = fork();

    if(pid > 0){
        close(fd[0]);
        fprintf(1, "prime 2\n");
        for (int i = 3; i < 35; i++) {
            if (i % 2 != 0) {
                write(fd[1], &i, 4);
            }
        }
        close(fd[1]);
        wait(0);
    } else {
        process(fd);
    }
    exit(0);
}
