#include "udp.h"

Udp::Udp () {
  socketDescriptor_ = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  perror ("socket");
  socketLength = sizeof (socketAddress_);
}

bool Udp::addToMembershipForMulticast (const char* address) {
  grsimGroup_.imr_multiaddr.s_addr = inet_addr (address); 
  int sd = setsockopt (socketDescriptor_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &grsimGroup_, sizeof (grsimGroup_));
  perror ("setsockopt()");
  if (sd == -1) {
    return false;
  }
  return true;
}

bool Udp::bind (const uint16_t port) {
  memset ((char*) &socketAddress_, 0, sizeof (socketAddress_));

  socketAddress_.sin_family = AF_INET;
  socketAddress_.sin_port = htons (port);
  socketAddress_.sin_addr.s_addr = INADDR_ANY;

  int bindingState = ::bind(socketDescriptor_, (struct sockaddr*) &socketAddress_, sizeof (socketAddress_));
  perror ("bind");
  if (bindingState == -1) {
    return false;
  }
  return true;
}

bool Udp::send (const char* text) {
  ssize_t sendingLength = sendto (socketDescriptor_, text, strlen (text), 0, (struct sockaddr*) &socketAddress_, socketLength);
  perror ("sendto()");
  if (sendingLength == -1) {
    return false;
  }
  return true;
}

bool Udp::listenMulticast (char* input_text) {

  ssize_t recoveryLength = recvfrom (socketDescriptor_, input_text, BUFFER_LENGTH, 0, (struct sockaddr*) &socketAddress_, &socketLength);
  perror ("recvfrom()");

  if (recoveryLength == -1) {
    return false;
  }
  return true;
}
