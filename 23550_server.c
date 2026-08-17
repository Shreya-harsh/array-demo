#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

int main()
{
    int server_fd,new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];

    server_fd = socket(AF_INET,SOCK_STREAM,0);

    if(server_fd < 0)
    {
        perror("socket creation failed");
        exit(1);
    }


    address.sin_family =AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if(bind(server_fd,(struct sockaddr *)&address,
                sizeof(address)) < 0){
        perror("bind failed");
        exit(1);
    }

    if(listen(server_fd,5) < 0)
    {
        perror("listen failed");
        exit(1);
    }

    printf("server listening on port  %d...\n",PORT);

    new_socket = accept(server_fd,(struct sockaddr *)&
            address,(socklen_t *)&addrlen);

    if(new_socket < 0)
    {
        perror("Accept failed");
        exit(1);
    }

    printf("client connected.\n");

// communication code
while(1)
{
    buffer[sizeof(buffer)-1]='\0';
    read(new_socket,buffer,sizeof(buffer));

    printf("client: %s\n",buffer);
    if((strcmp(buffer,"bye")==0)
    {
        printf("bye")
            break;
    }
}

    close(new_socket);
    close(server_fd);
    return 0;
}
