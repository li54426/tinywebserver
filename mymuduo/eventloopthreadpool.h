#ifndef EVENT_LOOP_THREAD_POOL_H
#define EVENT_LOOP_THREAD_POOL_H

#include "eventloopthread.h"
#include<string>
#include<vector>
#include<memory>

#include<functional>
#include"eventloop.h"


class EventLoopThreadPool{
public:
    using ThreadInitCallback = std:: function<void(EventLoop*)> ;

    EventLoopThreadPool(EventLoop *base_loop, const std::string & name_arg);
    ~EventLoopThreadPool();
    void setThreadNum(int num_thread);

    void start(const ThreadInitCallback &cb);

    // 如果工作在多线程中,baseLoop_默认以轮询的方式分配channel给subloop
    EventLoop * getNextLoop();

    std::vector<EventLoop*> getAllLoops();


private:
    EventLoop * base_loop_;
    std::string name_;
    bool started_;
    int num_thread_;
    int next_;
    std::vector< std:: unique_ptr<EventLoopThread> > threads_;
    std::vector<EventLoop *> loops_;
};






#endif