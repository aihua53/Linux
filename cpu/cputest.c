/*
 * 
 * memtester version 1
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <errno.h>
// #include <pthread.h>

#define __version__ "1.0"
#define EXIT_FAIL_NONSTARTER    0x01

static void usage(char *p){
    printf("version:");
    printf(__version__);
    printf("\nUsage: %s [interval(us)]\n", p);
    printf("example: cputest 10\n");
    exit(EXIT_FAIL_NONSTARTER);
}

void func(int i){
    int count;
    while(1){
        // printf("hello\n");
        if(count++ > 65535){
            count = 0;
        }
        usleep(i);
    }
}

int main(int argc, char** argv){
    int i;
    
    if (argc == 1) {
        usage(argv[0]);
        return 0;
    }

    

    i = atoi(argv[1]);

    if(argc>=3){
        int k = atoi(argv[2]);
        while(k>1){
            pid_t pid = fork();
            if(pid == 0){
                func(i);
            }
            k--;
        }
    }

    func(i);
    exit(0);
}
