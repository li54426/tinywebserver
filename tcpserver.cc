#include"tcpserver.h"



TcpServer ::TcpServer(EventLoop *loop, const InetAddress& listen_addr, const std::string &name, Option option ):
loop_(loop), ip_port_(listen_addr.toIpPort()), 
name_(name),
acceptor_(new Acceptor(loop, listen_addr, option == kReusePort)),
thread_pool_(new EventLoopThreadPool(loop, name_)),
connection_callback_(defaultConnectionCallback),
message_callback_(defaultMessageCallback),
next_conn_id_(1)
{
    acceptor_->setNewConnectionCallback(std::bind(
        &TcpServer::connection_callback_, this
    ));
}



TcpServer::~TcpServer(){
    loop_->assertInLoopThread();
    for(auto & item : connections_){
        TcpConnectionPtr conn(item.second);
        item.second.reset();
        conn-> getLoop()->runInLoop(std::bind(&TcpConnection::connectDestroyed, conn));
    }
}

void TcpServer::setNumThread(int num_thread){
    assert(num_thread > 0);
    thread_pool_->setThreadNum(num_thread);
}


void TcpServer::start(){
    thread_pool_ -> start(thread_init_callback_);

    // unique_ptr.get() 不会释放 unique_ptr 内部的指针。
    // 幸运的是, 生命周期不需要管
    // 添加到任务队列


    // 直接调用 acceptor_.listen()，则可能会引发线程安全问题。
    loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get() ) );
}




void TcpServer::newConnection(int sockfd, const InetAddress & peer_addr){
    loop_->assertInLoopThread();
    EventLoop *ioloop= thread_pool_->getNextLoop();
    char buf[64];
    snprintf(buf, sizeof buf, "-%s#%d", ip_port_.c_str(), next_conn_id_);
    ++next_conn_id_;
    string conn_name = name_ + buf;
    LOG_DEBUG("new connection from %s", peer);

    sockaddr_in local;
    memset(&local, 0, sizeof local);
    socklen_t  addrlen = sizeof local;
    if(::getsockname(sockfd, (sockaddr*)&local, &addrlen));
    InetAddress local_addr(local) ;

    TcpConnectionPtr conn ( new TcpConnection(
        ioloop,
        conn_name,
        sockfd,
        local_addr,
        peer_addr
    )  );



    connections_[conn_name] = conn;

    conn->setConnectionCallback(connection_callback_);
    conn-> setMessageCallback(message_callback_);
    conn->setWriteCompleteCallback(write_complete_callback_);
    conn-> setCloseCallback(std::bind(&TcpServer::removeConnection, this, placeholders::_1));
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn){
  loop_->runInLoop(std::bind(&TcpServer::removeConnectionInLoop, this, conn));
}