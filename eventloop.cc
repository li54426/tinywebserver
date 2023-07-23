#include"eventloop.h"

// 防止一个线程创建多个 EventLoop

__thread EventLoop *t_loop_in_this_thread = nullptr;

// 超时时间, 十秒
const int kPollerTimes = 10000;


int creatEventfd(){
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);

    if(evtfd < 0){
        LOG_FATAL("creat eventfd failed");
    }
    return evtfd;
}



bool EventLoop::isInLoopThread(){
    return thread_id_ == CurrentThread::tid();

}





EventLoop::EventLoop()
: looping_(false), quit_(false), calling_pending_functors_(false),
poller_(make_unique<EpollPoller>(this)),
thread_id_(CurrentThread::tid() ),
wakeup_fd_(creatEventfd()),
wakeup_channel_(make_unique<Channel>(this, wakeup_fd_)),
current_active_channel_(nullptr)
{
    if(t_loop_in_this_thread){
        LOG_FATAL("eventloop created in this thread");
    }
    LOG_INFO("creat the eventloop");
}