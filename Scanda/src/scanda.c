#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pcap.h>

#include "bruteForce.h"
#include "spesifikScan.h"
#include "scanmodule.h"
#include "versionmodule.h"
#include "portList.h"
#include "versionDetect.h"
#include "httpheader.h"
#include "directoryDisc.h"


void EndPoint() {
    char PurposeProgram[] = "Scanda v8.20 (c) 2023 by Hunkar Acar. This tool is a simple tool created to test the security of SCADA systems.\n\n";
    char Purpose2Program[] = "Scanda tool is a tool created to test the security of SCADA systems at intermediate and basic levels using various scenarios (c) v8.20.\n"
                             "Developer: Hunkar Acar. Being open-source allows for further development.";

    printf("\n\n%s", PurposeProgram);
    printf("%s\n\n", Purpose2Program);
}


int main(int argc, char *argv[]) {
	
    if (argc == 1 || strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        printf("\nUsage: ./scanda [parameters]..[ip]\n\n");

        char PurposeProgram[] = "Scanda v8.20 (c) 2023 by Hunkar Acar. This tool is a simple tool created to test the security of SCADA systems.\n\n";
        char Purpose2Program[] = "Scanda tool is a tool created to test the security of SCADA systems at intermediate and basic levels using various scenarios (c) v8.20\n"
                                 "Developer: Hunkar Acar. Being open-source allows for further development.";

        printf("Development: \\\\\\\\Hunkar Acar/////////\n\n");
        printf("Github: https://github.com/hunkaracar\n");
        printf("------------------------------------------------------------------\n");
        printf("\n%s", PurposeProgram);
        printf("Options:\n");

        printf("\t--help: Show help documentation\n");
        printf("\t-h: Show help documentation\n");
        printf("\t-T: Perform a general scan on the target IP\n");
        printf("\t-V: Tries to get version information on scanned ports\n");
        printf("\t-D: Makes directory discovery to web services of scada systems\n");
        printf("\t-F -f: Scada systems generally broadcast on the http(80) port and this argument provides version information and redirects to the website.\n");
        printf("\t-l -L:list: Shows the most used ports and the list of protocols by scada systems\n");
        printf("\t-p: Perform scanning on a specific port\n");
        printf("\t-U: Show the application running on the SCADA system\n");
        printf("\t-B: Attempt default password testing (Brute Force) on protocols requiring authentication in SCADA systems\n");
        printf("\t-m: Specify the protocol for the attack and perform the attack accordingly\n\n");
        printf("%s\n\n", Purpose2Program);

        printf("Examples:\n");
        printf("\tscanda -T 107.111.1.1\n");
        printf("\tscanda -p 21 107.111.1.1\n");
        printf("\tscanda -V 107.111.1.1\n");
        printf("\tscanda -F 107.111.1.1 or scanda -f 107.111.1.1 \n");
        //printf("\tscanda -E -p 21 107.111.1.1\n");
        printf("\tscanda -U 107.111.1.1\n");
        printf("\tscanda -D 107.111.1.1\n");
        printf("\tscanda -L or scanda -l\n");
        printf("\tscanda -B 107.111.1.1 -m FTP\n");

        return 0;
    }

   if (strcmp(argv[1], "-p") == 0) {
        if (argc != 4) {
            printf("Error: Invalid parameters. Please specify the target IP address and port number.\n");
            return 1;
        }

        char* target_ip = argv[3];
        int target_port = atoi(argv[2]);

        scanBeginV2(target_ip,target_port);
        scanPort(target_ip,target_port);
        EndPoint();
        
    }
    
    else if (strcmp(argv[1], "-T") == 0) {
        if (argc != 3) {
            printf("Error: Invalid parameters. Please specify the target IP address.\n");
            return 1;
        }

        char* target_ip = argv[2];

        scanBegin(target_ip);
        scanSystem(target_ip);
        EndPoint();
        
    }
    
    else if (strcmp(argv[1], "-U") == 0) {
		if (argc != 3) {
			printf("Error: Invalid parameters. Please specify the target IP address.\n");
			return 1;
		}
		
		char* ip_address = argv[2];
		
		scanBeginV3(ip_address);
		scanSystemProtocol(ip_address);
		EndPoint();
	}
	
	else if (strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "-L") == 0){
		if (argc != 2){
			printf("Error: Invalid parameters. Please get specify the -l and -L.\n");
			return 1;
		}
		
		returnPortList();
		EndPoint();
		
	}
	
	else if (strcmp(argv[1], "-B") == 0) {
        if (argc != 5) {
            printf("Error: Invalid parameters. Please specify the target IP address and protocol.\n");
            return 1;
        }
        
        char* target_ip = argv[2];
        char* protocol = argv[4];
        int port;
        
        if (strcmp(protocol, "FTP") == 0 || strcmp(protocol, "ftp") == 0) {
            port = 21;
        }
        
        else if (strcmp(protocol, "SSH") == 0 || strcmp(protocol, "ssh") == 0) {
            port = 22;
        }
         
        else if (strcmp(protocol, "Telnet") == 0 || strcmp(protocol, "telnet") == 0) {
            port = 23;
        }
         
        else {
            printf("Error: Unsupported protocol: %s\n", protocol);
            return 1;
        }
        
        scanBeginV4(target_ip,port,protocol);
        bruteForceMode(target_ip, port, protocol);
        EndPoint();
    }
    
    else if (strcmp(argv[1],"-V") == 0){
		if (argc != 3){
			printf("Error: Invalid parameters. Please specify the target IP address.\n");
            return 1;
		}
		
		char* targetip = argv[2];
		
		scanBeginV5(targetip);
		get_Version(targetip);
		EndPoint();
	}
	
	else if (strcmp(argv[1],"-F") == 0 || strcmp(argv[1],"-f") == 0) {
		if (argc != 3){
			printf("Error: Invalid parameters. Please specify the target IP address.\n");
            return 1;
		}
		char* target_ip = argv[2];
		sleep(1);
		getHTTPVersion(target_ip);
		EndPoint();
	}
	
	else if (strcmp(argv[1],"-D") == 0) {
		if (argc != 3){
			printf("Error: Invalid parameters. Please specify the target IP address.\n");
            return 1;
		}
		char* target_ip = argv[2];
		printInfo(target_ip);
		DiscoveryDirectory(target_ip);
		EndPoint();
		
	}
     
    else {
        printf("Error: Invalid command. Please use either '-p' or '-T or -B or -U' option.\n");
        return 1;
    }

    return 0;
}
