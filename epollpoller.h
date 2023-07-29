#ifndef EPOLLPOLLER_H
#define EPOLLPOLLER_H

#include"poller.h"

#include"channel.h"
#include"sys/epoll.h"
#include<vector>
// #include"timestamp.h"
#include"log.h"
#include<memory>
#include<assert.h>

/*
* epol1的使用
* epoll create 
* epoll ctl add/mod/del 
* epoll_wait
*/


class EpollPoller :public Poller{
public:
    EpollPoller(EventLoop*);
    ~EpollPoller() override;

     Timestamp poll(int timeoutMs, ChannelList * active_channels) override;
    void updateChannel(Channel * channel) override;
    void removeChannel(Channel * channel) override;


private:
    void fillActiveChannels(int num_event, ChannelList *activeChannels);
    void update(int operation , Channel *channel);


private:
    int epoll_fd_;

    static const int kInitEventListSize = 16;
    using EventList = std::vector<struct epoll_event>;

    EventList events_;
};




#endif