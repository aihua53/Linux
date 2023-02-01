#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>

#include<sys/socket.h>
#include<linux/un.h>
#include<string.h>
#include<unistd.h>

int main(int argc, char **argv)
{
	int pipefd[2];
	int result;
	FILE *in_file;
	FILE *out_file;
	char buff[65537];

	if (argc != 3) {
		printf("usage: ./client infile outfile\n");
		exit(0);
	}
	result = pipe(pipefd);

	in_file = fopen(argv[1], "rb");
	out_file = fopen(argv[2], "wb");


	int fd;
	int r;
	struct sockaddr_un addr = {0};
	//1.建立socket
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);

	//2.连接到指定的地址
	addr.sun_family = AF_UNIX;
	memcpy(addr.sun_path, "my.sock", strlen("my.sock"));
	r = connect(fd, (struct sockaddr*)&addr, sizeof(addr));

	//3.发送数据
//	write(fd, "hello!", strlen("hello!"));



	off_t off_in = 0, off_out = 0;
	//int len = 300*1024*1024;
	int len = 10;
	printf("%d\n", clock());
	while (len > 0) {
		int size = 65536;
		if (len < size) size = len;
		len -= size;

		result = splice(fileno(in_file), &off_in, pipefd[1], NULL, size, SPLICE_F_MORE | SPLICE_F_MOVE);
		result = splice(pipefd[0], NULL, fd, 0, size, SPLICE_F_MORE | SPLICE_F_MOVE);

//		read(fileno(in_file), buff, size);
//		write(fd, buff, size);
	}
	printf("%d\n", clock());

	//4.关闭
	close(fd);

	close(pipefd[0]);
	close(pipefd[1]);
	fclose(in_file);
	fclose(out_file);

	return 0;
}

