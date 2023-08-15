#ifndef POLLER_H
#define POLLER_H

#include<map>
#include<vector>
#include"channel.h"
#include"timestamp.h"


class EventLoop;
class Channel;




// 抽象类
class Poller{
public:
    using ChannelList = std::vector<Channel*>;

    Poller(EventLoop *);
    virtual ~Poller() ;

    virtual Timestamp poll(int timeoutMs, ChannelList *activeChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    bool hasChannel(Channel *channel) const;

    // static Poller * newDefaultPoller(EventLoop *);

    void assertInLoopThread()const;

protected:
    using ChannelMap = std::map<int, Channel*> ;
    ChannelMap channels_;

private:
    EventLoop *loop_;

};




#endif