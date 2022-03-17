#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <sched.h>



#define STDOUT_FILENO 1
int fd = STDOUT_FILENO;


using namespace std;

int main (int argc, char *argv[]) {
    // open file
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0,&mask);
    CPU_SET(2,&mask);
    if (sched_setaffinity(gettid(), sizeof(mask), &mask) == -1) {
        dprintf(fd, "sched_setaffinity error!\n");
    }

    FILE *f1 = fopen("/sys/class/kgsl/kgsl-3d0/gpu_busy_percentage", "r");
    if (f1 == NULL) return -1;
    // int fd1 = fileno(f1);
    FILE *f2 = fopen("/sys/class/kgsl/kgsl-3d0/devfreq/cur_freq", "r");
    if (f2 == NULL) return -1;
    // int fd2 = fileno(f2);
    FILE *f3 = fopen("/sys/class/kgsl/kgsl-3d0/devfreq/max_freq", "r");
    if (f3 == NULL) return -1;
    // int fd3 = fileno(f3);
    while(1) {
        char buf1[100] = {0};
        char buf2[100] = {0};
        char buf3[100] = {0};
        fgets(buf1, 100, f1);
        fgets(buf2, 100, f2);
        fgets(buf3, 100, f3);
        int percent;
        int cur;
        int max;
        sscanf(buf1,"%d",&percent);
        sscanf(buf2,"%d",&cur);
        sscanf(buf3,"%d",&max);
        cur = cur / 1000;
        max = max / 1000;
        int res = (cur * percent) / max;
        dprintf(fd, "%d\n", res);
        // dprintf(fd, "%d\n", cur);
        // dprintf(fd, "%d\n", max);
        // lseek(fd1, 0, SEEK_SET);
        // lseek(fd2, 0, SEEK_SET);
        // lseek(fd3, 0, SEEK_SET);
        fseek(f1,0,SEEK_SET);
        fseek(f2,0,SEEK_SET);
        fseek(f3,0,SEEK_SET);
        // usleep(1000000);
        sleep(1);
    }

    fclose(f1);
    // close(fd1);
    fclose(f2);
    // close(fd2);
    fclose(f3);
    // close(fd3);
    return 0;
}
