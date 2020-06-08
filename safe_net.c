//
//  safe_net.c
//  sp_4_lab
//
//  Created by Артем Шарапов on 06.06.2020.
//  Copyright © 2020 Artem Sharapov. All rights reserved.
//

#include "safe_net.h"

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//Server
int socket_s(int domain, int type, int protocol) {
    int result = socket(domain, type, protocol);
    if (result == -1) {
        perror("Socket opening error");
        exit(EXIT_FAILURE);
    }
    return result;
}
void bind_s(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int result = bind(sockfd, addr, addrlen);
    if (result == -1) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }
    
}
void listen_s(int sockfd, int backlog) {
    int result = listen(sockfd, backlog);
    if (result == -1) {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }
}
int accept_s(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int result = accept(sockfd, addr, addrlen);
    if (result == -1) {
        perror("Accepting error\n");
        exit(EXIT_FAILURE);
    }
    return result;
}

//Client
void inet_pton_s(int af, const char* src, void *dst) {
    int result = inet_pton(af, src, dst);
    switch (result) {
        case -1:
            perror("Addres family is non-valid");
            exit(EXIT_FAILURE);
            break;
        case 0:
            printf("Non-valid adress\n");
            exit(EXIT_FAILURE);
            break;
        default:
            break;
    }
}

void connect_s(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int result = connect(sockfd, addr, addrlen);
    if (result == -1) {
        perror("Connection fail");
        exit(EXIT_FAILURE);
    }
}
