#include <unistd.h>//包含write，，write等
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>//包含open函数
#include <stdio.h> //标准输入输出，包含printf

#define L 10*1024
int main()
{
        int fd,size;        //fd为文件描述符，size为读到的数据大小
        // char s[]="linux programmer!\n ",buffer[80];
        char s[L];
        memset(s,'c',sizeof(s));
        s[L-1] = '\n';
        // fd=open("/data/io.txt",O_WRONLY|O_CREAT|O_APPEND,0666); //打开文件，如没有就创建文件
        fd=open("/data/io.txt",O_DIRECT|O_WRONLY|O_CREAT|O_APPEND,0666);
        while(1){
                // fd=open("/data/io.txt",O_DIRECT|O_WRONLY|O_CREAT|O_APPEND,0666);
                // fd=open("/data/io.txt",O_WRONLY|O_CREAT|O_APPEND,0666);
                write(fd,s,sizeof(s));  
                usleep(2000);
                // close(fd);
        }
        close(fd);                                      //关闭文件

 
 
 
}