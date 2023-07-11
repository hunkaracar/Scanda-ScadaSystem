#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <time.h>
#include <errno.h>
//#include </usr/include/nmap.h>

#define MAX_PACKET_SIZE 65535
#define TIMEOUT 24 // Connection timeout (in seconds)

void scanBeginV2(const char* target_ip, int target_port) {

    printf("\nTarget Scanning...\n");
    printf("--------------------------------------------------------\n\n");
    printf("Github: https://github.com/hunkaracar\n");
    printf("The specific port scan [%d] in scada systems\n",target_port);
    printf("Initialize scan\n");

    // Get current time
    time_t now;
    time(&now);

    // Convert to struct tm
    struct tm* local_time = localtime(&now);

    // Hours info
    int hour = local_time->tm_hour;
    int minute = local_time->tm_min;
    int second = local_time->tm_sec;

    // Day info
    int day = local_time->tm_mday;
    int month = local_time->tm_mon + 1; // We add +1 because the month is in the range 0-11
    int year = local_time->tm_year + 1900; // Since the year is calculated from 1900, we add +1900

    // Hour and day print screen
    printf("at hours: %02d:%02d:%02d\n", hour, minute, second);
    printf("at day: %02d/%02d/%d\n", day, month, year);

    printf("Target Ip [%s] Attempt\n\n", target_ip);
    printf("--------------------------------------------------------------\n\n");
    printf("Initialize Scan Specific Port Waiting...\n\n");
    sleep(5);
}
/*
int checkHostStatuss(const char* targetIp) {
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

void scanPort(const char* targetIp, int port) {
	/*
	 if (!checkHostStatuss(targetIp)) {
        printf("\nDiscovery Host is down: %s\n", targetIp);
        return;
    }
     */
    const char* protocol = ""; // Protokol adı

    // Protokol adını belirleme
    const char* getProtocol(int port) {
    const char* protocol = ""; // Protokol adı

     switch (port) {
		 
		case 21:
			protocol = "FTP";
			break;
        case 22:
            protocol = "SSH";
            break;
        case 23:
            protocol = "Telnet";
            break;
        case 25:
            protocol = "SMTP";
            break;
        case 53:
            protocol = "DNS";
            break;
        case 69:
            protocol = "TFTP";
            break;
        case 80:
            protocol = "HTTP";
            break;
        case 88:
            protocol = "Kerberos";
            break;
        case 110:
            protocol = "POP3";
            break;
        case 123:
            protocol = "NTP";
            break;
        case 143:
            protocol = "IMAP";
            break;
        case 179:
            protocol = "BGP";
            break;
        case 194:
            protocol = "IRC";
            break;
        case 389:
            protocol = "LDAP";
            break;
        case 443:
            protocol = "HTTPS";
            break;
        case 465:
            protocol = "SMTPS";
            break;
        case 514:
            protocol = "RSH";
            break;
        case 520:
            protocol = "RIP";
            break;
        case 636:
            protocol = "LDAPS";
            break;
        case 993:
            protocol = "IMAPS";
            break;
        case 995:
            protocol = "POP3S";
            break;
        case 20000:
        case 20001:
			protocol = "DNP3";
			break;
        case 1023:
        case 1024:
        case 1025:
        case 1026:
        case 1080:
        case 1194:
        case 1234:
        case 1433:
        case 1521:
        case 1701:
        case 1723:
        case 1812:
        case 1813:
        case 1883:
        case 2222:
        case 2427:
        case 2428:
        case 3000:
        case 3030:
        case 3128:
        case 3306:
        case 3389:
        case 3690:
        case 4000:
        case 4040:
        case 4321:
        case 4567:
        case 47808:
        case 47809:
        case 4840:
        case 5000:
        case 5001:
        case 5020:
        case 5432:
        case 5631:
        case 5632:
        case 5900:
        case 6000:
        case 6001:
        case 62541:
        case 6379:
        case 6666:
        case 6667:
        case 8000:
        case 8080:
        case 8081:
        case 8082:
        case 8087:
        case 8443:
        case 8888:
        case 9000:
        case 9001:
        case 9100:
        case 9200:
        case 9500:
        case 9600:
        case 9876:
        case 9999:
        case 41820:
        case 44818:
            protocol = "Reserved";
            break;
            
        default:
			protocol = "UNKNOWN";
			break;
    }

    return protocol;
}


    // Create socket
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        printf("Discovery (1) Host Down [%s]\n\n",targetIp);
        exit(EXIT_FAILURE);
    }
    

    // Set IP address and port number
    struct sockaddr_in targetAddr;
    targetAddr.sin_family = AF_INET;
    targetAddr.sin_addr.s_addr = inet_addr(targetIp);
    targetAddr.sin_port = htons(port);
	
	printf("Discovery (1) Host Up [%s]\n\n",targetIp);
	sleep(5);
	
    // Connect to the target
    if (connect(sockfd, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) < 0) {
        if (errno == ETIMEDOUT) {
            printf("Connection timed out: Port %d [%s]\n", port, protocol);
        } 
        
        else if (errno == ECONNREFUSED) {
			
            printf("Discovery Port %d is closed\n", port);
        }
        
        else if (errno == EHOSTUNREACH) {
            printf("Discovery Port %d is filtered\n", port);
        }
        
        else {
            printf("Discovery Port %d error: %s\n", port, strerror(errno));
        }
    }
     
    else {
		
        printf("Discovery Port %d is OPEN\n\n", port);
    }

    // Close the socket
    close(sockfd);
    printf("\n____________________________________________________________________\n");
    printf("--[[Scan performed successfully]]--\n\n");
    
}
