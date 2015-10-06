/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ASSIGNMENT: Implement the Daemons Broadcast (Server)
//Name: Rahul Shinde
//CHICO STATE ID # 006948956
//CHANGE lOG:	|	DATE		|		 DESCRIPTION
//KJ			|	11/18/2014	|	Study and Implementation of Daemons Broadcast Client		
//AD			|	11/21/2014	|	Study and Implementation of Daemons Broadcast Client
//TP			|	11/22/2014	|   Study and Implementation of Daemons Broadcast Server
//RS			|	11/25/2014	|	Study and Implementation of Daemons Broadcast Server 
//KJ			|	11/26/2014	|	Testing and Documentation
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <sys/socket.h>
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <netdb.h>
using namespace std;

#define serverhost "localhost"
#define serverport 5000
#define BUFSIZE 2048

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//DESCRIPTION:this function connects with server and handle processes successfully
//INPUT:void
//OUTPUT:int return val
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

int main()
{
    int sockfd;
    struct sockaddr_in myaddr;
    struct sockaddr_in remaddr; /* remote address */
    socklen_t addrlen = sizeof(remaddr); /* length of addresses */
    int recvlen; /* # bytes received */
    unsigned char rbuf[BUFSIZE],sbuf[BUFSIZE];
    char *messsage = "Message Received\n";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    { cout<<"cannot create socket"<<endl;
      return 0;
    }
    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(serverport);
    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
    { cout<<"bind failed"<<endl; return 0; }

    cout<<"Server Started..."<<endl;
    /* now loop, receiving data and printing what we received */
    for (;;)
    {
        cout<<"waiting on port "<<serverport<<endl;
        recvlen = recvfrom(sockfd, rbuf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
        cout<<"received "<<recvlen<<"  bytes"<<endl;
        if (recvlen > 0)
        {
            cout<<"received message: "<< rbuf<<endl;
            sendto(sockfd, messsage, 17/*strlen(messsage)*/, 0, (struct sockaddr *)&remaddr, addrlen);
        }
        bzero(rbuf,BUFSIZE);
        //bzero(sbuf,BUFSIZE);
    }

     /* never exits */
}
