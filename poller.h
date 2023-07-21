#ifndef POLLER_H
#define POLLER_H

#include<map>
#include<vector>
class EventLoop;

#include"channel.h"
class Channel;
#include"timestamp.h"


// 抽象类, 方法类
class Poller{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *);
    ~Poller();

    virtual Timestamp poll(int timeoutMs, ChannelList activeChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    virtual bool hasChannel(Channel *channel) const;

    static Poller * newDefaultPoller(EventLoop *);

    void assertInLoopThread()const;

protected:
    using ChannelMap = std::map<int, Channel*> ;
    ChannelMap channels_;

private:
    EventLoop *loop_;

};


Poller::Poller(EventLoop *loop):
loop_(loop)
{}

bool Poller::hasChannel(Channel *channel)const{
    assertInLoopThread();
    auto it = channels_.find(channel-> fd());

    return it!= channels_.end() && it->second == channel;
}


#endif