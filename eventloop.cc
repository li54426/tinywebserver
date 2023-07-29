#include"eventloop.h"
 #include"epollpoller.h"
#include<memory>
#include<algorithm>

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

 void EventLoop::assertInLoopThread(){
    if(!isInLoopThread()){
        LOG_FATAL("not in thread ");
    }
 }



EventLoop::EventLoop()
: looping_(false), quit_(false), calling_pending_functors_(false),
poller_(new EpollPoller(this)),
thread_id_(CurrentThread::tid() ),
wakeup_fd_(creatEventfd()),
wakeup_channel_(new Channel(this, wakeup_fd_) ),
current_active_channel_(nullptr)
{
    if(t_loop_in_this_thread){
        LOG_FATAL("eventloop created in this thread");
    }
    LOG_INFO("creat the eventloop");

    // #####################[Question]#########################
    // 唤醒的逻辑是什么
    // 唤醒 等待 poller_->poll()的 loop;
    wakeup_channel_->setReadCallback(std::bind(&EventLoop:: handleRead, this));

    wakeup_channel_->enableReading();
}


EventLoop :: ~EventLoop(){
    LOG_DEBUG("eventloop of thread %d dtor", thread_id_);
    t_loop_in_this_thread = nullptr;
}



void EventLoop::handleRead(){
    uint64_t one =1;
    ssize_t n = read(wakeup_fd_, &one, sizeof(one));

    if(n!= sizeof(one)){
        LOG_ERROR("EventLoop::handleRead() reads % d bytes of 8");
    }
}



// #####################[Question]#########################
// 为什么 会这样 不是还有 subloop么
// 没有判断 是否为 acceptor的事件
// 可能是因为 每个 eventloop 都有一个 poller 
// 所以就不需要判断
void EventLoop::loop(){
    assert(!looping_  );
    assertInLoopThread();
    looping_ = false;
    quit_ = false;
    LOG_DEBUG("eventloop of thread %d is looping", thread_id_);

    while(!quit_){
        active_channles_.clear();

        // 阻塞在这里
        poll_return_time_ = poller_->poll(kPollerTimes, &active_channles_);
        ++iteration_;

        event_handling_ =true;

        for(Channel *channel : active_channles_){
            current_active_channel_ = channel;
            // 通过这个总的接口, 实现r. w的回调
            current_active_channel_->handleEvent(poll_return_time_);

        }
        current_active_channel_ = nullptr;

        event_handling_ = false;

        // // #####################[Question]#########################
        // 执行当前EventLoop事件循环需要处理的回调操作
        /**
         * IO线程 mainLoop accept fd《=channel subloop 
         * mainLoop事先注册一个回调cb(需要subloop来执行)
         * 唤醒 sub loop 后, 执行 main loop注册的回调
         */
        doPendingFunctors();


    }

    looping_ = false;


}


void EventLoop::quit(){
    quit_ = true;
    // 如果是在其他 线程中, 调用的quit, 在一个 subloop中
    // 调用了mainloop的 quit
    if(!isInLoopThread()){
        wakeup();
    }
}


void EventLoop::runInLoop(Functor cb){
    if(isInLoopThread() ){
        cb();
    }

    else{
        queueInLoop(std::move(cb));
    }
}




void EventLoop::queueInLoop(Functor cb){
    {
        std:: unique_lock<std::mutex> locker(functors_mtx_);

        // 放入 回调函数的 vector 中
        pending_functors_.emplace_back(cb);

    }

    // 唤醒相应的, 需要执行上面回调操作的1oop的线程了
    // 正在执行 loop 的回调, 如果但是 loop 又来了新的回调
    if(!isInLoopThread() || calling_pending_functors_){
        wakeup();
    }
}


// 和 handleWrite 相反的, 肯定时其他线程调用该函数
void EventLoop::wakeup(){
    uint64_t one = 1;
    ssize_t n =  ::write(wakeup_fd_, &one, sizeof one);

    if(n != sizeof one){
        LOG_ERROR("EventLoop::handleRead() writes % d bytes of 8");
    }
}



void EventLoop::doPendingFunctors(){
    std::vector<Functor> functors;

    calling_pending_functors_ = true;
    {
        std::unique_lock<mutex> locker(functors_mtx_);
        functors.swap(pending_functors_);

    }

    for(auto & functor: functors){
        functor();
    }
    calling_pending_functors_ = false;
}




//----------------------------------------------------------

void EventLoop::updateChannel(Channel *channel){
    assert(channel -> ownerLoop() == this);
    assertInLoopThread();
    poller_-> updateChannel(channel);


}


void EventLoop::removeChannel(Channel * channel){
    assert(channel -> ownerLoop() == this);
    assertInLoopThread();
    if(event_handling_){
        // #####################[Question]#########################
        // 用于检查是否正在处理事件时，不应该等待事件完成就继续执行么，为什么需要 assert ()
        assert(current_active_channel_ == channel || std::find(active_channles_.begin(), 
            active_channles_.end(),  channel) == active_channles_.end() );
    }    
    poller_->removeChannel(channel);
}


bool EventLoop::hasChannel(Channel * channel){
    assert(channel-> ownerLoop() == this);
    assertInLoopThread();
    return poller_-> hasChannel(channel);


}