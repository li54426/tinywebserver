#include"acceptor.h"
// 因为 listen_addr 没有地方保存
// 直接在构造函数中 socket 进行 绑定 
Acceptor::Acceptor(EventLoop * loop, const InetAddress& listen_addr, bool reuseport):
loop_(loop), accept_socket_(), accept_channel_(loop, accept_socket_.fd()),
listening_(false), idleFd_(::open ("/dev/null", O_RDONLY | O_CLOEXEC))
{
    assert(idleFd_ > 0);
    // 设置 channel, 因为 检测到 连接也是一个事件
    // 有读事件发生 <=> 有客户端连接
    accept_channel_.setReadCallback(
        std::bind(&Acceptor::handleRead, this)
    );

    // 设置 socket 
    accept_socket_.bindAddress(listen_addr);

}


Acceptor::~Acceptor(){
    accept_channel_.disableAll();
    accept_channel_.remove();
    ::close(idleFd_);
}


void Acceptor::listen(){
    // 需要引入 eventloop 头文件
    loop_->assertInLoopThread();
    listening_ = true;
    accept_socket_.listen();
    accept_channel_.enableReading();
}


bool Acceptor::listening()const{
    return listening_;
}



void Acceptor::setNewConnectionCallback(const NewConnectionCallback & cb){
    new_connection_callback_ = std::move(cb);
}


// ###################[Finished]#######################
// ###################[Question]#######################
// void Acceptor::handleRead(){
// 为什么会有新连接建立的时候, 调用 new_connection_callback_(connfd, peer_addr);
// 为什么又加了一层封装, (handleread 封装 用户传入的 自定义fun )
// 让用户只用关注连接成功做什么, 进行异常判断的逻辑交给库的设计人员
void Acceptor::handleRead(){
    loop_->assertInLoopThread();
    InetAddress peer_addr;
    int connfd = accept_socket_.accept(&peer_addr);
    if(connfd > 0){
        if(new_connection_callback_){
            new_connection_callback_(connfd, peer_addr);
        }
        else{
            close(connfd);
        }
    }
    else{
        LOG_DEBUG("%s%d", "connfd creat fail", connfd);
    }


}
