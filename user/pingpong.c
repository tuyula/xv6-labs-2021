//
// Created by tuyu on 2022/7/7.
//

#include "kernel/types.h"
#include "user/user.h"

int
main()
{
    int pid;
    int parent_fd[2], child_fd[2];
    pipe(parent_fd);
    pipe(child_fd);
    pid = fork();
    char buf[1];

    if(pid == 0){
        close(parent_fd[1]);

        if (read(parent_fd[0], buf, 1)) {
            printf("%d: received ping\n", getpid());
        }
        close(child_fd[0]);
        write(child_fd[1], "A", 1);
        close(child_fd[1]);
    } else {
        close(parent_fd[0]);
        write(parent_fd[1], "A", 1);
        close(child_fd[1]);

        if (read(child_fd[0], buf, 1)) {
            printf("%d: received pong\n", getpid());
        }
        close(child_fd[0]);
    }

    exit(0);
}