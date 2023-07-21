#include"tcpconnection.h"

using namespace std:: placeholders;
// 这个socketfd是哪来的
TcpConnection::TcpConnection(EventLoop* loop, const string name, 
    int sockfd, const InetAddress &local_addr, 
    const InetAddress &peer_addr):
    loop_(loop), socket_(make_unique<Socket>(sockfd)),
    channel_(make_unique<Channel>(loop, sockfd)),
    local_addr_(local_addr), peer_addr_(peer_addr),
    high_water_mark_(64 * 1024 * 1024)
{
    // 不存在从 "std::bind
    // <void (TcpConnection::(TcpConnection, std::Placeholder<1>))(Timestamp)>"
    // 到"Channel::ReadEventCallback" 的隐式转换。
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));



}
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