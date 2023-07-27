#include"thread.h"

std::atomic_int Thread::num_creat_ (0);


Thread::Thread(ThreadFunc func, string name ):func_(std::move(func)), name_(name), pid_(0)
    {
        if(name.empty()){
            setDefaultName();
        }

}

Thread::~Thread(){
    if(is_start_  && !is_join_){
        thread_->detach();
    }
}

// 开始运行线程, 也就是说, new thread 对象
void Thread::start(){
    lock_guard<mutex> locker (mtx_);
    thread_ = std::make_unique<thread>([this](){
        pid_ = pthread_self();
        // pid_= std::this_thread::get_id();
        func_();
    });
    
}

void Thread::join(){
    if (is_start_ && !is_join_) {
        is_join_ = true;
        thread_->join();
    }
}

bool Thread::isStart(){
    return is_start_;
}
bool Thread::isJoin(){
    return is_join_;
}

const string& Thread:: getName(){
    return name_;
}


void Thread::setDefaultName(){
    int num = ++num_creat_;
    name_ = "Thread"+ std::to_string(num_creat_); 
}
