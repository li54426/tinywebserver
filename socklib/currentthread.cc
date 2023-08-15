#include "currentthread.h"

namespace CurrentThread
{

    __thread int t_cachedTid = 0;
    void cacheTid()
    {
        if (t_cachedTid == 0)
        {
            long res = ::syscall(SYS_gettid);
            // 通过系统调用, 获取当前 tid
            t_cachedTid = static_cast<pid_t>(res);
        }
    }

    int tid()
    {
        // `__builtin_expect((x > 0), 1)` 表示条件 `x > 0` 的发生概率很高。
        if (__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }

}
