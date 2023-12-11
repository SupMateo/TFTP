#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#define FD_TERMINAL_OUT 1
#define BUFSIZE 1024

int main(int argc, char **argv)
{
	struct addrinfo hints, *result, *rp;
	struct sockaddr_in server_socket;

	memset(&hints, 0, sizeof(struct addrinfo)); 
	hints.ai_family = AF_INET;     
    hints.ai_socktype = SOCK_STREAM;

	char hostname[BUFSIZE];
	char file[BUFSIZE];
	char* port = "23";

	int status;
	int sock;
	int port_int = 23;
	

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

		if ((sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol)) < 0)
		{
			perror("Socket error");
			freeaddrinfo(result);
			exit(EXIT_FAILURE);
		}

		if (connect(sock, result->ai_addr, result->ai_addrlen) != 0)
		{
			perror("Connect error");
			close(sock);
			freeaddrinfo(result);
			exit(EXIT_FAILURE);
		}

		freeaddrinfo(result);
	}
}
