#include<stdio.h>
#include<unistd.h>
#include<signal.h>


void timeout(int sig){
    if(sig == SIGALRM){
        puts("time out\n");
    }
    alarm(2);
}


void keycontrol(int sig){
    if(sig == SIGINT){
        puts("ctrl +c\n");
    }
}

int main(){
    int i = 0;
    signal(SIGALRM, timeout);
    signal( SIGINT, keycontrol);
    // 调用 alarm() 设定一个定时器，预约 2 秒后触发 SIGALRM 信号。
    // 如果注释掉, 就不会 执行 timeout 函数
    alarm(2);

    for(int i = 0; i<3; ++i){
        puts("wait..");
        sleep(10);
    }
    return 0;
}