
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
    explicit InetAddress(int port, string ip = "127.0.0.1");
    explicit InetAddress(InetAddress &) = default;

    struct sockaddr * getSockAddr();
    string toIp() const;
    string toIpPort()const;
    string toPort()const;

    void setSockAddr(sockaddr_in );

private:
    sockaddr_in addr_;
};
InetAddress:: InetAddress(int port, string ip){
    // std::cout<<ip<<'\n';
    memset(&addr_, 0, sizeof(addr_));
    // 初始化 addr_, 三个 sin
    // 字符串 和 int 都要经过函数转换
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = inet_addr(ip.c_str());
    addr_.sin_port = htons(port);

}

string InetAddress::toIp() const{
    char buff[64] ={};
    inet_ntop(AF_INET, &addr_.sin_addr, buff, sizeof(buff));
    return buff;
}
string InetAddress::toIpPort()const{
    char buff[64] ={};
    inet_ntop(AF_INET, &addr_.sin_addr, buff, sizeof(buff));
    int len = strlen(buff);
    int port =  ntohs(addr_.sin_port);
    sprintf(buff + len, ":%u", port);
    return buff;


}
string InetAddress::toPort()const{
    char buff[64];
    int a = ntohs(addr_.sin_port);
    return std::to_string(a);
}

struct sockaddr * InetAddress::getSockAddr(){
    return reinterpret_cast<sockaddr*>(&addr_);
}

void InetAddress::setSockAddr(sockaddr_in addr){
    addr_ = addr;
}

#endif