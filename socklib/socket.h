#ifndef SOCKET_H
#define SOCKET_H



#include<sys/socket.h>
#include"log.h"
#include"inetaddress.h"
#include<unistd.h>
#include"netinet/tcp.h"



int creatNonBlocking();


class Socket{
public:
    Socket(int fd = creatNonBlocking())   ; 
    ~Socket();

    int fd()const;
    
    // socket 行为相关
    void bindAddress(const InetAddress &addr);
    void listen();
    int  accept(InetAddress *peeraddr);
    void shutdown();


    // socket 设置相关
    /// Enable/disable TCP_NODELAY (disable/enable Nagle's algorithm).
    void setTcpNoDelay(bool on);
    /// Enable/disable SO_REUSEADDR
    void setReuseAddr(bool on);
    /// Enable/disable SO_REUSEPORT
    void setReusePort(bool on);

    void setKeepAlive(bool on);


    void shutdownWrite();




private:
    const int fd_;


};






// const struct sockaddr* getSockAddr() const { return sockets::sockaddr_cast(&addr6_); }

// const struct sockaddr* sockets::sockaddr_cast(const struct sockaddr_in6* addr)
// {
//   return static_cast<const struct sockaddr*>(implicit_cast<const void*>(addr));
// }

// void setNonBlockAndCloseOnExec(int sockfd)
// {
//   // non-block
//   int flags = ::fcntl(sockfd, F_GETFL, 0);
//   flags |= O_NONBLOCK;
//   int ret = ::fcntl(sockfd, F_SETFL, flags);
//   // FIXME check

//   // close-on-exec
//   flags = ::fcntl(sockfd, F_GETFD, 0);
//   flags |= FD_CLOEXEC;
//   ret = ::fcntl(sockfd, F_SETFD, flags);
//   // FIXME check

//   (void)ret;
// }



// int sockets::createNonblockingOrDie(sa_family_t family)
// {
// #if VALGRIND
//   int sockfd = ::socket(family, SOCK_STREAM, IPPROTO_TCP);
//   if (sockfd < 0)
//   {
//     LOG_SYSFATAL << "sockets::createNonblockingOrDie";
//   }

//   setNonBlockAndCloseOnExec(sockfd);
// #else
//   int sockfd = ::socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
//   if (sockfd < 0)
//   {
//     LOG_SYSFATAL << "sockets::createNonblockingOrDie";
//   }
// #endif
//   return sockfd;
// }



#endif