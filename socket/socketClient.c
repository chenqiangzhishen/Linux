#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>


int main(void)
{
    int clientSockFd;
    char ch = 'A';
    int result;
    struct sockaddr_un serverAddress;
    //create a client socket.
    clientSockFd = socket(AF_UNIX, SOCK_STREAM, 0);
    //rename the client socket according to server's socket
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, "server_socket");
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
