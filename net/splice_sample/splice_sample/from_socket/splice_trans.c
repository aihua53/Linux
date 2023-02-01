#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>

#define MAXLINE 4096

int to_socket(int argc, char** argv, int connfd)
{
	int sockfd, n;
	struct sockaddr_in servaddr;
	char buff[4096];
	if (argc != 2) {
		printf("usage: ./client <ipaddress>\n");
		exit(0);
	}
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6667);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf("inet_pton error for %s\n", argv[1]);
		exit(0);
	}
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	/*
	n = read(connfd, buff, MAXLINE);
	buff[n] ='\0';
	printf("recv msg from client: %s\n", buff);
	write(sockfd, buff, strlen(buff));
	*/

#define SPLICE_F_MOVE 1
	int pfd[2];
	pipe(pfd);
	int bs = splice(connfd, NULL, pfd[1], NULL, 4, SPLICE_F_MOVE);
	printf("bs = %d\n", bs);
	bs = splice(pfd[0], NULL, sockfd, NULL, bs, SPLICE_F_MOVE);
	printf("bs = %d\n", bs);

	close(sockfd);
	return 0;
}

FILE *f_out;
off_t off_out = 0;

int to_file(int argc, char **argv, int connfd)
{
#define SPLICE_F_MOVE 1
	int pfd[2];

	pipe(pfd);

	int bs = splice(connfd, NULL, pfd[1], NULL, 5, SPLICE_F_MOVE);
	printf("bs = %d\n", bs);
	bs = splice(pfd[0], NULL, fileno(f_out), &off_out, bs, SPLICE_F_MOVE);
	printf("bs = %d\n", bs);
	return 0;
}

int main(int argc, char** argv)
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buff[4096];
	int n;

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6666);
	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
		printf("bind socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	if (listen(listenfd, 10) == -1) {
		printf("listen socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	f_out = fopen("out", "wb");
	printf("======waiting for client's request======\n");
	while (1) {
		if ((connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1){
			printf("accept socket error: %s(errno: %d)", strerror(errno), errno);
			continue;
		}

//		n = read(connfd, buff, MAXLINE);
//		buff[n] ='\0';
//		printf("recv msg from client: %s\n", buff);

//		to_socket(argc, argv, connfd);
		to_file(argc, argv, connfd);
		close(connfd);
	}
	close(listenfd);
	return 0;
}

