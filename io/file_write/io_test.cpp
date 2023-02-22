#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>




#define STDOUT_FILENO 1
int fd = STDOUT_FILENO;


using namespace std;

const struct option long_options[] = {
          { "help",        no_argument,       nullptr, 'h' }
        };

void show_help() {
	printf("getgpubusypercent [secs] \n"
           "default interval is 1 sec\n "         );
}


int main (int argc, char *argv[]) {
    int ret = -1;
    int fd = -1;
    int i = 1;
    char w_buf[20]="i like the mcu";
    while (1) {
        int option_index = 0;
        ret = getopt_long(argc, argv, "h", long_options, &option_index);
        if (ret < 0)
        break;
        switch(ret) {
            case 'h':
                show_help();
                return 0;
        }
    }

    if(argc > 1){
        i = atoi(argv[1]);
    }

    //default interval is 1 sec
    if(i<=0){
        i = 1;
    }

    // fd = open("/mesh_services/tony-test", O_CREAT | O_RDWR | O_SYNC,0777);
    fd = open("/mesh_services/tony-test", O_CREAT | O_RDWR,0777);
    if (fd == -1) {
        printf("the open the file is failure \n");
        return -1;
    }


    while(1) {
        ret=write(fd,w_buf,strlen(w_buf));
        if(ret == -1){
            printf("the write is failure\n");
            return -1;
        }
        // syncfs(fd);
        fdatasync(fd);
        // fsync(fd);
        sleep(i);
    }
    close(fd);

    return 0;
}
