/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ASSIGNMENT: Implement the Daemons Broadcast (Client)
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
    struct sockaddr_in myaddr,servaddr;
    socklen_t addrlen = sizeof(servaddr); /* length of addresses */
    struct hostent *hp; /* host information */
    //struct sockaddr_in servaddr; /* server address */
    char *my_messsage = "This is a test message from client";
    unsigned char rbuf[BUFSIZE];
    int recvlen; /* # bytes received */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    { cout<<"Cannot create socket"<<endl;
      return 0;
    }
    memset((char *)&myaddr, 0, sizeof(myaddr));
    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    myaddr.sin_port = htons(0);
    if (bind(sockfd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
    { cout<<"Bind failed"<<endl; return 0; }

    /* fill in the server's address and data */
    memset((char*)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serverport);
    /* look up the address of the server given its name */
    hp = gethostbyname(serverhost);
    if (!hp)
    {
        cout<<"Could not obtain address of"<< serverhost<<endl;
        return 0;
    }
    /* put the host's address into the server address structure */
    memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);
    /* send a message to the server */
    cout<<"Sending Message......"<<endl;
    if (sendto(sockfd, my_messsage, strlen(my_messsage), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    { cout<<"sendto failed"<<endl; return 0; }

    recvlen = recvfrom(sockfd, rbuf, BUFSIZE, 0, (struct sockaddr *)&servaddr, &addrlen);
    if (recvlen > 0)
    {
        cout<<"Response from Server: "<< rbuf<<endl;
    }
}
