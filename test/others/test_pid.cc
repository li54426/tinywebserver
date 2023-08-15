
// #include <unistd.h>
// #include <sys/syscall.h>
// #include <sys/types.h>
//#include <signal.h>
#include"currentthread.h"


#include<iostream>

// g++ test_pid.cc currentthread.h currentthread.cc -o test_pid
int main(int argc, char *argv[])
{
    pid_t tid;

    tid = CurrentThread::tid();

    std::cout << tid<<'\n';

return 0;
}