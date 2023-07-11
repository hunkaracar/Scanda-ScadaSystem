#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_PACKET_SIZE 65535
#define TIMEOUT 24 // Connection timeout (in seconds)

void scanBegin(const char* targetIp) {
    printf("\nTarget Scanning...\n");
    printf("--------------------------------------------------------\n\n");
    printf("Github: https://github.com/hunkaracar\n");
    printf("The most used 89 port scans in scada systems\n");
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
    printf("Initializing Scan Waiting...\n");
    sleep(2);
}
/*
int checkHostStatus(const char* targetIp) {
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

void scanSystem(const char* targetIp) {
	/*
    if (!checkHostStatus(targetIp)) {
        printf("\nDiscovery Host is down: %s\n", targetIp);
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

    const char* protocolPorts[] = {
        "FTP", "SSH", "Telnet", "SMTP", "DNS", "TFTP", "HTTP", "Kerberos", "POP3", "NFS", "NTP", "IMAP", "BGP", "IRC", "LDAP", "HTTPS",
        "SMTPS", "RSH", "RIP", "LDAPS", "IMAPS", "POP3S", "Reserved", "Reserved", "Reserved", "Reserved", "SOCKS", "OpenVPN", "Reserved",
        "MSSQL", "Oracle", "L2TP", "PPTP", "RADIUS", "RADIUS Accounting", "NFS", "Zookeeper", "X11", "Docker", "MS-SQL Monitor", "MS-SQL",
        "MediaWiki", "Redis", "Apache Tomcat", "MySQL", "Proxy Server", "RDP", "SVN", "Ruby on Rails", "Elasticsearch", "Home Assistant", "VNC",
        "Webmin", "Git", "MongoDB", "Oracle WebLogic", "Remote Desktop Gateway", "IKE", "IKE NAT", "IIS", "Jenkins", "Ethereum",
        "BitTorrent", "RTSP", "DHCP Server", "DHCP Client", "Modbus", "SNMP", "SCADA", "blackice-icecap", "blackice-alerts", "TCP", "SCADA","SCADA", "SCADA", "SCADA", "SCADA", "SCADA", "SCADA", "SCADA", "SCADA",
"MQTT (Message Queuing Telemetry Transport)", "MQTT (Message Queuing Telemetry Transport)",
"Ethernet/IP (Food and beverage industry)", "Ethernet/IP (Food and beverage industry)", "WirelessHART (Oil and gas industry)", "Profinet (Robotic systems and automation)",
"Modbus TCP/IP (Energy distribution and control)", "OPC UA (Unified Architecture)", "OPC UA (Unified Architecture)", "DeviceNet (Industrial automation systems)","DNP3","DNP3"
    };

    // Create socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set IP address and port number
    struct sockaddr_in targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_addr.s_addr = inet_addr(targetIp);

    printf("Discovery (1) Host Up [%s]\n\n", targetIp);
    sleep(4);

    int i;
    for (i = 0; i < sizeof(ports) / sizeof(*ports); i++) {
        targetAddr.sin_port = htons(ports[i]);
        // Wait 1 second before each connection attempt
        sleep(2);

        if (connect(sockfd, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) < 0) {
            if (errno == EINPROGRESS) {
                // Connection in progress
                struct timeval timeout;
                timeout.tv_sec = TIMEOUT;
                timeout.tv_usec = 0;
                fd_set fdSet;
                FD_ZERO(&fdSet);
                FD_SET(sockfd, &fdSet);
                int selectResult = select(sockfd + 1, NULL, &fdSet, NULL, &timeout);
                if (selectResult == 1) {
                    int socketError;
                    socklen_t socketErrorSize = sizeof(socketError);
                    getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &socketError, &socketErrorSize);
                    if (socketError == 0) {
                        printf("Discovery Port %d [%s] OPEN*\n", ports[i], protocolPorts[i]);
                    } 
                    
                    else {
                        printf("Port %d [%s] error: %s\n", ports[i], protocolPorts[i], strerror(socketError));
                    }
                } 
                
                else if (selectResult == 0) {
                    printf("Port %d [%s] Connection timed out \n", ports[i], protocolPorts[i]);
                } else {
                    perror("Select error");
                    exit(EXIT_FAILURE);
                }
            } 
            
            else if (errno == ECONNREFUSED) {
                printf("Discovery Port %d [%s] closed\n", ports[i], protocolPorts[i]);
            } 
            
            else if (errno == EHOSTUNREACH) {
                printf("Discovery Port %d [%s] filtered\n", ports[i], protocolPorts[i]);
            } 
            
            else {
                printf("Port %d [%s] error: %s\n", ports[i], protocolPorts[i], strerror(errno));
            }
        } 
        
        else {
            printf("Discovery Port %d [%s] OPEN*\n", ports[i], protocolPorts[i]);
            close(sockfd); // Close the connection
        }

        // Re-create connection socket
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation error");
            exit(EXIT_FAILURE);
        }

        // Set socket timeout
        struct timeval timeout;
        timeout.tv_sec = TIMEOUT;
        timeout.tv_usec = 0;

        if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
            perror("Setsockopt error");
            exit(EXIT_FAILURE);
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout, sizeof(timeout)) < 0) {
            perror("Setsockopt error");
            exit(EXIT_FAILURE);
        }
    }

    // Close the socket
    close(sockfd);
    printf("\n____________________________________________________________________\n");
    printf("--[[Scan performed successfully]]--\n\n");
}
