#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

#define SERVER_PORT 8000

int main()
{
//File descriptor returned by calling socket function
    int serverSocket;

//Declare two proprietary sockaddr_in structure variables,
//represent the client and server respectively
    struct sockaddr_in server_addr;
    struct sockaddr_in clientAddr;
    int addr_len = sizeof(clientAddr);
    int client;
    char buffer[200];
    int iDataNum;
    if((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(serverSocket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        return 1;
    }

//Set the socket on the server to the listening state
    if(listen(serverSocket, 5) < 0)
    {
        perror("listen");
        return 1;
    }

//Always in accept blocking state
        client = accept(serverSocket, (struct sockaddr*)&clientAddr, (socklen_t*)&addr_len);
        if(client < 0)
        {
            perror("accept");
        }

        while(1)  //Continuously accept data from the client
        {
            buffer[0] = '\0';
            iDataNum = recv(client, buffer, 200, 0);
            if(iDataNum <0)
            {
                perror("recv null");
                continue;
            }
            buffer[iDataNum] = '\0';
            if(strcmp(buffer, "-1") == 0)
                break;
            printf("%s", buffer);

        }
    close(serverSocket);//Disconnect from the client
    return 0;
}

 
