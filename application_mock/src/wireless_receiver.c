#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>


#include "wireless_receiver.h"
#include "fan_control_protocol.h"
#include "registers.h"

#define PORT 8000
#define MAX_BUFFER_LENGTH 16

static void* recv_task(void *vargp);

void wireless_receiver_start_receive(pthread_t* id)
{
    pthread_create(id, NULL, recv_task, NULL);
}

static void* recv_task(void *vargp)
{
    int server_socket, connection_socket, bytes_read;
    struct sockaddr_in address;
    socklen_t address_size = sizeof(address);
    int opt = 1;
    char buffer[MAX_BUFFER_LENGTH] = {0};
       
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("Socket creation failed!");
        goto exit;
    }
       
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("Setting socket option failed!");
        goto exit;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );

    if (bind(server_socket, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Binding failed!");
        goto exit;
    }

    if (listen(server_socket, 1) < 0)
    {
        perror("Listening failed!");
        goto exit;
    }

    while(1)
    {
        printf("Waiting for client to connect\n");

        if ((connection_socket = accept(server_socket, (struct sockaddr *)&address, (socklen_t *)&address_size)) < 0)
        {
            perror("Accepting the connection failed");
            goto exit;
        }

        printf("Client connected\n");

        while(1)
        {
            bytes_read = recv(connection_socket, buffer, sizeof(buffer), 0);

            if (bytes_read == 0)
            {
                printf("Client closed the connection\n");
                break;
            }

            printf("Received(%d): ", bytes_read);
            for (int i = 0; i < bytes_read; i++)
                printf("%d ", buffer[i]);
            printf("\n");

            int action_ret = process_message(bytes_read, buffer);
            printf("New FAN (%d) register value: ", action_ret);
            printByte(FAN);
        
            memset(buffer, 0, sizeof(buffer));
        }
    }

exit:
    printf("Exit thread!");
}