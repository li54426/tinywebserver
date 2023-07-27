#ifndef BLOCK_QUEUE
#define BLOCK_QUEUE


#include<deque>
#include<queue>
#include<mutex>
#include<condition_variable>

#include<iostream>
using namespace std;

template<class T>
class BlockQueue{
public:
    BlockQueue(int maxsize =512):
         maxSize_ (maxsize){}
    
    ~BlockQueue(){
        close();
    }
    bool pop(T &a);
    bool pop(T &a, int tiemout);
    bool full();
    int push(T);
    size_t size();
    void clear();
    void close();
    void flush();

    

private:
    int maxSize_;
    mutex mtx_;
    queue<T> qu_;
    bool isClose_ = false;
    // 和 生产者消费者相关的 条件变量
    condition_variable conCon_;
    condition_variable conPro_;
};








#endif


