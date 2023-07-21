#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include"socket.h"
#include"channel.h"
#include<unistd.h>
#include<fcntl.h>

#include<functional>

// 因为需要调用其成员函数, 所以只能 include一下
// class EventLoop;
#include"eventloop.h"


class Acceptor{
public:
    using NewConnectionCallback = std::function<void(int sockfd, const InetAddress & )>;

    Acceptor(EventLoop * loop, const InetAddress& listen_addr, bool reuseport);
    void listen();
    bool listening()const;

private:
    void handleRead();


private:
    EventLoop * loop_;

    Socket accept_socket_;
    Channel accept_channel_;
    bool listening_;
    NewConnectionCallback new_connection_callback_;

    int idleFd_;
    
};


// 因为 listen_addr 没有地方保存
// 直接在构造函数中 socket 进行 绑定 
Acceptor::Acceptor(EventLoop * loop, const InetAddress& listen_addr, bool reuseport):
loop_(loop), accept_socket_(), accept_channel_(loop, accept_socket_.fd()),
listening_(false), idleFd_(::open ("/dev/null", O_RDONLY | O_CLOEXEC))
{
    assert(idleFd_ > 0);
    //设置channel
    accept_channel_.setReadCallback(
        std::bind(&Acceptor::handleRead, this)
    );

    // 设置 socket 
    accept_socket_.bindAddress(listen_addr);

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

// ###################[Question]#######################
// void Acceptor::handleRead(){
// 为什么会有新连接建立的时候, 调用 new_connection_callback_(connfd, peer_addr);
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
        LOG_ERROR("%s", "connfd creat fail");
    }


}






#endif