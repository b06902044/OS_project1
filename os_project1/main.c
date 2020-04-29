#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sched.h>
#include <errno.h>
#include <unistd.h>

typedef struct Process{
    char name[50];
    int rea, exe;
    int pid;
}process;

int main(int argc, char **argv){
    char cmd[20];
    int N;
    scanf("%s%d", cmd, &N);

    process *pro = (process *)malloc(N * sizeof(process));
    for(int i = 0; i < N; i++){
        scanf("%s %d %d", pro[i].name, &pro[i].rea, &pro[i].exe);
        pro[i].pid = -1;
    }

    schedule(pro, N, cmd);
    return 0; 
}
