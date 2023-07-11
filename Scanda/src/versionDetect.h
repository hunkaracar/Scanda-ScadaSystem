#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define BUFFER_SIZE 1024
#define TIMEOUT_SECONDS 27

void scanBeginV5(const char* targetIp) {
	
    printf("\nTarget Scanning...\n");
    printf("--------------------------------------------------------\n\n");
    printf("Github: https://github.com/hunkaracar\n");
    printf("It scans open ports in Scada systems and shows the version information of the services they use.\n");
    printf("Initializing scan\n");

    // Get current time
    time_t now;
    time(&now);

    // Convert to struct tm
    struct tm* localTime = localtime(&now);

    // Time info
    int hour = localTime->tm_hour;
    int minute = localTime->tm_min;
    int second = localTime->tm_sec;

    // Date info
    int day = localTime->tm_mday;
    int month = localTime->tm_mon + 1;
    int year = localTime->tm_year + 1900;

    // Print time and date
    printf("at hours: %02d:%02d:%02d\n", hour, minute, second);
    printf("at day: %02d/%02d/%d\n", day, month, year);

    printf("Target IP [%s] Attempt\n\n", targetIp);
    printf("--------------------------------------------------------------\n\n");
    printf("Initializing Scan and Get Version Information Waiting...\n\n");
    sleep(4);
}
/*
int checkHostStatussss(const char* targetIp) {
    char command[100];
	sprintf(command, "ping -c 1 -W 1 %s > /dev/null 2>&1", targetIp);
	int status = system(command);

    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        return 1; // Host is up
    } else {
        return 0; // Host is down
    }
}
 */

char* read_response(int sockfd) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    ssize_t bytesRead = 0;
    ssize_t totalBytesRead = 0;
    while (totalBytesRead < BUFFER_SIZE - 1) {
        bytesRead = read(sockfd, buffer + totalBytesRead, sizeof(buffer) - 1 - totalBytesRead);

        if (bytesRead < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // Timeout occurred, break the loop
                break;
            } else {
                perror("Could not read response from server!!!");
                exit(1);
            }
        } else if (bytesRead == 0) {
            // No more data to read, break the loop
            break;
        }

        totalBytesRead += bytesRead;
    }

    buffer[totalBytesRead] = '\0';
    printf("Version:[%s]\n\n", buffer);

    return strdup(buffer);
}

void get_Version(char* targetip) {
	/*
	 if (!checkHostStatussss(targetip)) {
        printf("\nDiscovery Host is down: %s\n\n", targetip);
        return;
    }
     */
    int ports[] = {
        21, 22, 23, 25, 53, 69, 80, 88, 110, 111, 123, 143, 179, 194, 389, 443, 465,
        502, 514, 520, 636, 993, 995, 102, 1023, 1024, 1025, 1026, 1080, 1194, 1234, 1433, 1521, 1701, 1723, 1812,
        1813, 1883, 2222, 2427, 2428, 3000, 3030, 3128, 3306, 3389, 3690, 4000, 4040, 4321, 4567, 47808, 47809,
        4840, 5000, 5001, 5020, 5432, 5631, 5632, 5900, 6000, 6001, 62541, 6379, 6666, 6667, 8000, 8080, 8081, 8082, 8087,
        8443, 8888, 9000, 9001, 9100, 9200, 9500, 9600, 9876, 9999, 41820, 44818, 20000, 20001
    };

    int num_ports = sizeof(ports) / sizeof(ports[0]);
    int i = 0;

    for (i = 0; i < num_ports; i++) {
        int sockfd;
        struct sockaddr_in server_addr;

        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation failed!");
            exit(1);
        }

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(ports[i]);

        if (inet_pton(AF_INET, targetip, &(server_addr.sin_addr)) <= 0) {
            perror("Invalid address/Address not supported");
            exit(1);
        }

        // Set socket timeout
        struct timeval timeout;
        timeout.tv_sec = TIMEOUT_SECONDS;
        timeout.tv_usec = 0;
        setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));

        if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            if (errno == ECONNREFUSED) {
				printf("");
                //printf("Discovery port closed %d [%s]\n", ports[i], targetip);
            } else {
                perror("Connection failed");
                close(sockfd);
                exit(1);
            }
        } else {
            printf("Discovery port OPEN %d [%s]\n", ports[i], targetip);
            sleep(1);

            char* response = read_response(sockfd);

            // Burada response'dan versiyon bilgisini analiz edebilirsiniz.
            // Örneğin, SSH için "SSH-2.0" banner'ını kontrol edebilirsiniz.

            free(response);
            close(sockfd);
            
        }
       
    }
     printf("\n____________________________________________________________________\n");
	 printf("--[[Scan performed successfully]]--\n\n");
}
