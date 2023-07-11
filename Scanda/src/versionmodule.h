#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define MAX_PACKET_SIZE 65535
#define TIMEOUT 24 // Connection timeout (in seconds)



void scanBeginV3(const char* targetIp) {
	
    printf("\nTarget Scanning...\n");
    printf("--------------------------------------------------------\n\n");
    printf("Github: https://github.com/hunkaracar\n");
    printf("Detecting which system the Scada system is used for\n");
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
int checkHostStatusss(const char* targetIp) {
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

struct SystemInfo {
	int port;
	const char* name;
};



void scanSystemProtocol(const char* targetIp){
	/*
	if (!checkHostStatusss(targetIp)) {
        printf("\nDiscovery Host is down: %s\n\n", targetIp);
        return;
    }
     */
	struct SystemInfo system[] = {
		
		{1883, "MQTT (Message Queuing Telemetry Transport)"},
        {8883, "MQTT (Message Queuing Telemetry Transport)"},
        {44818, "Ethernet/IP (Food and beverage industry)"},
        {2222, "Ethernet/IP (Food and beverage industry)"},
        {102, "Profinet (Robotic systems and automation)"},
        {135, "Profinet (Industrial automation systems)"},
        {502, "Modbus TCP/IP (Energy distribution and control)"},
        {503, "Modbus TCP/IP (Energy distribution and control)"},
        {4840, "OPC UA (Unified Architecture)"},
        {62541, "OPC UA (Unified Architecture)"},
        //{44818, "DeviceNet (Industrial automation systems)"},
        {41820, "WirelessHART (Oil and gas industry)"},
	
	};
	
	int numSystem = sizeof(system) / sizeof(*system);
	
	//create socket
	int sockfd;
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("Socket creation error");
		printf("Discovery (1) Host Down [%s]",targetIp);
		exit(EXIT_FAILURE);
	}
	
	//Set IP address and port number
	struct sockaddr_in targetAddr;
	targetAddr.sin_family = AF_INET;
	targetAddr.sin_addr.s_addr = inet_addr(targetIp);
	 
	printf("Discovery (1) Host Up [%s]\n\n",targetIp);
	sleep(5);
	
	
    int i;
    for (i = 0; i < numSystem; i++) {
        targetAddr.sin_port = htons(system[i].port);
        sleep(1);

        // Connect to the target
        if (connect(sockfd, (struct sockaddr*)&targetAddr, sizeof(targetAddr)) < 0) {
            if (errno == ETIMEDOUT) {
                printf("Port %d [%s] Connection timed out\n", system[i].port, system[i].name);
            }
             
            else if (errno == ECONNREFUSED) {
                printf("Discovery Port %d [%s] Closed\n", system[i].port, system[i].name);
            }
            
            else if (errno == EHOSTUNREACH) {
                printf("Discovery Port %d [%s] Filtered\n", system[i].port, system[i].name);
            } 
            
            else {
                printf("Discovery Port %d [%s] Error: %s\n", system[i].port, system[i].name, strerror(errno));
            }
        }
         
        else {
			
            printf("\nDiscovery Port %d [%s] Open\n", system[i].port, system[i].name);
            printf("In this scada system, port [%d] is OPEN and [%s] service is running on this port\n\n",system[i].port, system[i].name);
            close(sockfd); // Close the connection
        }
        

        // Re-create connection socket
        if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            perror("Socket creation error");
            exit(EXIT_FAILURE);
        }

        sleep(1); // Pause for 1 second before attempting the next port
    }


    close(sockfd);
    printf("\n____________________________________________________________________\n");
    printf("--[[Scan performed successfully]]--\n\n");
}
