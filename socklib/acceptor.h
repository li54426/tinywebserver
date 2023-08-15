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
    ~Acceptor();
    void listen();
    bool listening()const;

    void setNewConnectionCallback(const NewConnectionCallback & cb);

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








#endif