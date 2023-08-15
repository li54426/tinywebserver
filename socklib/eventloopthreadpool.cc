#include"eventloopthreadpool.h"




EventLoopThreadPool::EventLoopThreadPool(EventLoop *base_loop, const std::string & name_arg):
base_loop_(base_loop),
name_(name_arg),
started_(false),
num_thread_(0),
next_(0)
{

}


EventLoopThreadPool::~EventLoopThreadPool() = default;

void EventLoopThreadPool::setThreadNum(int num_thread){
    num_thread_ = num_thread;
}

void EventLoopThreadPool::start(const ThreadInitCallback &cb){
    started_ = true;

    for(int i = 0; i<num_thread_; ++i){
        char buf[name_.size() + 32];
        snprintf(buf, sizeof buf, "%s%d", name_.c_str(), i);
        EventLoopThread *t = new EventLoopThread(cb, buf);
        threads_.push_back(std::unique_ptr<EventLoopThread>(t));

        // 开启 loops 循环
        loops_.push_back(t-> startLoop());
    }

    if(num_thread_ == 0 && cb){
        cb(base_loop_);
    }
}

// 如果工作在多线程中,baseLoop_默认以轮询的方式分配channel给subloop
EventLoop * EventLoopThreadPool::getNextLoop(){
    EventLoop * loop = base_loop_;
    if(loops_.size() ){
        loop = loops_[next_ ++];
        next_ %= num_thread_;
    }
    return loop;
}

std::vector<EventLoop*> EventLoopThreadPool::getAllLoops(){
    return loops_;
}