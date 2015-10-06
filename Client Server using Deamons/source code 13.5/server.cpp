/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>
#include <sys/stat.h>

#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SOCK_PATH "echo_socket"

using namespace std;
///////////////////////////////////////////////////////////////////////////////////////////////
//DESCRIPTION:the function demonize() Tries to fork process to create child process
//INPUT:void
//OUTPUT:void
////////////////////////////////////////////////////////////////////////////////////////////////
static void daemonize(void)
{
    pid_t pid, sid;

    /* already a daemon */
    if ( getppid() == 1 ) return;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* At this point we are executing as the child process */

    /* Change the file mode mask */
    umask(0);

    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Change the current working directory.  This prevents the current
       directory from being locked; hence not being able to remove it. */
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    /* Redirect standard files to /dev/null */
    freopen( "/dev/null", "r", stdin);
    freopen( "/dev/null", "w", stdout);
    freopen( "/dev/null", "w", stderr);
}
///////////////////////////////////////////////////////////////////////////////////////////////
//DESCRIPTION: this function handle client requests and handle input processes
//INPUT:VOID
//OUTPUT:INT AS RETURN VAL 
////////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{

    socklen_t t;
    int s, s2, len;
    struct sockaddr_un local, remote;
    char str[100];
    time_t tt;
    struct tm * now;


    if ((s = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);
    unlink(local.sun_path);
    len = strlen(local.sun_path) + sizeof(local.sun_family);
    if (bind(s, (struct sockaddr *)&local, len) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }

    daemonize();

    for(;;) {
        int done, n;
	string datetime = "";

        printf("Waiting for a connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr *)&remote, &t)) == -1) {
            perror("accept");
            exit(1);
        }

        printf("Connected.\n");

        done = 0;
        do {
            n = recv(s2, str, 100, 0);
            if (n <= 0) {
                if (n < 0) perror("recv");
                done = 1;
            }

            if (!done){

		datetime = "";
		tt = time(0);
		now = localtime( & tt );
		datetime.append("Date: ");
		datetime.append(to_string(now->tm_mon + 1));
		datetime.append("-");
		datetime.append(to_string(now->tm_mday));
		datetime.append("-");
		datetime.append(to_string(now->tm_year + 1900));

		datetime.append(" Time: ");
		datetime.append(to_string(now->tm_hour));
		datetime.append("-");
		datetime.append(to_string(now->tm_min));
		datetime.append("-");
		datetime.append(to_string(now->tm_sec));
			
		strcpy(str,datetime.c_str());

                if (send(s2, str, 36, 0) < 0) {
                    perror("send");
                    done = 1;
                }
	    }
        } while (!done);

        close(s2);
    }

    return 0;
}
