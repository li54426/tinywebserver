#include"eventloopthread.h"


EventLoopThread::EventLoopThread(const ThreadInitCallback&cb , 
        const std::string &name):
        loop_(nullptr),
        exiting_(false),
        thread_(std::bind(&EventLoopThread::threadFunc, this), name),
        mutex_(),
        cond_()
{

}

EventLoopThread::~EventLoopThread(){
    exiting_ = true;
    if(!loop_){
        loop_ -> quit();
        thread_.join();
    }
}


EventLoop * EventLoopThread::startLoop(){
    thread_.start();
    EventLoop * loop = nullptr;
    {
        std::unique_lock<mutex> locker(mutex_);
        while(loop_ == nullptr){
            cond_.wait(locker);
        }

    }
    return loop_;
}


// 默认的传入线程的函数
void  EventLoopThread::threadFunc(){
    // 创建一个 独立的 eventloop, 和线程一一对应
    EventLoop loop;
    if(thread_init_callback_){
        thread_init_callback_(&loop);
    }

    {
        std::unique_lock<mutex> locker(mutex_);
        loop_ = &loop;
        cond_.notify_one();

    }

    // 就进入 循环 了
    loop.loop();

    std::unique_lock<mutex> locker(mutex_);


}