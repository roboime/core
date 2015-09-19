/*
 * This file is part of the ssl-sim project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the
 * use of this software.  Permission is granted to anyone to use this software
 * for any purpose, including commercial applications, and to alter it and
 * redistribute it freely, subject to the following restrictions:
 */

#include "net.h"

// TODO: Windows implementation for better cross-platform

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

static const unsigned int ONE = 1;
static const unsigned char TTL = 3;

struct Socket {
  int sockfd;
  struct sockaddr_in saddr;
  struct ip_mreq mreq;
};

struct Socket *new_socket_iface(int port, const char *addr, const char *iface) {
  struct Socket *i = (struct Socket *)calloc(1, sizeof(struct Socket *));

  // open a UDP socket
  if ((i->sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
    perror("Could not open socket file descriptor");

  i->saddr.sin_family = PF_INET;
  i->saddr.sin_port = htons(port);

#define OR_ANY(ADDR) (strlen(ADDR) ? inet_addr(ADDR) : htonl(INADDR_ANY));
  // bind socket to the multicast address if present
  i->saddr.sin_addr.s_addr = OR_ANY(addr);

  i->mreq.imr_multiaddr.s_addr = inet_addr(addr);
  i->mreq.imr_interface.s_addr = OR_ANY(iface);
#undef OR_ANY

  return i;
}

struct Socket *new_socket(int port, const char *addr) {
  return new_socket_iface(port, addr, "");
}

void delete_socket(struct Socket *socket) {
  // shutdown socket
  shutdown(socket->sockfd, 2);

  // close socket
  close(socket->sockfd);

  free(socket);
}

bool socket_receiver_bind(struct Socket *socket) {
  // enable address reuse
  if (setsockopt(socket->sockfd, SOL_SOCKET, SO_REUSEADDR, &ONE, sizeof(ONE)) < 0) {
    perror("Could not enable address reuse");
    return false;
  }

  // bind to interface
  if (bind(socket->sockfd, (struct sockaddr *)&socket->saddr, sizeof(socket->saddr)) < 0) {
    perror("Could not bind socket to interface");
    return false;
  }

  // join multicast group
  if (setsockopt(socket->sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                 (const void *)&socket->mreq, sizeof(socket->mreq)) < 0) {
    perror("Could not join to multicast");
    return false;
  }

  return true;
}

bool socket_sender_bind(struct Socket *socket) {
  struct sockaddr_in saddr;
  saddr.sin_family = PF_INET;
  saddr.sin_port = htons(0);                 // Use the first free port
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); // bind socket to any address

  if (bind(socket->sockfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) <
      0) {
    perror("Error binding socket to interface");
    return false;
  }

  struct in_addr iaddr;
  memset(&iaddr, 0, sizeof(struct in_addr));
  iaddr.s_addr = INADDR_ANY; // use DEFAULT interface

  // Set the outgoing interface to DEFAULT
  if (setsockopt(socket->sockfd, IPPROTO_IP, IP_MULTICAST_IF, &iaddr,
                 sizeof(struct in_addr)) < 0) {
    perror("Could not set outgoing interface");
    return false; // XXX: maybe some of these errors can be ignored?
  }

  // Set multicast packet TTL to 3; default TTL is 1
  if (setsockopt(socket->sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &TTL, sizeof(TTL)) <
      0) {
    perror("Could not set multicast packet TTL");
    return false;
  }

  // send multicast traffic to myself too
  if (setsockopt(socket->sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &ONE, sizeof(ONE)) <
      0) {
    perror("Could not enable multicast loop to self");
    return false;
  }

  return true;
}

int socket_receive(struct Socket *socket, char *into_buffer, int buffer_size) {
  socklen_t socklen = sizeof(struct sockaddr_in);

  // receive packet from socket
  int len;
  if ((len = recvfrom(socket->sockfd, into_buffer, buffer_size - 1, 0,
                      (struct sockaddr *)&socket->saddr, &socklen)) < 0)
    perror("Could not receive from socket");

  into_buffer[len] = 0;
  return len;
}

int socket_send(struct Socket *socket, const char *from_buffer, int send_size) {
  socklen_t socklen = sizeof(struct sockaddr_in);
  int len = sendto(socket->sockfd, from_buffer, send_size, 0,
                   (struct sockaddr *)&socket->saddr, socklen);
  return len;
}

#ifdef _NET_DEMO_RCVR
int main() {
  struct Socket *socket = new_socket(5007, "224.1.1.1");
  socket_receiver_bind(socket);

  char buffer[10240];
  socket_receive(socket, buffer, 10240);
  puts(buffer);

  delete_socket(socket);
}
#endif

#ifdef _NET_DEMO_SNDR
int main() {
  struct Socket *socket = new_socket(5007, "224.1.1.1");
  socket_sender_bind(socket);

  const char *text = "Hurray!!!";
  socket_send(socket, text, strlen(text));

  delete_socket(socket);
}
#endif
