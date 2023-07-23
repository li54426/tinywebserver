#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

class EventLoop;


#include<functional>

#include<memory>
#include<iostream>
#include<mutex>
#include"channel.h"


#include"log.h"


#include"inetaddress.h"
#include"buffer.h"

#include"socket.h"
#include"timestamp.h"


using std::function;


class TcpConnection;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;

using ConnectionCallback = function<void(TcpConnectionPtr &)>;
using CloseCallback  = function<void(TcpConnectionPtr &)>;
using WriteCompleteCallback = function<void(TcpConnectionPtr &)>;
using MessageCallback = function<void(const TcpConnectionPtr&, Buffer *, Timestamp)>;

using HighWaterMarkCallback = function<void(TcpConnectionPtr &, size_t )> ;

/*
* TcpServer => Acceptor => 又一个新用户连接, 通过 accept 拿到 connfd
* => TcpConnection 设置回调=> channel => Poller=> 调用channel的回调操作

*/
class TcpConnection : public std::enable_shared_from_this<TcpConnection>{
public:
    TcpConnection(EventLoop* loop, const string name, 
        int sockfd, const InetAddress &local_addr, 
        const InetAddress &peer_addr);
    ~TcpConnection() = default;

    EventLoop * getLoop()const {return loop_;}
    const string& name(){return name_;}
    const InetAddress& localAddress(){return local_addr_;}
    const InetAddress &peerAdddress(){return peer_addr_;}

    // 实际上就是链路的抽象
    void send(void * message, int len);
    void send(string &message);
    void shutdown();
    void setTcpnodelay(bool on);

    void startRead();
    void stopRead();
    bool isReading();

    void setConnectionCallback(ConnectionCallback &cb);
    void setMessageCallback(MessageCallback &cb);
    void setWriteCompleteCallback(WriteCompleteCallback &cb);


    void setCloseCallback(CloseCallback & cb);
    void setHighWaterMarkCallback(HighWaterMarkCallback & cb);

    Buffer* inputBuffer();
    Buffer* outputBuffer();

private:
    void handleRead(Timestamp);

    void handleWrite();
    void handleClose();
    void handleError();

    void sendInLoop(const void * data, size_t len);






private:
    const string name_;

    // 不是baseloop 而是一个 subloop
    EventLoop *loop_;

    // 有自己的端口号所以必须记录下来
    const InetAddress local_addr_;
    const InetAddress peer_addr_;  

    // 因为是链路的抽象, 所以完全拥有 channel 和 socket资源
    std::unique_ptr<Channel> channel_;
    std::unique_ptr<Socket> socket_;


    Buffer input_buffer_;
    Buffer output_buffer_;

    // ###################[Question]#######################
    // 为什么会有 connection_callback, 不用处理连接
    ConnectionCallback connection_callback_;
    MessageCallback message_callback_;
    WriteCompleteCallback write_complete_callback_;
    CloseCallback close_callback_;

    HighWaterMarkCallback high_water_mark_callback_;


    int high_water_mark_ ;

    enum StateE{
        kDisConnected, kConnecting, kConnected, kDisconnection
    };
    int state_;



    void setState(StateE state);

};
















#endif