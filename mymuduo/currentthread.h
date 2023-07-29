#ifndef CURRENT_THREAD_H
#define CURRENT_THREAD_H

#include<unistd.h>
#include<sys/syscall.h>
#include <sys/types.h>
namespace CurrentThread{
    // 当你在一个源文件中定义了一个全局变量或函数，并且想在其他源文件中使用它时，
    // 需要在其他源文件中使用 extern 关键字进行声明。

    // 线程局部存储
    extern __thread int t_cachedTid;

    void cacheTid();
    // inline 
    int tid();



}





#endif