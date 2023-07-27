#include"blockqueue.h"

template<class T>
bool BlockQueue<T>::pop(T &a){
    unique_lock<mutex> locker(mtx_);

    if(qu_.size() == 0){
        conCon_.wait(locker);
        if(isClose_){
            return false;
        }
    }

    conPro_.notify_one();
    a =  qu_.front();
    qu_.pop();
    return true;
}

template<class T>
bool BlockQueue<T>::pop(T &a, int timeout){
    unique_lock<mutex> locker(mtx_);

    if(qu_.size() == 0){
        if(conCon_.wait_for(locker, std::chrono::seconds(timeout) ) == std::cv_status::timeout) {
            return false;
        }
        if(isClose_){
            return false;
        }
    }

    conPro_.notify_one();
    a =  qu_.front();
    qu_.pop();
    return true;
}



template<class T>
int BlockQueue<T>::push(T t){
    unique_lock<mutex> locker(mtx_);
    
    if(qu_.size() == maxSize_){
        // 注意是, 等待 生产者的通知, 因此是 conPro_
        conPro_.wait(locker);
    }
    qu_.push(t);
    // 为什么不是 ontify_all ()
    // 生产者线程中只有一个元素被推入到队列中, 只需要唤醒一个等待的消费者线程即可
    // 避免不必要的竞争和上下文切换，提高性能。
    conCon_.notify_one();
    return 0;
}


template<class T>
void BlockQueue<T>::clear(){
    lock_guard<mutex> locker(mtx_);
    qu_.clear();

}


template<class T>
size_t BlockQueue<T> :: size(){
    lock_guard<mutex> locker(mtx_);
    return qu_.size();
}



template<class T>
bool BlockQueue<T> :: full(){
    lock_guard<mutex> locker(mtx_);
    return qu_.size() == maxSize_;
}

template<class T>
void BlockQueue<T> :: close(){
    lock_guard<mutex> locker(mtx_);
    std::cout<< "closed success"<< '\n';
    // qu_.clear();
    isClose_ = true;
}


template<class T>
void BlockQueue<T>::flush(){
    // 通知消费者
    conCon_.notify_one();
}