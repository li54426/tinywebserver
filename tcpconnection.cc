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
void TcpConnection::send(string &message){
    if(state_ == kConnected){
        // 判断当前代码是否在事件循环所在的线程中运行。
        if(loop_ -> isInLoopThread()){
            sendInLoop(message.c_str(), message.size());
        }
    }
}


void TcpConnection:: sendInLoop(const void * data, size_t len){

}


void TcpConnection::shutdown(){

}
void TcpConnection::setTcpnodelay(bool on){

}

void TcpConnection::startRead(){

}
void TcpConnection::stopRead(){

}
bool TcpConnection::isReading(){

}

void TcpConnection::setConnectionCallback(ConnectionCallback &cb){
    connection_callback_ = cb;
}
void TcpConnection::setMessageCallback(MessageCallback &cb){
    message_callback_ = cb;
}

void TcpConnection::setWriteCompleteCallback(WriteCompleteCallback &cb){
    write_complete_callback_ = cb;
}
void TcpConnection::setCloseCallback(CloseCallback & cb){
    close_callback_ = cb;
}
void TcpConnection::setHighWaterMarkCallback(HighWaterMarkCallback &cb){
    high_water_mark_callback_ = cb;
}



void TcpConnection::handleRead(Timestamp timestamp){
    //

    loop_-> assertInLoopThread();

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
    loop_ ->assertInLoopThread();
    if(channel_->isWriting()){

    }
    int saved_error = 0;
    ssize_t n = output_buffer_.WriteFd(channel_->fd(), &saved_error);
    if(n>0){
        output_buffer_.Retrieve(n);

    }

}

Buffer* TcpConnection::inputBuffer(){
    return &input_buffer_;
}
Buffer* TcpConnection::outputBuffer(){
    return &output_buffer_;
}


