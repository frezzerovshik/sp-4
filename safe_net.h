//
//  safe_net.h
//  sp_4_lab
//
//  Created by Артем Шарапов on 06.06.2020.
//  Copyright © 2020 Artem Sharapov. All rights reserved.
//

#pragma once
#include <sys/types.h>
//Socket functions including error handling

//Server functions
int socket_s(int domain, int type, int protocol);
void bind_s(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void listen_s(int sockfd, int backlog);
int accept_s(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

//Client functions
void connect_s(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void inet_pton_s(int af, const char* src, void *dst);


