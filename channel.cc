#include"channel.h"

// 设置三个 感兴趣的事件
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd):
loop_(loop), fd_(fd), events_(0), revents_(0), index_(-1), addedToLoop_(false),
event_handing_(false)
{}

void Channel::tie(const std:: shared_ptr<void> & obj){
    tie_ = obj;
    tied_ = true;
}

const int Channel::fd(){
    return fd_;
}

// ------------------设置感兴趣的事件--------------
void Channel::enableReading(){
    events_ |= kReadEvent;
    update();
}

void Channel::disableReading(){
    events_ &= (~kReadEvent);
    update();
}

void Channel::enableWriting(){
    events_ |= (kWriteEvent);
    update();
}

void Channel::disableWriting(){
    events_ &= (~kWriteEvent);
    update();
}

void Channel::disableAll(){
    events_ = kNoneEvent;
    update();
}


void Channel::update(){
    addedToLoop_ = true;
    loop_->updateChannel(this);
}


void Channel::remove(){
    assert(isNoneEvent());
    addedToLoop_ = false;
    loop_->removeChannel(this);
}

bool Channel::isNoneEvent(){
    return kNoneEvent == events_;
}


int Channel::index(){
    return index_;
}

void Channel::setIndex(int index){
    index_ = index;
}


void Channel::set_revents(int events){
    revents_ = events;
}

bool Channel::isWriting()
{
    return events_ & kWriteEvent;
}

bool Channel::isReading()
{
    return events_ & kReadEvent;
}
void Channel::handleEvent(Timestamp receve_time){
    if(tied_){
        std::shared_ptr<void> guard =tie_.lock();
        if(guard){
            handleEventWithGuard(receve_time);
        }
    }
    else{
        handleEventWithGuard(receve_time);
    }
}


int Channel::events(){
    return events_;
}


void Channel::handleEventWithGuard(Timestamp receve_time){
    event_handing_ = true;
    if(events_ & POLLOUT){
        write_callback_();
    }

    if(events_ & (POLLIN | POLLPRI | POLLRDHUP)){
        read_callback_(receve_time);
    }
    if(revents_ & (POLLERR | POLLNVAL)){
        error_callback_();
    }
    event_handing_ = false;
}
