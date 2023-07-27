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
    sendInLoop(static_cast<const void *>(message), (size_t)len);
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
    loop_->assertInLoopThread();
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool fault_error = false;
    if(state_ == kDisConnected){
        LOG_ERROR("disconnected");
        return ;
    }

    // 如果输出队列为空且写缓冲区中没有待发送的数据，尝试直接写入套接字。
    // 如果写入成功，则更新已写入字节数 nwrote，计算剩余字节数 remaining，并检查是否所有数据都已写入完毕。
    // 如果是，则调用 writeCompleteCallback_回调函数。
    if(!channel_-> isWriting() && output_buffer_.ReadableBytes() == 0){
        nwrote = ::write(channel_->fd(), data, len);

        if(nwrote >= 0){
            remaining = len - nwrote;
            if(remaining == 0 && write_complete_callback_){
                loop_-> queueInLoop(std::bind(write_complete_callback_, shared_from_this()));
            }
        }

        else{
            nwrote = 0;
            // 被阻塞
            if(errno != EWOULDBLOCK){
                LOG_ERROR("tcpconn::sendInLoop");
                if(errno == EPIPE ||errno == ECONNRESET){
                    fault_error = true;
                }
            }

        }
    }

    assert(remaining <= len);
    if(!fault_error && remaining > 0){
        size_t old_len = output_buffer_.ReadableBytes();
        if(old_len + remaining >= high_water_mark_ && high_water_mark_callback_){
            loop_->queueInLoop(std::bind(high_water_mark_callback_, shared_from_this(), old_len));
            
        }
        output_buffer_.Append(static_cast<const char *>(data) + nwrote, remaining);
        if(!channel_->isWriting()){
            // 数据还没有写完
            channel_ -> enableWriting();
        }
    }
}

// ssize_t sockets::write(int sockfd, const void *buf, size_t count)
// {
//   return ::write(sockfd, buf, count);
// }





void TcpConnection::shutdown(){
    if(state_ == kConnected){
        setState(kDisconnecting);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}


void TcpConnection::shutdownInLoop(){
    loop_ -> assertInLoopThread();
    if(!channel_->isWriting()){
        socket_->shutdownWrite();
    }
}

void TcpConnection::setTcpnodelay(bool on){
    socket_->setTcpNoDelay(on);
}

void TcpConnection::startRead(){
    loop_-> runInLoop(std::bind(&TcpConnection::startReadInLoop, this));
}


void TcpConnection::startReadInLoop()
{
    loop_->assertInLoopThread();
    if(!reading_ || !channel_->isReading()){
        channel_-> enableReading();
        reading_ = true;

    }
}

void TcpConnection::stopReadInLoop()
{
    loop_->assertInLoopThread();
    if(reading_ || channel_-> isReading()){
        channel_->disableReading();
        reading_ = false;
    }
}

void TcpConnection::stopRead(){
    loop_->assertInLoopThread();
    if(reading_ || channel_-> isReading()){
        channel_->disableReading();
        reading_ = false;
    }
}
bool TcpConnection::isReading(){
    return reading_;
}

void TcpConnection::setConnectionCallback(const ConnectionCallback &cb){
    connection_callback_ = cb;
}
void TcpConnection::setMessageCallback(const MessageCallback &cb){
    message_callback_ = cb;
}

void TcpConnection::setWriteCompleteCallback(const WriteCompleteCallback &cb){
    write_complete_callback_ = cb;
}
void TcpConnection::setCloseCallback(const CloseCallback & cb){
    close_callback_ = cb;
}
void TcpConnection::setHighWaterMarkCallback(const HighWaterMarkCallback &cb){
    high_water_mark_callback_ = cb;
}

void TcpConnection::connectEstablished()
{
    loop_->assertInLoopThread();
    assert(state_ == kDisconnecting);
    setState(kConnected);
    // tie
    channel_->tie(shared_from_this());
    channel_->enableReading();

    connection_callback_(shared_from_this());
}

void TcpConnection::connectDestroyed()
{
    loop_->assertInLoopThread();
    if(state_ == kConnected){
        setState(kDisConnected);
        channel_->disableAll();
        connection_callback_ (shared_from_this());
    }
    channel_->remove();
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

        if(output_buffer_.ReadableBytes()== 0){
            channel_->disableWriting();

            if(write_complete_callback_){
                loop_->queueInLoop(std::bind(write_complete_callback_, shared_from_this()));
            }

            if(state_ == kDisconnecting){
                shutdownInLoop();
            }
        }
    }

}

void TcpConnection::handleClose()
{
    loop_->assertInLoopThread();

    setState(kDisConnected);
    channel_-> disableAll();

    assert(state_ == kDisConnected || state_ == kDisconnecting );
    TcpConnectionPtr guard_this(shared_from_this());
    close_callback_(guard_this);
}

void TcpConnection::handleError()
{
    int err = getSocketError(socket_->fd());

    LOG_ERROR("tcp conn %s  handle error", name_)//,  strerror_r(err, t_errnobuf, sizeof t_errnobuf) );
}


int getSocketError(int sockfd)
{
  int optval;
  socklen_t optlen = static_cast<socklen_t>(sizeof optval);

  if (::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
  {
    return errno;
  }
  else
  {
    return optval;
  }
}



Buffer* TcpConnection::inputBuffer(){
    return &input_buffer_;
}
Buffer* TcpConnection::outputBuffer(){
    return &output_buffer_;
}


