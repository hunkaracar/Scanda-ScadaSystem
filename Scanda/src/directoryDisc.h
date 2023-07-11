#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <curl/curl.h>
#include <time.h>
#include <unistd.h>


void printInfo(char* target_ip) {
	printf("\nStarting directory discovery...\n");
	printf("Target http://[%s] Attempt\n",target_ip);
	printf("----------------------------------------------------------\n\n");
	sleep(3);
}

void DiscoveryDirectory(const char* target_ip) {

      const char* directoryArray[] = {
        "/robots.txt", "/admin", "/administrator", "/login", "/control", "/config", "/data",
        "/logs", "/images", "/scripts", "/cgi-bin", "/api", "/backup", "/dashboard",
        "/reports", "/settings", "/monitoring", "/utilities", "/maintenance",
        "/diagnostics", "/historical_data", "/alarms", "/archive", "/devices",
        "/events", "/protocols", "/updates", "/secure", "/test", "/help", "/public",
        "/configurations", "/alarms_and_events", "/status", "/history", "/assets", "/procedures",
        "/modbus", "/opendnp3", "/opc", "/scans", "/trends", "/users", "/roles",
        "/permissions", "/audit", "/backup_and_restore", "/system_info", "/security",
        "/firmware", "/notifications", "/bin/", "/cache/", "/cli/", "/components/", "/includes/",
        "/installation/", "/language/", "/layouts/", "/libraries/", "/logs/", "/modules/", "/plugins/",
        "/tmp/"
    };
     
     //Total number of directories
     int directoryCount = sizeof(directoryArray) / sizeof(directoryArray[0]);
     
     //use cURL to send HTTP request
     CURL *curl = curl_easy_init();
     if (curl) {
		 CURLcode res;
		 
		 int i;
		 for(i=0; i < directoryCount; i++) {
			 //Generate request URL
			 char request_url[200];
			 snprintf(request_url,sizeof(request_url),"http://%s%s",target_ip,directoryArray[i]);
			 
			 //CURL Building
			curl_easy_setopt(curl, CURLOPT_URL, request_url);
            curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
            curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
            
            //Send Request
            res = curl_easy_perform(curl);
            
            //HTTP state code control
            long http_code = 0;
            curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE, &http_code);
            if (res != CURLE_OK) {
				printf("%s Failed to send request!\n", directoryArray[i]);
			}
			else {
				if (http_code == 200) {
					printf("Discovered Directory %s: 200 OK\n",directoryArray[i]);
				}
				else if (http_code == 403) {
					printf("Discovered Directory %s: Forbidden (403)\n", directoryArray[i]);
				}
			}
			 
		 }
		 
		 //Clear CURL
		 curl_easy_cleanup(curl);
		 
		 printf("\n____________________________________________________________________\n");
		 printf("--[[Directory Scan performed successfully]]--\n\n");
    
	}
}
    
