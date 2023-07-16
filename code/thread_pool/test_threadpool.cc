#include<iostream>


#include"thread_pool.h"
#include<unistd.h>

// g++ test_threadpool.cc thread_pool.h -o test


void printHello(int n) {
    std::cout << "Hello from thread " << n << std::endl;
}

int main() {
    ThreadPool pool(4, 200);

    for (int i = 0; i < 8; ++i) {
        pool.AddTask(printHello, i);
    }
    //~pool;
    // for(int i = 0; i<10; ++i){
    //     sleep(1);
    //     cout<< "sleep 1 seconds"<< '\n';
    // }
    
    // pool.Join();
    for (int i = 0; i < 8; ++i) {
        pool.AddTask(printHello, i+10);
        cout<< "add tasks too"<< '\n';
    }

    // 阻塞等待所有任务完成
    // sleep(10);

    return 0;
}




// #include <iostream>
// #include <vector>
// #include <queue>
// #include <thread>
// #include <functional>
// #include <mutex>
// #include <condition_variable>

// class ThreadPool {
// public:
//     explicit ThreadPool(size_t numThreads)
//         : stop(false)
//     {
//         for (size_t i = 0; i < numThreads; ++i) {
//             workers.emplace_back(
//                 [this] {
//                     for (;;) {
//                         std::function<void()> task;
//                         {
//                             std::unique_lock<std::mutex> lock(queueMutex);
//                             condition.wait(lock, [this] { return stop || !tasks.empty(); });
//                             if (stop && tasks.empty()) {
//                                 return;
//                             }
//                             task = std::move(tasks.front());
//                             tasks.pop();
//                         }
//                         task();
//                     }
//                 }
//             );
//         }
//     }

//     template <class Func, class... Args>
//     void enqueue(Func&& func, Args&& ...args)
//     {
//         {
//             std::unique_lock<std::mutex> lock(queueMutex);
//             tasks.emplace(
//                 [func, args...] (){
//                     func(args...);
//                 }
//             );
//         }
//         condition.notify_one();
//     }

//     ~ThreadPool()
//     {
//         {
//             std::unique_lock<std::mutex> lock(queueMutex);
//             stop = true;
//         }
//         condition.notify_all();
//         for (std::thread &worker : workers) {
//             worker.join();
//         }
//     }

// private:
//     std::vector<std::thread> workers;
//     std::queue<std::function<void()>> tasks;

//     std::mutex queueMutex;
//     std::condition_variable condition;
//     bool stop;
// };

// // 示例用法
// void printNumber(int number)
// {
//     std::cout << "Number: " << number << std::endl;
// }

// int main()
// {
//     ThreadPool pool(4);

//     for (int i = 0; i < 8; ++i) {
//         pool.enqueue(printNumber, i);
//     }

//     // 注意：这里不需要手动调用线程池的析构函数，当 main 函数结束时，线程池会自动销毁并释放资源

//     return 0;
// }
