
#ifndef CHANNEL_H

#define CHANNEL_H

#include<functional>

//class Channel;
class EventLoop;
class Timestamp;
// Channel 的意思是通道
// 封装了 sockfd 以及其感兴趣的事件, 如 EPOLLIN, EPOLLOUT等
// 还绑定了poller返回的具体事件
// 一个 EventLoop 可以有很多个channel;
class Channel{
public:
    using EventCallback = std::function<void()> ;
    using ReadEventCallback = std::function<void(Timestamp)>;
    Channel(EventLoop *loop, int fd);
    ~Channel();

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

    // one loop per thread;
    EventLoop *ownerLoop(){return loop_; };
    void remove();

private:
    static const int k_none_event_;
    static const int k_read_event_;
    static const int k_write_event;

    EventLoop *loop_;
    const int fd_;
    int events;
    int revents_;
    int index_;

    // 向 poller 进行 更新
    void update();


    ReadEventCallback read_callback_;
    EventCallback write_callback_;
    EventCallback close_callback_;
    EventCallback error_callback_;


};



Channel::Channel(EventLoop* loop, int fd):
loop_(loop), fd_(fd), events(0), revents_(0), index_(-1){}






#endif
