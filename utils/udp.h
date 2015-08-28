#ifndef UDP_H
#define UDP_H

/*
 * Missing Documentation... to be done
 */

#include <stdio.h>
#include <string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#define BUFFER_LENGTH 512

class Udp{
  struct sockaddr_in socketAddress_;
  struct ip_mreq grsimGroup_;
  int socketDescriptor_;
  socklen_t socketLength;

public:
  Udp ();
  bool addToMembershipForMulticast (const char* address);
  bool bind (const uint16_t port);
  bool send (const char* output_text);
  bool listenMulticast (char* input_text);
};

#endif
