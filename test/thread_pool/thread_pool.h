#ifndef THREAD_POOL_H
#define THREAD_POOL_H


#include<queue>
#include<mutex>
#include<vector>
#include<thread>
#include<functional>
#include<condition_variable>
#include<iostream>
using std::queue;
using std::mutex;
using std::vector;
using std::function;
using std::lock_guard;
using std:: unique_lock;
using std:: thread;
using std::condition_variable;
using std::cout;

class ThreadPool{
public:
    ThreadPool(int thread_number=1, int max_request = 1024): thread_number_(thread_number), 
      max_request_(max_request){
        // 当对tasks_ 进行操作时, 就要加锁
        // unique_lock<mutex> locker(qu_mtx_);
        // locker.unlock();
        cout<< "start init"<< '\n'; 
        for( int i =0 ; i< thread_number_ ; ++i){
            workers_.emplace_back([this](){
                cout<< "the thread start"<< '\n';
                while(1){
                    std::function<void()> task;

                    {// 该层大括号是为了控制 locker的生命周期
                     // 因为, locker是用来保证 task_的线程安全
                        // if(tasks_.size() == 0){
                        //     return;
                        // }
                        unique_lock<mutex> locker(qu_mtx_);
                        // locker.lock();
                        con_var_.wait(locker, [this](){return  is_close|| tasks_.size();} );

                        if(is_close && tasks_.size() == 0){
                            return;
                        }
                        
                        task = std::move(tasks_.front() ) ;
                        tasks_.pop();
                        
                    }
                    task();

                }
            });
            
            //workers_[i].join();
            
        }
        cout<< "end init"<<'\n'; 
        
    }
    // 如何实现
    template<class F, class...Args>
    void AddTask(F&&f, Args &&...args){
        unique_lock<mutex>  locker(qu_mtx_);
        tasks_.emplace([f, args...](){
            f(args...); 
        });
        locker.unlock();
        con_var_.notify_one();
        cout<< "end add task"<< '\n';
    }

    ~ThreadPool(){
        // cout<< "xigou"<< '\n';
        {
            unique_lock<mutex> locker(qu_mtx_);
            is_close = true;
        }
        con_var_.notify_all();
        for(auto &worker: workers_){
            worker.join();
        }
        cout<< "end join"<< '\n';
    }

private:
    int max_request_;
    int thread_number_;
    bool is_close;
    mutex qu_mtx_;
    condition_variable con_var_;
    vector<thread> workers_;
    queue<function<void()> > tasks_;

};



















#endif