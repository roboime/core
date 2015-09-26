#include <stdio.h>
#include <string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>

#include "../build/grSim_Replacement.pb.h"
#include "../build/grSim_Packet.pb.h"
#include "../build/grSim_Commands.pb.h"
#include "../build/messages_robocup_ssl_wrapper.pb.h"
#include "../build/messages_robocup_ssl_geometry.pb.h"
#include "../build/messages_robocup_ssl_detection.pb.h"
#include "../build/messages_robocup_ssl_refbox_log.pb.h"
#include "../build/grSim_Packet.pb.h"
#include "../build/grSim_Commands.pb.h"

#define BUFFER_LENGTH 10240

struct Udp{
  struct sockaddr_in socketAddress_;
  struct ip_mreq grsimGroup_;
  int socketDescriptor_;
  socklen_t socketLength;

  Udp ();
  bool addToMembershipForMulticast (const char* address);
  bool bind (const uint16_t port);
  bool send (const char* output_text, int size);
  int listenMulticast (char* input_text);
};

Udp::Udp () {
  socketDescriptor_ = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (socketDescriptor_ < 0) {
    perror ("socket");
  }
  socketLength = sizeof (socketAddress_);
}

bool Udp::addToMembershipForMulticast (const char* address) {
  grsimGroup_.imr_multiaddr.s_addr = inet_addr (address); 
  int sd = setsockopt (socketDescriptor_, IPPROTO_IP, IP_ADD_MEMBERSHIP, &grsimGroup_, sizeof (grsimGroup_));
  if (sd < 0) {
    perror ("setsockopt()");
  }
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

bool Udp::send (const char* text, int size) {
  ssize_t sendingLength = sendto (socketDescriptor_, text, size, 0, (struct sockaddr*) &socketAddress_, socketLength);
  perror ("sendto()");
  if (sendingLength == -1) {
    return false;
  }
  return true;
}

int Udp::listenMulticast (char* input_text) {
  int recoveryLength = recvfrom (socketDescriptor_, input_text, BUFFER_LENGTH, 0, (struct sockaddr*) &socketAddress_, &socketLength);

  if (recoveryLength == -1) {
    perror ("recvfrom()");
  }
  return recoveryLength;
}

#ifdef RCVR
int main(){
  char text[10240];
  Udp receiver;
  SSL_WrapperPacket packet;
  receiver.addToMembershipForMulticast("224.5.23.2");
  receiver.bind(10020);

  while (1){
    int len = receiver.listenMulticast(text);
    packet.ParseFromArray(text, len);

    if (packet.has_detection()){
      for (int i=0; i<packet.detection().balls_size(); i++){
        SSL_DetectionBall ball = packet.detection().balls(i);
        printf ("-Ball (%2d/%2d): POS=<%9.2f, %9.2f>\n", i+1, packet.detection().balls_size(), ball.x(), ball.y());
      }
    }
  }
}
#endif

#ifdef SNDR
int main(){
  Udp sender;
  sender.socketAddress_.sin_family = AF_INET;
  sender.socketAddress_.sin_addr.s_addr = inet_addr("127.0.0.1");
  sender.socketAddress_.sin_port = htons(20011);


  grSim_Packet* sendingPacket = new grSim_Packet();
  grSim_Commands* commands = sendingPacket->mutable_commands();

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

  char* text = new char[sendingPacket->ByteSize()+1];
  sendingPacket->SerializeToArray(text, sendingPacket->ByteSize());

  while (1){
    sender.send(text, sendingPacket->ByteSize());
  }

  delete[] text;
  delete sendingPacket;
}
#endif
