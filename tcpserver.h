#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include"eventloop.h"

#include"acceptor.h"

#include"tcpconnection.h"
#include"eventloopthreadpool.h"
#include "callbacks.h"
#include"callbacks.h"
#include"inetaddress.h"

#include"log.h"


#include<string>
#include <functional>
#include<memory>
#include<map>



class TcpServer{
public:
      enum Option
        {
            kNoReusePort,
            kReusePort,
        };

    
    using ThreadInitCallback = std::function<void(EventLoop *)> ;
    using ConnectionMap = std::map<std::string,  TcpConnectionPtr> ;

    TcpServer(EventLoop *, const InetAddress&, const std::string&, Option option = kNoReusePort);
    ~TcpServer();


    void setConnectionCallback(const ConnectionCallback &cb);
    void setMessageCallback(const MessageCallback &cb);
    void setWriteCompleteCallback(const WriteCompleteCallback &cb);

    void setThreadInitCallback(const ThreadInitCallback &cb);

    void setNumThread(int numthread);


    void start();
private:
    void newConnection(int sockfd, const InetAddress &peer_addr);

    void removeConnection(const TcpConnectionPtr &conn);

    void removeConnectionInLoop(const TcpConnectionPtr &conn);




private:
    EventLoop *loop_;
    const std::string ip_port_;
    const std::string name_;

    ConnectionMap connections_;
    std::unique_ptr<Acceptor> acceptor_;
    std::unique_ptr<EventLoopThreadPool> thread_pool_;

    ConnectionCallback connection_callback_;
    MessageCallback message_callback_;
    WriteCompleteCallback write_complete_callback_;

    ThreadInitCallback thread_init_callback_;

    int next_conn_id_;







};





#endif