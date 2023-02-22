#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int copyfile(char * src ,char * dest, int count, int file_name);

int main(int argc , char *argv[])
{
	int count = 1;
	int i = 0;
   if(argc <3)
    {
        return -1;
    }

    if (argc >= 4) {
    	for (; i < atoi(argv[3]); i++) {
			pid_t pid = fork();
			if(pid == 0)
				break;
    	}
    }
    if (argc >= 5) {
    	count = atoi(argv[4]);
    }
    copyfile(argv[1] , argv[2], count, i);
    return 0;
}


int copyfile(char * src ,char * dest, int count, int file_name)
{

    while(count != 0) {
    	count --;
    	int fdsrc = open(src ,O_RDONLY);//以只读方式打开文件
    if(fdsrc  < 0)
    {
        printf("open %s error !\n",src);  //注意 ： 用指针输出字符串的，
        return -1;
    }
 	char dest1[128] = {0};
 	snprintf(dest1, 128, "%s_%d",dest, file_name);
    int fddest = open(dest1 , O_RDWR|O_CREAT|O_APPEND, 0666); //注意，以任何"w"模式打开文件，若已经存在该文件，会先清空，然后再开始输出到该文件中去
    if(fddest < 0)
    {
        printf("open %s error dest!\n",dest1);
        return -1;
    }
    printf("open %s  dest!\n",dest1);
    int byte_count;
    char buf[4096];
    while((byte_count=read(fdsrc, buf, 4096)) != 0) //逐个字符去读取文件内容，
    {
        write(fddest, buf, byte_count);
    }
    close(fdsrc);
    //fsync(fddest);
    close(fddest);


     }

    return 0;
}