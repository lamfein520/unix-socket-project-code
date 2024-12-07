#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <utils/Log.h>
#include <sys/epoll.h>

#define MAXFILE 65535  // 最大文件描述符
#define BUF_SIZE 8192  // 缓冲区大小
#define SOCKET_PATH "server-socket"

char *executeCMD(const char *cmd) {
    FILE *ptr = NULL;
    char buf[BUF_SIZE];
    char *result = NULL;
    size_t result_size = 0;

    if ((ptr = popen(cmd, "r")) == NULL) {
        perror("popen error");
        return strdup("Command execution failed");
    }

    while (fgets(buf, BUF_SIZE, ptr) != NULL) {
        size_t buf_len = strlen(buf);
        char *new_result = realloc(result, result_size + buf_len + 1);
        if (new_result == NULL) {
            free(result);
            pclose(ptr);
            perror("Memory allocation failed");
            return strdup("Memory allocation error");
        }
        result = new_result;
        strcpy(result + result_size, buf);
        result_size += buf_len;
    }

    pclose(ptr);
    return result ? result : strdup("Command returned no output");
}

int main() {
    struct sockaddr_un serun, cliun;
    int listenfd, connfd;
    char buf[BUF_SIZE];

    printf("Main rootServer running\n");

    // 创建 UNIX 套接字
    if ((listenfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket error");
        exit(EXIT_FAILURE);
    }

    // 初始化服务器地址结构
    memset(&serun, 0, sizeof(serun));
    serun.sun_family = AF_UNIX;
    serun.sun_path[0] = 0;  // 使用抽象套接字
    strcpy(serun.sun_path + 1, SOCKET_PATH);
    socklen_t addrlen_ = sizeof(serun.sun_family) + strlen(SOCKET_PATH) + 1;

    // 绑定套接字
    if (bind(listenfd, (struct sockaddr *)&serun, addrlen_) < 0) {
        perror("bind error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(listenfd, 20) < 0) {
        perror("listen error");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("Waiting for connections...\n");

    // 服务循环
    while (1) {
        socklen_t l = sizeof(struct sockaddr_un);
        if ((connfd = accept(listenfd, (struct sockaddr *)&cliun, &l)) < 0) {
            perror("accept error");
            continue;
        }

        int len = recv(connfd, buf, BUF_SIZE - 1, 0);
        if (len > 0) {
            buf[len] = '\0';
            printf("Received command: %s\n", buf);

            char *result = executeCMD(buf);
            if (send(connfd, result, strlen(result), 0) < 0) {
                perror("send error");
            }
            free(result);
        } else {
            perror("recv error");
        }

        close(connfd);
    }

    close(listenfd);
    return 0;
}

