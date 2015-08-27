#include "udp.h"

Udp::Udp(){
  socketState = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  socketLength = sizeof(socketOther);
  perror("socket");
}

bool Udp::binding(uint16_t port){
  memset((char*) &socketMe, 0, sizeof(socketMe));

  socketMe.sin_family = AF_INET;
  socketMe.sin_port = htons(port);
  socketMe.sin_addr.s_addr = htonl(INADDR_ANY);

  bindingState = bind(socketState, (struct sockaddr*) &socketMe, sizeof(socketMe));
  perror("bind");
  if (bindingState == -1){
    return false;
  }
  return true;
}

bool Udp::send(const char* text){
  socketOther.sin_family = socketMe.sin_family;
  socketOther.sin_port = socketMe.sin_port;
  socketOther.sin_addr.s_addr = socketMe.sin_addr.s_addr;
  ssize_t sendingLength = sendto(socketState, text, strlen(text)+1, 0, (struct sockaddr*) &socketOther, socketLength);
  perror("sendto()");
  if (sendingLength == -1){
    return false;
  }
  return true;
}

bool Udp::listen (char* input_text, bool broadcast = false){
  printf ("Waiting...");
  fflush(stdout);

  if (broadcast){
    setsockopt(socketState, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof (broadcast));
  }

  ssize_t recoveryLength = recvfrom(socketState, input_text, BUFFER_LENGTH, 0, (struct sockaddr*) &socketOther, &socketLength);
  perror("recvfrom()");

  if (recoveryLength == -1){
    return false;
  }
  return true;
}
