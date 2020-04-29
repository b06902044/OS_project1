#ifndef CONTROL_H
#define CONTROL_H

typedef struct Process{
    char name[50];
    int rea, exe;
    int pid;
}process;

void set_aff(int pid, int core);

int create_process(process p);

void block_process(int pid);

void wake_process(int pid);

#endif

