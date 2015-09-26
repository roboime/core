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
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "../build/grSim_Replacement.pb.h"
#include "../build/grSim_Packet.pb.h"
#include "../build/grSim_Commands.pb.h"
#include "../build/messages_robocup_ssl_wrapper.pb.h"
#include "../build/messages_robocup_ssl_geometry.pb.h"
#include "../build/messages_robocup_ssl_detection.pb.h"
#include "../build/messages_robocup_ssl_refbox_log.pb.h"
#include "../build/grSim_Packet.pb.h"
#include "../build/grSim_Commands.pb.h"

using namespace std;

static const unsigned int ONE = 1;
static const unsigned char TTL = 3;

struct Socket {
  int sockfd;
  struct sockaddr_in saddr_;
  struct ip_mreq mreq;
};

struct Socket *new_socket_iface(int port, const char *addr, const char *iface) {
  struct Socket *i = (struct Socket *)calloc(1, sizeof(struct Socket *));

  // open a UDP socket
  if ((i->sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP)) < 0)
    perror("Could not open socket file descriptor");

  i->saddr_.sin_family = PF_INET;
  i->saddr_.sin_port = htons(port);

  /*
#define OR_ANY(ADDR) (strlen(ADDR) ? inet_addr(ADDR) : htonl(INADDR_ANY));
  // bind socket to the multicast address if present
  i->saddr.sin_addr.s_addr = OR_ANY(addr);

  i->mreq.imr_multiaddr.s_addr = inet_addr(addr);
  i->mreq.imr_interface.s_addr = OR_ANY(iface);
#undef OR_ANY
*/

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

  //free(socket);
}

bool socket_receiver_bind(struct Socket *socket) {
  // enable address reuse
  if (setsockopt(socket->sockfd, SOL_SOCKET, SO_REUSEADDR, &ONE, sizeof(ONE)) < 0) {
    perror("Could not enable address reuse");
    return false;
  }

  // bind to interface
  if (bind(socket->sockfd, (struct sockaddr *)&socket->saddr_, sizeof(socket->saddr_)) < 0) {
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
  saddr.sin_family = AF_INET;
  saddr.sin_port = htons(0);                 // Use the first free port
  saddr.sin_addr.s_addr = htonl(INADDR_ANY); // bind socket to any address

  if (bind(socket->sockfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in)) <
      0) {
    perror("Error binding socket to interface");
    return false;
  }

  /*
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

  */
  return true;
}

int socket_receive(struct Socket *socket, char *into_buffer, int buffer_size) {
  socklen_t socklen = sizeof(struct sockaddr_in);

  // receive packet from socket
  int len;
  if ((len = recvfrom(socket->sockfd, into_buffer, buffer_size - 1, 0,
                      (struct sockaddr *)&socket->saddr_, &socklen)) < 0)
    perror("Could not receive from socket");

  into_buffer[len] = 0;
  return len;
}

int socket_send(struct Socket *socket, const char *from_buffer, int send_size) {
  socklen_t socklen = sizeof(struct sockaddr_in);
  int len = sendto(socket->sockfd, from_buffer, send_size, 0,
                   (struct sockaddr *)&socket->saddr_, socklen);
  return len;
}

#ifdef RCVR
int main() {
  struct Socket *socket = new_socket(10020, "224.5.23.2");
  socket_receiver_bind(socket);
  SSL_WrapperPacket packet;
  int len;
  char buffer[10240];

  while (1){
    len = socket_receive(socket, buffer, 10240);

    packet.ParseFromArray(buffer, len);

    if (packet.has_detection()){
      for (int i=0; i<packet.detection().balls_size(); i++){
        SSL_DetectionBall ball = packet.detection().balls(i);
        printf ("-Ball (%2d/%2d): POS=<%9.2f, %9.2f>\n", i+1, packet.detection().balls_size(), ball.x(), ball.y());
      }
    }
  }

  delete_socket(socket);
}
#endif

#ifdef SNDR
int main() {
  struct Socket *socket = new_socket(20011, "192.168.1.118");
  //socket_sender_bind(socket);

  grSim_Packet* packet = new grSim_Packet();
  grSim_Commands* commands = packet->mutable_commands();

  commands->set_isteamyellow(true);
  commands->set_timestamp(0.0);

  grSim_Robot_Command* command = commands->add_robot_commands();

  command->set_id(1);
  command->set_kickspeedx(1);
  command->set_spinner(false);
  command->set_kickspeedz(0.0);
  command->set_veltangent(0.0);
  command->set_velnormal(2.0);
  command->set_velangular(0.0);
  command->set_wheelsspeed(true);
  command->set_wheel1(1.0);
  command->set_wheel2(1.0);
  command->set_wheel3(1.0);
  command->set_wheel4(1.0);

  char *text = new char[packet->ByteSize()];
  packet->SerializeToArray(text, packet->ByteSize());

  while (1){
    socket_send(socket, text, strlen(text));
  }

  delete[] text;
  delete packet;
  delete_socket(socket);
}
#endif
