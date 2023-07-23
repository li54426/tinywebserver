#ifndef CURRENT_THREAD_H
#define cURRENT_THREAD_H

#include<unistd.h>
#include<sys/syscall.h>

namespace CurrentThread{
    // 当你在一个源文件中定义了一个全局变量或函数，并且想在其他源文件中使用它时，需要在其他源文件中使用 extern 关键字进行声明。

    // 线程局部存储
    extern __thread int t_cachedTid;

    void cacheTid(){
        if(t_cachedTid == 0){
            // 通过系统调用, 获取当前 tid 
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
    inline int tid(){
        // `__builtin_expect((x > 0), 1)` 表示条件 `x > 0` 的发生概率很高。
        if(__builtin_expect(t_cachedTid == 0, 0) ){
            cacheTid();
        }
        return t_cachedTid;
    }



}





#endif