///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ASSIGNMENT: implement the daytime server
//Name: Rahul Shinde
//CHICO STATE ID # 006948956
//CHANGE lOG:	
//INITIALS		|	DATE		|		 DESCRIPTION
//KJ			|	11/19/2014	|		Implemented simple client server app
//RS			|	11/20/2014	|		Implemented echo functionality
//AD			|	11/23/2014	|		Tried forking process to create child process
//TP			|	11/24/2014	|		Successfully forked processes but unable to handle client-server request
//KJ			|	11/26/2014	|	    Daemon successfully working as expected and perfectly handling client requests. Also implemented documentation.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SOCK_PATH "echo_socket"

///////////////////////////////////////////////////////////////////////////////////////////////////////
//DESCRIPTION:this function connects with server and handle processes successfully
//INPUT:void
//OUTPUT:int return val
////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    int s, t, len;
    struct sockaddr_un remote;
    char str[100];

    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    printf("Trying to connect...\n");

    remote.sun_family = AF_UNIX;
    strcpy(remote.sun_path, SOCK_PATH);
    len = strlen(remote.sun_path) + sizeof(remote.sun_family);
    if (connect(s, (struct sockaddr *)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected.\n");

    while(1){//printf("> "), fgets(str, 100, stdin), !feof(stdin)) {
        if (send(s, str, strlen(str), 0) == -1) {
            perror("send");
            exit(1);
        }

        if ((t=recv(s, str, 100, 0)) > 0) {
            str[t] = '\0';
            printf("%s\n", str);
		exit(0);
        } else {
            if (t < 0) perror("recv");
            else printf("Server closed connection\n");
            exit(1);
        }
    }

    close(s);

    return 0;
}
