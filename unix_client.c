#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <signal.h> 
#define MAXLINE 80
 
char *client_path = "client-socket";
char *server_path = "server-socket";
 
int main() {
	struct  sockaddr_un cliun, serun;
	int len;
	char buf[100];
	int sockfd, n;
 
	if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0){
		perror("client socket error");
		exit(1);
	}
//    signal(SIGPIPE, SIG_IGN);	
    memset(&serun, 0, sizeof(serun));
    serun.sun_family = AF_UNIX;
	serun.sun_path[0] = 0;
    strcpy(serun.sun_path+1,server_path);
    if (connect(sockfd, (struct sockaddr *)&serun, sizeof(struct sockaddr_un)) < 0){
    	perror("connect error");
    	exit(1);
    }
    printf("please input send char:");
    while(fgets(buf, MAXLINE, stdin) != NULL) {  
         write(sockfd, buf, strlen(buf));
         n = read(sockfd, buf, MAXLINE);  
         if ( n <= 0 ) {  
            printf("the other side has been closed.\n");
            break;
         }else {  
            printf("received from server: %s \n",buf);
         }
         printf("please input send char:");
    }
    printf("end server  date"); 
    close(sockfd);
    return 0;
}
