#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include<functional>
#include<atomic>
#include<vector>
#include<memory>
#include<mutex>
#include"log.h"
#include"channel.h"
// #include"defaultpoller.cc"
#include"timestamp.h"

#include"sys/eventfd.h"

#include"currentthread.h"


 #include"poller.h"
class Channel;
class Poller;


/**
 *              mainLoop
 * 
 *      no ==================== 生产者-消费者的线程安全的队列
 * 
 *  subLoop1     subLoop2     subLoop3
 */ 



class EventLoop{
public:
    using Functor = std::function<void()>;

    EventLoop();
    ~EventLoop();

    // 开启时间循环
    void loop();
    // 退出事件循环
    void quit();

    Timestamp pollerReturnTime()const{return poll_return_time_;}


    // #####################[Question]###################
    // 在当前loop中执行回调
    void runInLoop(Functor cb);
    // 将cb放入队列中, 唤醒 loop 所在的线程, 执行 cb
    // 用于将函数对象（回调函数）放入事件循环的任务队列中
    void queueInLoop(Functor cb);


    // 线程相关
    void assertInLoopThread();

    // 是不是 loop的这个线程
    bool isInLoopThread();



    // 唤醒 sub reactor 所在的线程
    void wakeup();
    
    // 修改eventloop中 poller 的方法
    // 为什么 用channel *
    // 需要传入的参数包括 fd, 以及 events
    // 直接将 channel* 传进去, 方便一些
    void updateChannel(Channel * );
    void removeChannel(Channel*);
    bool hasChannel(Channel*);






private:
// functions
    // wakeupfd 的 读操作
    void handleRead();


    // 执行回调
    void doPendingFunctors();



private:
    using ChannelList = std::vector<Channel*>;
    ChannelList active_channles_;
    Channel * current_active_channel_;

    std::atomic_bool looping_;
    std::atomic_bool quit_;
    std::atomic_bool has_callback_functors_;

    bool event_handling_;
    int64_t iteration_;

    // 记录 自己的 thread id
    const int thread_id_;
    
    // 返回 发生事件的时间点
    Timestamp poll_return_time_;
    std::unique_ptr <Poller> poller_;
    bool calling_pending_functors_;

    // 当mainloop 获取一个新用户的channel 通过轮询算法选择一个 subloop
    // 通过该成员 **唤醒** subloop 处理 channel
    // #####################[Question]#########################
    // wakeup_channel 要封装 wakeup_fd
    // 类型为 eventfd
    int wakeup_fd_; 
    std::unique_ptr<Channel> wakeup_channel_;

    // 存储loop所有需要执行的所有回调操作
    std::vector<Functor> pending_functors_;
    // 保护 上面对象的vector 线程安全
    std::mutex functors_mtx_; 
    
};




#endif