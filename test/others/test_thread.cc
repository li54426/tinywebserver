#include <iostream>
#include <thread>

void foo() {
    std::cout << "Thread is running." << std::endl;
}

int main() {
    std::thread t(foo); // 创建一个新线程，执行函数 foo

    std::cout << "Main thread is doing some work." << std::endl;

    t.join(); // 等待新线程执行完成

    std::cout << "Main thread continues." << std::endl;

    return 0;
}