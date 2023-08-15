#ifndef EVENT_LOOP_THREAD_H
#define EVENT_LOOP_THREAD_H


#include<functional>
#include<mutex>
#include<condition_variable>
#include<string>


#include"eventloop.h"
#include"thread.h"

class EventLoop;


class EventLoopThread{
public:
    using ThreadInitCallback = std::function<void(EventLoop *)>;

    EventLoopThread(const ThreadInitCallback&cb = ThreadInitCallback(), 
        const std::string &name = std::string());
    ~EventLoopThread();
    EventLoop * startLoop();



private:
    void threadFunc();

private:
    EventLoop * loop_ ;//GUARDED_BY(mutex_);
    Thread thread_;
    bool exiting_;

    std::mutex mutex_;

    std::condition_variable cond_;

    ThreadInitCallback thread_init_callback_;



};








#endif