
#ifndef THREAD_H

#define THREAD_H

#include<thread>
#include<memory>
#include<string> 
#include<functional>
#include<mutex>
#include<atomic>

using std::lock_guard;
using std::mutex;
using std::function;
using std::string;
using std::unique_ptr;
using std::thread;
// 可以 控制开始时间 的线程对象
class Thread{
public:
    using ThreadFunc = function<void()>;

    Thread(ThreadFunc, string name = string());

    ~Thread();

    // 开始运行线程, 也就是说, new thread 对象
    void start();

    void join();
    
    bool isStart();
    bool isJoin();
    const string& getName(); 


private:
    void setDefaultName();



private:
    unique_ptr<thread> thread_;
    string name_;
    int  pid_;
    
    // 肯定要存起来
    ThreadFunc func_;
    
    bool is_start_;
    bool is_join_;

    mutex mtx_;
    static std::atomic_int num_creat_;



};




#endif