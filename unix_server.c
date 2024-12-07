#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/epoll.h>
#include <sys/un.h>
int main()
{
    char *socket_path = "server-socket";
    struct sockaddr_un serun, cliun;
    socklen_t cliun_len;
    int listenfd, connfd, size;
    char buf[80];
    int i, n;
    if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(1);
    }
    //unlink(socket_path);
    memset(&serun, 0, sizeof(serun));
    serun.sun_family = AF_UNIX;
    serun.sun_path[0] = 0;
    strcpy(serun.sun_path+1,socket_path);
    socklen_t addrlen_ = sizeof(serun.sun_family) + strlen(socket_path) + 1;
    int ret = bind(listenfd, (struct sockaddr*)&serun,addrlen_);
    if(ret == -1)
    {
        perror("bind");
        exit(0);
    }
    // 3. 监听
    ret = listen(listenfd, 20);
    if(ret == -1)
    {
        perror("listen");
        exit(0);
    }

   
    while(1)
    {
	printf("wait connect...\n");
	socklen_t l =   sizeof(struct sockaddr_un);
        int connfd = accept(listenfd, (struct sockaddr *)&cliun, &l);
        if(connfd == -1)
        {
            perror("accept");
            exit(-1);
        }
        printf("a new client connected! ");
    
        int count = read(connfd, buf, sizeof(buf));
        if(count == 0)//客户端关闭了连接
        {
            printf("客户端关闭了连接。。。。\n");
          
        }
        else
        {
            if(count == -1)
            {
                perror("read");
                exit(-1);
            }
            else
            {
                //正常通信
                printf("client say: %s\n" ,buf);
		write(connfd,"received ok",sizeof("received ok"));
            }
        }
    }
    close(listenfd);
    return 0;
}
