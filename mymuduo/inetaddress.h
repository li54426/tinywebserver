
#ifndef INETADDR
#define INETADDR

#include<netinet/in.h>
#include<arpa/inet.h>
#include<string>

#include<cstring>
using std::string;

#include<iostream>
class InetAddress{
public:
    explicit InetAddress(int port = 0, string ip = "127.0.0.1");
    explicit InetAddress(const InetAddress &) = default;
    explicit InetAddress(const struct sockaddr_in& addr);


    struct sockaddr * getSockAddr()const;
    string toIp() const;
    string toIpPort()const;
    string toPort()const;

    void setSockAddr(sockaddr_in );

private:
    sockaddr_in addr_;
};



#endif