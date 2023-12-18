#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "gettftp.h"

#define FD_TERMINAL_OUT 1
#define BUFSIZE 1024

int main(int argc, char **argv)
{
	struct addrinfo hints, *result, *rp,*p;

	memset(&hints, 0, sizeof(struct addrinfo)); 
	hints.ai_family = AF_INET;     
    hints.ai_socktype = SOCK_DGRAM;

	char hostname[BUFSIZE];
	char ip[BUFSIZE];
	char file[BUFSIZE];
	char* port = "69";
	char rrq[BUFSIZE];

	int status;
	int sock;
	int port_int = 69;
	

	if(argc != 3)
	{
		write(FD_TERMINAL_OUT,"Syntax : ./gettftp.c hostname file\n",strlen("Syntaxe : ./gettftp.c hostname file\n"));
	}
	else
	{
			
		strncpy(hostname, argv[1], BUFSIZE - 1);
		hostname[BUFSIZE - 1] = '\0';

		strncpy(file, argv[2], BUFSIZE - 1);
		file[BUFSIZE - 1] = '\0';

		status = getaddrinfo(hostname, port, &hints, &result);
		if (status != 0) {
			fprintf(stderr, "ERROR : %s\n", gai_strerror(status));
			exit(EXIT_FAILURE);
		}	
			

		inet_ntop(AF_INET, &result->ai_addr->sa_data[2], ip, sizeof(ip));
		printf("IP : %s\n",ip);
		if((sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) == -1){
			perror("socket");
		}
		printf("socket réservé !\n");
		snprintf(rrq, BUFSIZE, "00000001%s0000octet0000", file);

		if (sendto(sock, rrq, strlen(rrq), 0, result->ai_addr, sizeof(*(result->ai_addr))) == -1)
        {
            perror("sendto");
            exit(EXIT_FAILURE);
        }else{
			printf("message envoyé : %s\n",rrq);
			close(sock);
			freeaddrinfo(result);
		}
	}
}

