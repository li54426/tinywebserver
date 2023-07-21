#include"eventloop.h"

#include <sys/eventfd.h>

__thread EventLoop *t_loop_in_this_thread = nullptr;


// 默认的poller io复用接口的超时时间
const int k_poller_time_ms = 1000;

int createEventfd(){
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
}