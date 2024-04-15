/*
** MYTEAMS PROJECT, 2024
** client.c
** File description:
** client.c
*/

#include "client.h"
#include <stdlib.h>

int send_and_recv_mess(char *buf, client_t *client)
{
    int bytes_received = 0;

    if (send(client->fd, buf, strlen(buf), 0) == -1) {
        perror("send");
        return 84;
    }
    bytes_received = recv(client->fd, buf, 1024, 0);
    if (bytes_received == -1) {
        perror("recv");
        return 84;
    }
    buf[bytes_received] = '\0';
    printf("Server response: %s\n", buf);
    return 0;
}

int launch_client(client_t *client)
{
    char *buf;
    size_t buf_size = 0;

    while (1) {
        printf("Enter command: ");
        if (getline(&buf, &buf_size, stdin) == -1) {
            perror("getline");
            break;
        }
        send_and_recv_mess(buf, client);
    }
    return 0;
}

static struct client_s *default_client(void)
{
    client_t *ret = malloc(sizeof(client_t));

    ret->fd = socket(AF_INET, SOCK_STREAM, 0);
    ret->status = 0;
    return ret;
}

static struct sockaddr_in default_sockaddr(int port)
{
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    return serv_addr;
}

client_t *get_client(int port)
{
    client_t *clien = default_client();
    struct sockaddr_in serv_addr = default_sockaddr(port);

    if (clien == NULL || clien->fd < 0) {
        printf("\n Socket creation error \n");
        return NULL;
    }
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return NULL;
    }
    clien->status = connect(clien->fd, (struct sockaddr*)&serv_addr,
    sizeof(serv_addr));
    if (clien->status < 0) {
        printf("\nConnection Failed \n");
        return NULL;
    }
    return clien;
}
