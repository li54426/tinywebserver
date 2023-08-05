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

using namespace std::placeholders;


// 最终向用户提供的接口
// 4 个设置回调函数 的借口
// 设置线程
// 开启监听 start(), 创建线程池
class TcpServer{
public:
      enum Option
        {
            kNoReusePort,
            kReusePort,
        };

    
    using ThreadInitCallback = std::function<void(EventLoop *)> ;
    using ConnectionMap = std::map<std::string,  TcpConnectionPtr> ;

    // 隐含着设置回调的过程
    TcpServer(EventLoop *, const InetAddress&, const std::string&, Option option = kNoReusePort);
    ~TcpServer();

    EventLoop *getLoop()const;


    void setConnectionCallback(const ConnectionCallback &cb);
    void setMessageCallback(const MessageCallback &cb);
    void setWriteCompleteCallback(const WriteCompleteCallback &cb);

    void setThreadInitCallback(const ThreadInitCallback &cb);

    void setNumThread(int numthread);

    // ###################[Question]#######################
    // 为什么要设置 返回线程池的函数
    std::shared_ptr<EventLoopThreadPool> threadPool();

    // 开启监听 start(), 创建线程池
    void start();
private:
    void newConnection(int sockfd, const InetAddress &peer_addr);

    void removeConnection(const TcpConnectionPtr &conn);

    // // 移除 sub loop 连接的函数。
    void removeConnectionInLoop(const TcpConnectionPtr &conn);




private:
    EventLoop *loop_;
    const std::string ip_port_;
    const std::string name_;

    ConnectionMap connections_;
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> thread_pool_;

    ConnectionCallback connection_callback_;
    MessageCallback message_callback_;
    WriteCompleteCallback write_complete_callback_;

    ThreadInitCallback thread_init_callback_;

    int next_conn_id_;







};





#endif