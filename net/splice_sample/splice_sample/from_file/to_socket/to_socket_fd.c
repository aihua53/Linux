#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<fcntl.h>
#define MAXLINE 4096

FILE *in_file;
off_t off_in = 0;

int abc(int argc, char** argv)
{
	int sockfd, n;
	struct sockaddr_in servaddr;
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("create socket error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6666);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
		printf("inet_pton error for %s\n", argv[1]);
		exit(0);
	}
	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
		printf("connect error: %s(errno: %d)\n", strerror(errno), errno);
		exit(0);
	}

	int result;
	int pipefd[2];
	int size = 5;
	result = pipe(pipefd);
	result = splice(fileno(in_file), &off_in, pipefd[1], NULL, size, SPLICE_F_MORE | SPLICE_F_MOVE);
	result = splice(pipefd[0], NULL, sockfd, 0, size, SPLICE_F_MORE | SPLICE_F_MOVE);

	close(sockfd);
	return 0;
}

int main(int argc, char** argv)
{
	int T = 123;
	if (argc != 3) {
		printf("usage: ./client toIP infile\n");
		exit(0);
	}
	in_file = fopen(argv[2], "rb");
	while (T--) {
		abc(argc, argv);
		sleep(2);
		//usleep(30000);
	}
	return 0;
}

