#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUF_SIZE 1024

void redirectHTTP(const char* target_ip) {
    printf("\nRedirect Scada Http Url => http://%s\n\n\n", target_ip);
}

void getHTTPVersion(const char* target_ip) {
	printf("\nScada System HTTP on 80 port information showing...\n");
	printf("-------------------------------------------------------------------------\n\n");
	sleep(3);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    if (inet_pton(AF_INET, target_ip, &(server.sin_addr)) <= 0) {
        perror("inet_pton");
        return;
    }

    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection Error.\n");
        return;
    }

    char request[MAX_BUF_SIZE];
    sprintf(request, "GET / HTTP/1.0\r\n\r\n");
    if (send(sock, request, strlen(request), 0) < 0) {
        perror("send");
        return;
    }

    char response[MAX_BUF_SIZE];
    if (recv(sock, response, MAX_BUF_SIZE, 0) < 0) {
        perror("recv");
        return;
    }

    char* serverHeader = strstr(response, "Server:");
    if (serverHeader != NULL) {
        char serverInfo[MAX_BUF_SIZE];
        sscanf(serverHeader, "Server: %[^\r\n]", serverInfo);
        printf("\nHTTP Version Server Info: %s\n\n", serverInfo);
        redirectHTTP(target_ip);
    } else {
        printf("\nServer Info not found.\n\n");
    }

    close(sock);
}
