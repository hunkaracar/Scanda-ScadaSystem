#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void returnPortList(){
	
	printf("\nShows the most used ports and the list of protocols by scada systems\n\n");
	
	int ports[] = {	
	21, 22, 23, 25, 53, 69, 80, 88, 102, 110, 111, 123, 143, 161, 162, 179, 194, 389, 443, 465,
    502, 514, 520, 636, 993, 995, 102, 1023, 1024, 1025, 1026, 1080, 1194, 1234, 1433, 1521, 1701, 1723, 1812,
    1813, 1883, 2222, 2427, 2428, 3000, 3030, 3128, 3306, 3389, 3690, 4000, 4040, 4321, 4567, 47808, 47809,
    4840, 5000, 5001, 5002, 5003, 5020, 5432, 5631, 5632, 5900, 6000, 6001, 62541, 6379, 6666, 6667, 8000, 8080, 8081,8082,8087,
     8443, 8888, 9000, 9001, 9100, 9200, 9500, 9600, 9876, 9999, 44818, 41820, 20000,20001
    
	};
	
	const char* ProtocolPorts[] = {
		"FTP","SSH", "Telnet", "SMTP", "DNS", "TFTP", "HTTP", "Kerberos","ISO-TSAP","POP3","NFS", "NTP", "IMAP", "SNMP","SNMP","BGP", "IRC", "LDAP", "HTTPS",
		"SMTPS", "Modbus", "RIP", "LDAPS", "IMAPS", "POP3S", "Reserved", "Reserved", "Reserved", "Reserved", "SOCKS", "OpenVPN", "Reserved",
		"MSSQL", "Oracle", "L2TP", "PPTP", "RADIUS", "RADIUS Accounting", "NFS", "Zookeeper", "X11", "Docker", "MS-SQL Monitor", "MS-SQL",
		"MediaWiki", "Redis", "Apache Tomcat", "MySQL", "Proxy Server", "RDP", "SVN", "Ruby on Rails", "Elasticsearch", "Home Assistant", "VNC",
		"Webmin", "Git", "MongoDB", "Oracle WebLogic","MC Protocol","MC Protocol","MELSEC Communication Protocol","Remote Desktop Gateway", "IKE", "IKE NAT", "IIS", "Jenkins", "Ethereum",
		"BitTorrent", "RTSP", "DHCP Server", "DHCP Client", "Modbus", "SNMP", "SCADA", "blackice-icecap","blackice-alerts", "TCP","SCADA", "SCADA","SCADA",
		"SCADA", "SCADA", "SCADA", "SCADA", "SCADA","MQTT (Message Queuing Telemetry Transport)", "MQTT (Message Queuing Telemetry Transport)",
		"Siemens S7",
		"Ethernet/IP (Food and beverage industry)","DNP3","DNP3"
		
	};
	
	
	int num_port = sizeof(ports)/ sizeof(ports[0]);
	
	int i;
	for (int i=0; i<num_port; i++){
		
		printf("%d [%s]\n",ports[i],ProtocolPorts[i]);
		
	}
	
	//return 1;
	
}
