#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void)
{
    int serverSockFd, clientSockFd;
    int clientLen;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    serverSockFd = socket(AF_INET, SOCK_STREAM, 0);//create a new unnamed socket.

    serverAddress.sin_family = AF_INET;
	//serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(3333);
	//serverAddress.sin_port = 3333;
    //strcpy(serverAddress.sun_path, "server_socket");
    //change unnamed socket to named socket by bind function.
    bind(serverSockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(serverSockFd, 5);//create a listen queue that to wait for client to connect...
    while(1)
    {
        char ch;
        printf("the server is waiting\n");

        clientLen = sizeof(clientAddress);
        //accept a connection from client.
        clientSockFd = accept(serverSockFd, (struct sockaddr *)&clientAddress, &clientLen);
        //read from client.
        read(clientSockFd, &ch, 1);
        ch ++;
        //write to client.
        write(clientSockFd, &ch, 1);
        //close client socket.
        close(clientSockFd);
        exit(0);
    }
}
