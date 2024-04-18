/*
** MYTEAMS PROJECT, 2024
** client.c
** File description:
** client.c
*/

#include "client.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "libs/def.h"

int recv_serveur(client_t *client)
{
    char buf[4097] = {0};
    int bytes_received = 0;

    if (FD_ISSET(client->fd, &(client->read_fd))) {
        bytes_received = read(client->fd, buf, 4096);
        if (bytes_received < 0) {
            PERR_NORET("no byte read\n");
            return 84;
        }
        if (bytes_received == 0)
            return 0;
        buf[bytes_received] = '\0';
        dolibteams(buf);
        printf("Server response: %s\n", buf);
    }
    return 0;
}

int send_serv(client_t *client)
{
    char buf[4097] = {0};

    if (FD_ISSET(STDIN_FILENO, &(client->read_fd))) {
        if (fgets(buf, 4096, stdin) == NULL) {
            PERR_NORET("fgets failed");
            return 84;
        }
        if (write(client->fd, buf, strlen(buf)) == -1) {
            PERR_NORET("fgets failed");
            return 84;
        }
    }
    return 0;
}

static bool is_running(bool running)
{
    static int current = true;
    static int next = true;

    current = next;
    next = running;
    return current;
}

static void sig_handler(int signal)
{
    (void)signal;
    is_running(false);
}

int launch_client(client_t *client)
{
    signal(SIGINT, sig_handler);
    FD_ZERO(&(client->read_fd));
    while (is_running(true)) {
        FD_SET(STDIN_FILENO, &(client->read_fd));
        FD_SET(client->fd, &(client->read_fd));
        if (select(client->fd + 1, &(client->read_fd), NULL, NULL, NULL) == -1)
            break;
        send_serv(client);
        recv_serveur(client);
    }
    if (write(client->fd, "/logout\n", strlen("/logout\n")) == -1) {
        PERR_NORET("fgets failed");
        return 84;
    }
    return 0;
}

static struct client_s *default_client(void)
{
    client_t *ret = malloc(sizeof(client_t));

    ret->fd = socket(AF_INET, SOCK_STREAM, 0);
    return ret;
}

static struct sockaddr_in default_sockaddr(int port)
{
    struct sockaddr_in serv_addr;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    return serv_addr;
}

client_t *get_client(int port, const char *ip)
{
    client_t *clien = default_client();
    struct sockaddr_in serv_addr = default_sockaddr(port);
    int status = 0;

    if (clien == NULL || clien->fd < 0) {
        printf("\n Socket creation error \n");
        return NULL;
    }
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return NULL;
    }
    status =
        connect(clien->fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (status < 0) {
        printf("\nConnection Failed \n");
        return NULL;
    }
    return clien;
}
