#include"poller.h"

Poller::Poller(EventLoop *loop):
loop_(loop)
{}


 Poller::~Poller() {
    loop_ = nullptr;
 }



bool Poller::hasChannel(Channel *channel)const{
    assertInLoopThread();
    auto it = channels_.find(channel-> fd());

    return it!= channels_.end() && it->second == channel;
}




void Poller::assertInLoopThread() const{
    loop_->assertInLoopThread();
}

// #include"epollpoller.h"

// Poller* Poller::newDefaultPoller(EventLoop *loop){
//     return new EpollPoller(loop);
// }