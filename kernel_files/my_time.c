#include <linux/module.h>
#include <linux/time.h>
#include <linux/init.h>
#include <linux/linkage.h>
#include <linux/kernel.h>

asmlinkage int sys_my_time(unsigned long *a, unsigned long *b){
	struct timespec now;
	getnstimeofday(&now);
	*a = now.tv_sec;
	*b = now.tv_nsec;
    return 1;
}
