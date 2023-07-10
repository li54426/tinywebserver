#include"blockqueue.h"
#include<iostream>
#include<thread>
// using namespace std;
using std::thread;
#include<unistd.h>
#include<chrono>

int main() {
    // 测试代码
    BlockQueue<int> queue(5); // 最大大小为5的队列

    // 生产者线程
    thread producer([&queue]() {
        for (int i = 0; i < 10; ++i) {
            cout << "生产者推入元素: " << i << '\n';
            queue.push(i);
            this_thread::sleep_for(std::chrono::seconds(1));
        }
        queue.close();
    });
    

    // 消费者线程
    thread consumer([&queue]() {
        int value;
        for (int i = 0; i < 10; ++i) {
            if (queue.pop(value)) {
                cout << "消费者取出元素: " << value << '\n';
            } else {
                cout << "队列为空\n";
            }

            if(i == 4){
                queue.close();
            }
            this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    producer.join();
    consumer.join();
    
    return 0;
}