#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
// #include <string>
// #include <iostream>
// using namespace std;
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <fcntl.h>
// #include <unistd.h>

int testWrite();
int testSendfile(char *path);
int testSplice();

#define MAXLINE 4096
#define REPEAT_COUNT 10

int   sockfd, len;
struct sockaddr_in  servaddr;
FILE *fq;
int count = REPEAT_COUNT;


int main(int argc, char** argv){
    // int   sockfd, len;
    // struct sockaddr_in  servaddr;
    // FILE *fq;

    if( argc < 2){
        printf("usage: ./client <ipaddress>\n");
        return 0;
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);
        return 0;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6666);
    if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        printf("inet_pton error for %s\n",argv[1]);
        return 0;
    }

    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0){
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno);
        return 0;
    }
	 
    if( ( fq = fopen(argv[2],"rb") ) == NULL ){
        printf("File open fail.\n");
        close(sockfd);
        exit(1);
    }

    int opt = atoi(argv[3]);
    switch (opt)
    {
    case 1:
        printf("testWrite\n");
        testWrite();
        break;
    case 2:
        printf("testSendfile\n");
        testSendfile(argv[2]);
        break;
    case 3:
        printf("testSplice\n");
        testSplice();
        break;
    
    default:
        break;
    }


    printf("send done\n");
    close(sockfd);
    fclose(fq);
    return 0;
}

int testWrite(){
    char  buffer[MAXLINE];
    bzero(buffer,sizeof(buffer));
   do{
        while(!feof(fq)){
            len = fread(buffer, 1, sizeof(buffer), fq);
            if(len != write(sockfd, buffer, len)){
                printf("write.\n");
                break;
            }
        }
        count--;
        printf("count=%d\n",count);
        fseek(fq, 0, SEEK_SET);
   }while(count > 0);
   return 0;
}

int testSendfile(char *path){
    int file_fd = open(path,O_RDWR | O_CREAT,664);
    struct stat stat_buf;
    fstat(file_fd, &stat_buf);
    do{
        sendfile(sockfd, file_fd, NULL,stat_buf.st_size);
        count--;
        printf("count=%d\n",count);
    }while(count > 0);

    close(file_fd);
    return 0;
}

int testSplice(){
    int result;
	int pipefd[2];
	int size = 327680;
	result = pipe(pipefd);

	do{
        while(1){
            result = splice(fileno(fq), NULL, pipefd[1], NULL, size, SPLICE_F_MORE | SPLICE_F_MOVE);
            if(result == 0){
                break;
            }
            result = splice(pipefd[0], NULL, sockfd, 0, size, SPLICE_F_MORE | SPLICE_F_MOVE);
        }
        count--;
        printf("count=%d\n",count);
        fseek(fq, 0, SEEK_SET);
    }while(count > 0);


    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}