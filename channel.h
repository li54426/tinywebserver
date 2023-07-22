
#ifndef CHANNEL_H

#define CHANNEL_H


#include<sys/poll.h>
#include<functional>

//class Channel;
class EventLoop;
#include"timestamp.h"
//class Timestamp;
// Channel 的意思是通道
// 封装了 sockfd 以及其感兴趣的事件, 如 EPOLLIN, EPOLLOUT等
// 还绑定了poller返回的具体事件
// 一个 EventLoop 可以有很多个channel;
// Channel 类负责将底层的事件（如套接字的可读 / 可写事件）**转发** 给相应的回调函数进行处理
class Channel{
public:
    using EventCallback = std::function<void()> ;
    using ReadEventCallback = std::function<void(Timestamp)>;
    Channel(EventLoop *loop, int fd);
    ~Channel();

    const int fd();

    //void set;
    void setReadCallback(ReadEventCallback cb) {
        read_callback_ = std::move(cb);
    }
    void setWriteCallback(EventCallback cb){
        write_callback_ = std::move(cb);
    }
    void setCloseCallback(EventCallback cb){
        close_callback_ = std::move(cb);
    }

    void setErrorCallbak(EventCallback cb){
        error_callback_= std::move(cb);
    }

    // one loop per thread;
    EventLoop *ownerLoop(){return loop_; };
    void remove();
    
    void enableReading();
    void disableReading();

    
    int events();
    void set_revents(int );



    int index();
    void setIndex(int index);

    void handleEvent(Timestamp);

private:
    // 向 poller 进行 更新
    // 因为不含 poller , 所以需要 loop 进行调用
    void update();
    void handleEventWithGuard(Timestamp timestamp);


private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop *loop_;
    const int fd_;

    // 感兴趣的事件
    int events_;
    int revents_;
    // channel的状态, 是已经注册到epoll中还是没有添加, 又或者删除了
    int index_;


    // 需要调用的时候, 就 a.read_callback_();
    // 修正: private 
    ReadEventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;
    EventCallback error_callback_;


};



// 设置三个 感兴趣的事件
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd):
loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1){}



const int Channel::fd(){
    return fd_;
}


void Channel::enableReading(){
    events_ |= kReadEvent;
    update();
}

void Channel::disableReading(){
    events_ &= (~kReadEvent);
    update();
}

int Channel::index(){
    return index_;
}

void Channel::setIndex(int index){
    index_ = index;
}


void Channel::set_revents(int events){
    revents_ = events;
}


void Channel::handleEvent(Timestamp timestamp){

}

void Channel::handleEventWithGuard(Timestamp receve_time){

    if(events_ & POLLOUT){
        write_callback_();
    }

    if(events_ & (POLLIN | POLLPRI | POLLRDHUP)){
        read_callback_(receve_time);
    }
    if(revents_ & (POLLERR | POLLNVAL)){
        error_callback_();
    }
}

#endif
