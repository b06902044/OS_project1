#define CHILD 1
#define _GNU_SOURCE
#include "control.h"
#include <sched.h>
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>


void set_aff(int pid, int core){
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(core, &mask);
    if(sched_setaffinity(pid, sizeof(mask), &mask) < 0){
        fprintf(stderr, "core = %d pid = %d set affinity fail\n", core, pid);
    } 
    else{
        //fprintf(stderr, "core = %d pid = %d set affinity success\n", core, pid);
    }
    return;
}

int create_process(process p){
    int pid = fork();
    if(pid == 0){
        //fprintf(stderr, "child pid = %d\n", getpid());
        unsigned long s1, s2, e1, e2;
        syscall(334, &s1, &s2);
        for(int i = 1; i <= p.exe; i++){
            volatile unsigned long j;
	        for (j = 0; j < 1000000UL; j++);
            //if(i % 100 == 0)
                //fprintf(stderr, "name = %s: %d / %d pri = %d\n", p.name, i, p.exe, sched_getscheduler(getpid()));
        }
        syscall(334, &e1, &e2);
        char buf[100];
        sprintf(buf, "[Project1] %d %lu.%09lu %lu.%09lu\n", getpid(), s1, s2, e1, e2);
        //fprintf(stderr, "%s\n", buf);
        syscall(333, buf);
        exit(0);
    }
    set_aff(pid, 1);
    return pid;
}

void block_process(int pid){
    struct sched_param param;
    param.sched_priority = 0;
    //fprintf(stderr, "min = %d\n", param.sched_priority);
    if(sched_setscheduler(pid, SCHED_IDLE, &param) < 0){
        fprintf(stderr, "pid = %d set scheduler idle fail\n", pid);
    }
    //fprintf(stderr, "pid = %d set low pri to %d\n", pid ,sched_getscheduler(pid));
    return;
}

void wake_process(int pid){
    struct sched_param param;
    param.sched_priority = 0;
    //fprintf(stderr, "max = %d\n", param.sched_priority);
    if(sched_setscheduler(pid, SCHED_OTHER, &param) < 0){
        fprintf(stderr, "pid = %d set scheduler other fail\n", pid);
    }
    //fprintf(stderr, "pid = %d set high pri to %d\n", pid ,sched_getscheduler(pid));
    return;
}
