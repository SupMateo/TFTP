#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define FD_TERMINAL_OUT 1
#define BUFSIZE 1024

int main(int argc, char **argv)
{
	char server[BUFSIZE];
	char file[BUFSIZE];

	if(argc != 3)
	{
		write(FD_TERMINAL_OUT,"Syntax : ./gettftp.c hostname file\n",strlen("Syntaxe : ./gettftp.c hostname file\n"));
	}
	else
	{
		strncpy(server, argv[1], BUFSIZE - 1);
        server[BUFSIZE - 1] = '\0';

        strncpy(file, argv[2], BUFSIZE - 1);
        file[BUFSIZE - 1] = '\0';
	}
}
