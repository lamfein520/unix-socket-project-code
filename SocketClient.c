#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <string.h>

int main(int argc, char *argv[]) {
int client_sockfd;
int len;
int i;
char sendline[17824];
struct sockaddr_in remote_addr; //服务器端网络地址结构体
char buf[17824] = { '\0' }; //数据传送的缓冲区

for (i = 1; i < argc; i++) {
strcat(buf, argv[i]);
printf("%s\n", buf);
strcat(buf, " ");
}
strcat(buf, " 2>&1\0");
//printf("%s\n", buf);

memset(&remote_addr, 0, sizeof(remote_addr)); //数据初始化--清零
remote_addr.sin_family = AF_INET; //设置为IP通信
remote_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //服务器IP地址
remote_addr.sin_port = htons(40000); //服务器端口号

if((argc < 2 )||(strncmp(buf,"cct",3)==0)||(strncmp(buf,"su",2)==0)){
while(1){
fgets(sendline, 17824, stdin);
if(sendline[0]==10)
continue;
for(i=0;i<17824;i++){
if(sendline[i]==10){
sendline[i]=32;
break;
}
}
strcat(sendline," 2>&1\0");
//printf("sendline :%s\n", sendline);
if(strncmp(sendline,"exit",4)==0){
return 0;
}
if ((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
perror("socket");
return 1;
}
/*将套接字绑定到服务器的网络地址上*/
if (connect(client_sockfd, (struct sockaddr *) &remote_addr,
sizeof(struct sockaddr)) < 0) {
perror("connect");
return 1;
}

len = send(client_sockfd, sendline, strlen(sendline), 0);
len = recv(client_sockfd, buf, 17824, 0);
buf[len] = '\0';
if(strstr(buf,"not found")!=NULL){
write(2,buf,len);
}
else
printf("received:\n%s\n", buf);
close(client_sockfd);
}
return 0;
}
/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
if ((client_sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
perror("socket");
return 1;
}
/*将套接字绑定到服务器的网络地址上*/
if (connect(client_sockfd, (struct sockaddr *) &remote_addr,
sizeof(struct sockaddr)) < 0) {
perror("connect");
return 1;
}
len = send(client_sockfd, buf, strlen(buf), 0);
len = recv(client_sockfd, buf, 17824, 0);
buf[len] = '\0';
printf("received:\n%s\n", buf);
close(client_sockfd); //关闭套接字


return 0;
}
