#include"inetaddress.h"
// g++ test_addr.cc inetaddress.h -o test_addr
// ./test_addr


#include<iostream>
int main(){
    InetAddress inet(9000);
    std::cout<< inet.toIp()<< inet.toIpPort()<< inet.toPort()<< '\n';
    return 0;
}