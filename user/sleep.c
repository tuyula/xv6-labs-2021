//
// Created by tuyu on 2022/7/7.
//

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    if(argc < 2){
        fprintf(2, "Usage: sleep second\n");
        exit(1);
    }

    int second = atoi(argv[1]);
    sleep(second);
    exit(0);
}

