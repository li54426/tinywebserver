#include"socket.h"



int creatNonBlocking(){
    int fd =  socket(AF_INET, SOCK_STREAM| SOCK_NONBLOCK, 0);
    if(fd< 0){
        LOG_ERROR("%s", "creat socket error");
    }
    return fd;
}


Socket::Socket(int fd): fd_(fd){}


Socket::~Socket(){
    ::close(fd_);
}


int Socket::fd()const{
    return fd_;
}



void Socket::bindAddress(const InetAddress &addr){
    int ret = ::bind(fd_, addr.getSockAddr(), sizeof(sockaddr_in));
    if(ret< 0){
        LOG_ERROR("%s", "bind socket error");
    }
}

void Socket::listen(){
    int ret = ::listen(fd_, 1024);
    if(ret< 0){
        LOG_ERROR("%s", "listen socket error");
    }
}


int  Socket::accept(InetAddress *peeraddr){
    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    socklen_t len ;
    int connfd = ::accept(fd_, (sockaddr*)&addr, &len);
    peeraddr->setSockAddr(addr);

    if(connfd>0){
        LOG_INFO("%s= %d", "connect fd", connfd);
    }  
    return connfd;

}


void Socket::shutdown(){
    int ret = ::shutdown(fd_, SHUT_RD);
    if(ret<0){
        LOG_ERROR("%s", "shutdown error");
    }
}
