#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SERVER_PORT 8000

int main(int argc,char *argv[])
{

    int d,k;
    k=atoi (argv[1]);
    d=atoi (argv[2]);

//The client only needs a socket file descriptor for communication with the server
    int clientSocket;
//Describe the socket of the server
    struct sockaddr_in serverAddr;
    char sendbuf[200];
    if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
//ip address

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect");
        return 1;
    }

    sendbuf[0]='0';
    sendbuf[1]='\0';
    send(clientSocket, sendbuf, strlen(sendbuf), 0);//send message
    srand((unsigned)time(NULL));
    int  a = rand()%100*100; //random time
    usleep(a);
    while(1){
        int j;
        for(j=1;j<k;j++)
        {
            int num=j*d;
            int n;
            char ch;
            for(n = 0; num; ++n) {
                sendbuf[n] = num % 10 + '0';
                num /= 10;
            }
            sendbuf[n] = '\0';
            int i;
            for(i = 0; i < n / 2; ++i) {
                ch = sendbuf[i];
                sendbuf[i] = sendbuf[n - 1 - i];
                sendbuf[n - 1 - i] = ch;
 	    }
          send(clientSocket, sendbuf, strlen(sendbuf), 0);
           srand((unsigned)time(NULL));
           int  a = rand()%100*100;

          usleep(a);
        }
        sendbuf[0] = '-';
        sendbuf[1] = '1';
        sendbuf[2] = '\0';
        send(clientSocket, sendbuf, strlen(sendbuf), 0);
    }
    close(clientSocket);
    return 0;

}
