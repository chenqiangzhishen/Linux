#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>//socket(), connect()
#include <sys/un.h>//sockaddr_un
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>//AF_INET
#include <arpa/inet.h>//inet_addr()


int main(void)
{
    int clientSockFd;
    char ch = 'A';
    int result;
    struct sockaddr_in serverAddress;
    //create a client socket.
    clientSockFd = socket(AF_INET, SOCK_STREAM, 0);
    //rename the client socket according to server's socket
    serverAddress.sin_family = AF_INET;
	//serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(3333);
	//serverAddress.sin_port = 3333;
    //strcpy(serverAddress.sun_path, "server_socket");
    //let client socket connect to server
    result = connect(clientSockFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if(result == -1)
    {
        perror("oops: socketClient");
        exit(1);
    }
    //write and read from the created client socket.
    write(clientSockFd, &ch, 1);
    read(clientSockFd, &ch, 1);
    printf("char from server=%c\n", ch);
    close(clientSockFd);
    exit(0);
}
