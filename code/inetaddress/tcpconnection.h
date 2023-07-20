#ifndef TCPCONNECTION_h
#define TCPCONNECTION_H

class EventLoop;


#include<functional>
using std::function;
#include<memory>
#include<iostream>
#include<mutex>
#include"../channel/channel.h""


using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

using ConnectionCallback = function<void(TcpConnectionPtr &)>;
using CloseCallback  = function<void(TcpConnectionPtr &)>;
using WriteCompleteCallback = function<void(TcpConnectionPtr &)>;
using MessageCallback = function<void(const TcpConnectionPtr&, Buffer *, timestamp)>;





#include"inetaddress.h"
#include"buffer.h"

#include"socket.h"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(EventLoop* loop, const string name, int sockfd, const InetAddress &local_addr, 
        const InetAddress &peer_addr);
    ~TcpConnection();

    EventLoop * getLoop()const {return loop_;}
    const string& name(){return name_;}
    const InetAddress& localAddress(){return local_addr_;}
    const InetAddress &peerAdddress(){return peer_addr_;}

    // 实际上就是链路的抽象
    void send(void * message);
    void send(string &message);
    void shutdown();
    void setTcpnodelay(bool on);

    void startRead();
    void stopRead();
    bool isReading();

    void setConnectionCallback(ConnectionCallback &cb);
    void setMessageCallback(ConnectionCallback &cb);
    void setWriteCompleteCallback(WriteCompleteCallback &cb);
    void setCloseCallback(CloseCallback & cb);
    void setHighWaterMarkCallback();

    Buffer* inputBuffer();
    Buffer* outputBuffer();

private:
    void handleRead(Timestamp);




private:
    const string name_;

    // 不是baseloop 而是一个 subloop
    EventLoop *loop_;

    // 有自己的端口号所以必须记录下来
    const InetAddress local_addr_;
    const InetAddress peer_addr_;  

    std::unique_ptr<Channel> channel_;
    std::unique_ptr<Socket> socket_;


    Buffer input_buffer_;
    Buffer output_buffer_;

};
















#endif