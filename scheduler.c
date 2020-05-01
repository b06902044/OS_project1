#define _GNU_SOURCE
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include "control.h"
#include "scheduler.h"
#define PARENT 0

static int run = -1, fin = 0, time = 0, last = 0;
int queue[30];
int front = 0, back = 0;

int top(void){
    return queue[front];
}
void pop(void){
    front = (front + 1) % 30;
    return;
}
void push(int pro){
    queue[back] = pro;
    back = (back + 1) % 30;
    return;
}
int empty(void){
    if(front == back)   return 1;
    else    return 0;
}

int fifo(process *pro, int N){
    if(run != -1)   return run;
    int next = -1;
    for(int i = 0; i < N; i++){
        if(pro[i].pid != -1 && pro[i].exe){
            if(next == -1 || pro[i].rea < pro[next].rea)
                next = i;
        }
    }
    return next;
}

int sjf(process *pro, int N){
    if(run != -1)   return run;
    int next = -1;
    for(int i = 0; i < N; i++){
        if(pro[i].pid != -1 && pro[i].exe){
            if (pro[i].pid == -1 || pro[i].exe == 0)
				continue;
            if(next == -1 || pro[i].exe < pro[next].exe)
                next = i;
        }
    }
    return next;
}

int psjf(process *pro, int N){
    int next = -1;
    for(int i = 0; i < N; i++){
        if(pro[i].pid != -1 && pro[i].exe){
            if(next == -1 || pro[i].exe < pro[next].exe)
                next = i;
        }
    }
    return next;
}

int rr(process *pro, int N){
    int left = (time - last) % 500;
    if(run != -1 && left)   return run;
    if(run != -1 && !left){
        if(empty()) return run;
        else{
            push(run);
            int next = top();
            pop();
            return next;
        }
    }
    if(run == -1){
        if(empty()) return -1;
        else{
            int next = top();
            pop();
            return next;
        }
    }
    return -1;
}


void schedule(process *pro, int N, char *cmd){
    int policy;
    if(cmd[0] == 'F')   policy = 1;
    else if(cmd[0] == 'S')  policy = 2;
    else if(cmd[0] == 'P') policy = 3;
    else if(cmd[0] == 'R') policy = 4;

    for(int i = 0; i < 30; i++) queue[i] = -1;

    set_aff(getpid(), 0);
    wake_process(getpid());
    
    while(1){
        //if(time % 100 == 0)
            //fprintf(stderr, "time = %d\n", time);
        if(run != -1 && pro[run].exe == 0){
            //fprintf(stderr, "%d finish at time %d\n", run, time);
            waitpid(pro[run].pid, NULL, 0);
            printf("%s %d\n", pro[run].name, pro[run].pid);
            fflush(stdout);
            run = -1;
            fin++;
            if(fin == N){
                break;
            }
        }

        for(int i = 0; i < N; i++){
            if(pro[i].pid == -1 && pro[i].rea == time){
                //fprintf(stderr, "%s ready at time %d\n", pro[i].name, time);
                pro[i].pid = create_process(pro[i]);
                push(i);
                //fprintf(stderr, "%s ready at time %d pid = %d pri = %d\n", pro[i].name, time, pro[i].pid, sched_getscheduler(pro[i].pid));
                //fprintf(stderr, "%s " ,pro[i].name);
                block_process(pro[i].pid);
                //fprintf(stderr, "pid = %d pri = %d\n", pro[i].pid, sched_getscheduler(pro[i].pid));
                //fprintf(stderr, "%s %d\n", pro[i].name, pro[i].pid);
            }
        }

        int next;
        switch(policy){
            case 1:
                next = fifo(pro, N);
                break;
            case 2:
                next = sjf(pro, N);
                break;
            case 3:
                next = psjf(pro, N);
                break;
            case 4:
                next = rr(pro, N);
                break;
        }
        //if(time % 100 == 0)
           // fprintf(stderr, "next = %d\n", next);
        
        if(next != -1 && next != run){
            //fprintf(stderr, "%s " ,pro[next].name);
            wake_process(pro[next].pid);
            //fprintf(stderr, "pid = %d pri = %d\n", pro[next].pid, sched_getscheduler(pro[next].pid));
            //if(run != -1){
                //fprintf(stderr, "%s " ,pro[run].name);
                block_process(pro[run].pid);
                //fprintf(stderr, "pid = %d pri = %d\n", pro[run].pid, sched_getscheduler(pro[run].pid));
            //}
            run = next;
            last = time;
        }

        volatile unsigned long i;		\
	    for (i = 0; i < 1000000UL; i++){

        }
        if(run != -1)   pro[run].exe--;
        time++;

    }
}

