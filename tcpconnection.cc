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
    // channel_->setReadCallback([this](Timestamp timestamp) {
    //     handleRead(timestamp);
    // });

    channel_ -> setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_-> setCloseCallback(std::bind(&TcpConnection:: handleClose, this));
    channel_-> setErrorCallback(std::bind(&TcpConnection::handleError, this));
    socket_->setKeepAlive(true);
    LOG_DEBUG("connection ctor %d", sockfd);

}
// TcpConnection::~TcpConnection(){

// }


// 实际上就是链路的抽象
void TcpConnection::send(void * message, int len){
    
}
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

Buffer* TcpConnection::inputBuffer(){
    return &input_buffer_;
}
Buffer* TcpConnection::outputBuffer(){
    return &output_buffer_;
}


void TcpConnection::handleRead(Timestamp timestamp){
    //
    int saved_error = 0;
    ssize_t n = input_buffer_.ReadFd(channel_-> fd(), &saved_error);
    if(n> 0){
        // 已经建立链接的用户, 有可读事件发生了, 调用用户传入的 **回调函数**, onMessage
        message_callback_(shared_from_this(), &input_buffer_, timestamp);
    }
    else if( n == 0){
        handleClose();
    }
    else{
        errno = saved_error;
        LOG_ERROR("tcpconnection::handle");

    }
}


void TcpConnection::handleWrite(){
    int saved_error = 0;
    ssize_t n = output_buffer_.WriteFd(channel_->fd(), &saved_error);
    if(n>0){
        output_buffer_.Retrieve(n);

    }

}