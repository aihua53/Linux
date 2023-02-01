#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<linux/un.h>

int main()
{
	int fd;
	int r;
	char buf[100000];
	//1.建立socket
	fd = socket(AF_UNIX, SOCK_DGRAM, 0);  //AF_FILE 等同//AF_UNIX
	if (fd == -1) {
		printf("socket error:%m\n");
		exit(-1);
	}

	//2.构造本地文件地址
	struct sockaddr_un addr = {0};
	addr.sun_family = AF_UNIX; //必须跟socket的地址族一致
	memcpy(addr.sun_path, "my.sock", strlen("my.sock"));
	
	//3.把socket绑定在地址上
	r = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
	if (r == -1) {
		printf("bind error:%m\n");
		exit(-1);
	}

	//4.接收数据
	bzero(buf , sizeof(buf));
	r = read(fd, buf, sizeof(buf));
	buf[r] = 0;
	printf("%s\n", buf);

	//5.关闭
	close(fd);

	//6.删除socket文件
	unlink("my.sock");

	//socket文件不会自动删除，需要在程序结尾去删除该文件，否则，再次运行//A程序出错
	return 0;
}
