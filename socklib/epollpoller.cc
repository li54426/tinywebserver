// #include"poller.h"
#include"epollpoller.h"


// 状态常量定义
//  channel 未添加到 poller
const int kNew = -1;
// channel 添加到 了 poller中
const int kAdded = 1;
// 从channel 中删除
const int kDeleted = 2;


EpollPoller::EpollPoller(EventLoop * loop):
Poller(loop),
epoll_fd_(epoll_create1(EPOLL_CLOEXEC)),
events_(kInitEventListSize)
{
    if(epoll_fd_ < 0){
        LOG_ERROR("%s", "creat eppoll fail");
    }
}


EpollPoller::~EpollPoller(){
    ::close(epoll_fd_);
}


Timestamp EpollPoller::poll(int timeoutMs, ChannelList * active_channels){
    int num_event = epoll_wait(epoll_fd_, 
                                &*events_.begin(), 
                                static_cast<int> (events_.size() ) , 
                                timeoutMs);
    int saved_error = errno;
    Timestamp now (Timestamp::now());
    if(num_event > 0){
        fillActiveChannels(num_event, active_channels);
    }

    if((size_t)(num_event) == events_.size()){
        events_.resize(events_.size() * 2);
    }
    else if(num_event == 0){
        // 没有时间发生
    }
    else {
        // 发生错误
        //  EINTR  The  call  was  interrupted  by  a signal handler before either (1) any of the requested
        // events occurred or (2) the timeout expired; see signal(7).
        // 中断错误
        if(saved_error != EINTR){
            LOG_ERROR("%s %d", "epoll error, and the error number=", errno);
            errno = saved_error;
        }
    }
    return now;
}

void EpollPoller:: fillActiveChannels(int num_event, ChannelList *active_channels){
    assert((size_t) num_event <= events_.size());
    for(int i = 0; i<num_event; ++i){
        Channel *channel = static_cast<Channel*> (events_[i].data.ptr);
        int fd = channel ->fd();
        LOG_DEBUG("%s %d", "poll the fd=", fd);

        channel-> set_revents(events_[i].events);
        active_channels-> push_back(channel);
    }
}


void EpollPoller::updateChannel(Channel * channel) {
    Poller::assertInLoopThread();
    const int index = channel-> index();
    if(index == kNew || index  == kDeleted){
        int fd = channel-> fd();
        if(index == kNew){
            assert(channels_.find(fd) == channels_.end() );
            channels_[fd] = channel;
        }
        else{
            assert(channels_.find(fd) == channels_.end() );
            assert(channels_[fd] == channel);
        }
        // 添加到epoll
        update(EPOLL_CTL_ADD, channel);

    }
    else{
        // 已经存在, 则更改他的 关注的事件 状态
    }

}




void EpollPoller::removeChannel(Channel * channel) {
    assertInLoopThread();

    int fd = channel-> fd();
    channels_.erase(fd);

    // 判断是否合法
    assert(channels_.find(fd) != channels_.end());
    assert(channels_[fd] == channel);
    

    int index = channel-> index();
    assert(index == kAdded || index == kDeleted);
    if(index  == kAdded){
        update(EPOLL_CTL_DEL, channel);
    }
    channel-> setIndex(kNew);




}

void EpollPoller::update(int operation , Channel *channel){
    epoll_event event;
    memset(&event, 0, sizeof(event));
    event.events = channel-> events();
    event.data.ptr = channel;
    int fd = channel-> fd();

    if(::epoll_ctl(epoll_fd_, operation,fd, &event ) < 0){
        if(operation == EPOLL_CTL_DEL){
            LOG_ERROR("%s", "epoll_ctl error");
        }
        else{
            LOG_FATAL("%s", "epoll_ctl error");
        }
        
    }

}
