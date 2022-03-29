#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


#define BUF_SIZE 1024
#define STDOUT_FILENO 1
int fd = STDOUT_FILENO;

int pid = 0;
int max = 0;
int min = 0;
int avg = 0;


void show_help() {
	printf("getmem -p pid [-t interval] \n"
           "default interval is 5 sec\n "         );
}

int dumpsys_meminfo(char *cmd, char *buf, int length){
    FILE *fp = popen(cmd, "r");
    if(fp== NULL){
        printf("exec command failed\n");
        return -1;
    }

    fread(buf, 1, length, fp);
    // printf("%s",buf);
    // printf("*************\n");
    pclose(fp);
    return 0;
}

int parse(char *buf){
    int pss;
    char str[20];
    char *buf2 = strstr(buf, "PSS:");
    sscanf(buf2,"%*s%s",str);
    pss = atoi(str)/1024;
    dprintf(fd, "%d \n", pss);

    return pss;
}

void getNameByPid(pid_t pid, char *task_name) {
    char proc_pid_path[BUF_SIZE];
    char buf[BUF_SIZE];

    sprintf(proc_pid_path, "/proc/%d/status", pid);
    FILE* fp = fopen(proc_pid_path, "r");
    if(NULL != fp){
        if( fgets(buf, BUF_SIZE-1, fp)== NULL ){
            fclose(fp);
        }
        fclose(fp);
        sscanf(buf, "%*s %s", task_name);
    }
}

void stop(int s){
    char task_name[50];
    getNameByPid(pid,task_name);

    dprintf(fd, "\n");
    dprintf(fd, "summary\n");
    dprintf(fd, "pid: %d\n", pid);
    dprintf(fd, "task_name: %s\n", task_name);
    dprintf(fd, "pss_max: %dMB\n", max);
    dprintf(fd, "pss_min: %dMB\n", min);
    dprintf(fd, "pss_avg: %dMB\n", avg);
    exit(0);
}

int main(int argc, char *argv[]){
    int ch;
    int t = 5; //5s
    char cmd[50] = {0};
    char buf[2000] = {0};

    while((ch = getopt(argc, argv, "hp:t:")) != -1){
        switch (ch)
        {
        case 'h':
            show_help();
            return 0;
        case 'p':
            pid = atoi(optarg);
            sprintf(cmd,"dumpsys meminfo -s %d", pid);
            break;
        case 't':
            t = atoi(optarg);
            break;
        default:
            break;
        }

    }

    if (pid == 0) {
        printf("Please Enter the pid !! \n");
        return -1;
    }

    signal(SIGINT, stop);

    while(1){
        int value = 0;
        dumpsys_meminfo(cmd, buf, sizeof(buf));
        value = parse(buf);

        //calcute max, max, avg
        if(max == 0){
            max = min = avg = value;
        }
        if(value > max){
            max = value;
        }else if(value < min){
            min = value;
        }
        avg = (value + avg)/2;

        sleep(t);
    }

    return 0;

}