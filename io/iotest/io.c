#include <unistd.h>//包含write，，write等
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>//包含open函数
#include <stdio.h> //标准输入输出，包含printf

#define L 10*1024
int main()
{
        /****** write *******/
        int fd,size;
        char s[L];
        memset(s,'c',sizeof(s));
        s[L-1] = '\n';
        fd=open("/data/io.txt",O_WRONLY|O_CREAT|O_APPEND,0666);
        fd=open("/data/io.txt",O_DIRECT|O_WRONLY|O_CREAT|O_APPEND,0666);
        while(1){
                write(fd,s,sizeof(s));  
                usleep(2000);
        }
        close(fd);

        /***** read *****/
        // int fd_r;
        // char buf[4096];
        // int byte_count;
        // fd_r = open("/data/test.txt",O_RDONLY);
        // byte_count = read(fd_r,buf,sizeof(buf));
        // close(fd_r);     

}